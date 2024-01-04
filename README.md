new MCU code:
- component definition:
     an abstract sub-system of the physical car or the code that requires logic to be evaluated by the MCU to determine what input to give it or logic required to handle output from.
- driver definition:
    - code required to purely unpack / pack data into internal structs / classes for use by components or logic
    - I think the best way to handle the driver level is that all the drivers 
- state machine 
- architecture:

    - over-arching state machine
    - components level 
        - inverters (multiple)
        - pedals
        - torque / speed controller
        - driver dashboard
        
    - driver level:
        - hytech_can driver
        - spi drivers: SPI adcs for load cells, steering input, glv, etc.

### outline

Levels represent the layer of abstraction they are on. The reason for keeping track of this is to minimize the layers of abstraction for ease of understanding while also creating logical structure and getting maximum benefit per abstraction.

##### state diagram legend

`+`  = Public
`-`  = Private


#### level 1: state machine goals for interface design and implementation
- Reason for abstraction: allows for easy swapping and adding of different portable components and better [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns) from [business logic](https://www.techtarget.com/whatis/definition/business-logic) of the car to the business logic of the component.


Any firmware project that needs to have different states needs each component that creates outputs and / or controls real components of the car needs can be thought of as each component being controlled by the state machine. What I am thinking is that in a similar fashion to the shared bus, each component can contain a shared pointer to the state machine. The component can know what state the car is in and based on the state it can determine how to behave. Obviously the state machine also needs to know about what the component is doing as well to determine the state, so the component also needs to be able to pass back data to the state machine. 

For example, our state machine needs to handle understand the state of the pedals component. The pedals dont know about the state of the car, but it does know whether or not the pedals are outputting valid data. Each component can manage their own state and the abstract component base class could contain the set of component-agnostic states through which the statemachine evaluates.

It is only within the logic of our state machine that the components are allowed to communicate with one another. 

The main idea is that each firmware project has a specific implementation of a state machine, however the components are portable between firmware projects. Additionally, the components remain as concrete 




```mermaid
---
title: state machine and component state abstraction
---
classDiagram

    class component_state{
        <<enumeration>>
        INITIALIZING
        ACTIVE
        STOPPED
        ERROR
    }
    class car_state{
        <<enumeration>>
        STARTUP
        INITIALIZING 
        READY_TO_DRIVE
        ERROR
    }
    class StateMachine {
        
        component* bms
        component* vectornav
        component* pedals
        component* dashboard
        component* drivetrain

        car_state state
        void init()
        void loop()
        bool set_state(car_state)
    }
    
    class component{
        <<Abstract>>
        component_state state
    }


    component_state "1" *-- component : contains
    component_state "N" *-- StateMachine : contains
    car_state "1" *-- StateMachine : contains

```



#### level 2 portable components: interfaces, logic and structure

Reason for abstraction: these components can be a part of a shared library between all boards. 

For instance, if our dashboard firmware needed to know about the state of our pedals for displaying whether or not they are implausible, all we would need to do to integrate it would be to create an instance of the class

below are some hypothetical component class definitions.
```mermaid
---
title: components
---
classDiagram
    class component{
        <<Abstract>>
        -component_state state_
        +component_state get_state()
        +void set_state()
    }
    class pedal_handler{
        -void validate_accel_pedals()
        -void validate_brake_pedals()

        +void set_accel_pedal_values(float apps1, float apps2)
        +void set_brake_pedal_values(float brake1, float brake2)
        +float get_desired_throttle()
        +void validate()
    } 
    class torque_vectoring_controller {
        
        +void init(torque_vectoring_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void calculate_estimated_wheel_slip()
        -void predict()
        -void run_pid()
    }
    
    class launch_controller {
        
        +void init(launch_control_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void pull_from_table(float current_speed)
    }
    component <|-- pedal_handler : implements
    component <|-- torque_vectoring_controller : implements
    component <|-- launch_controller : implements
    
```

#### level 3 SPI / i2c data bus abstraction from hardware specific implementations
- idea for abstract of the shared bus sensors. This is currently aimed at our use of a SPI bus. The read data functions are what convert the data gotten from the shared bus to the real-world values for each one of the sensors. This was being attempted with ADC_SPI versus STEERING_SPI using just copies of the class. 

```mermaid
---
title: shared data bus abstraction
---
classDiagram
    
    class Sensor~SharedDataBusType~{
        <<Abstract>>
        const shared_ptr~SharedBusType~ bus
        Sensor<SharedDataBusType>(const SharedDataBusType& bus)
    }

    class SteeringSensor~SharedDataBusType~{
        float readPosition()
    }
    class LoadSensor~SharedDataBusType~{
        float readForce()
    }
    class CurrentSensor~SharedDataBusType~{
        float readCurrent()
    }
    Sensor <|-- LoadSensor : implements
    Sensor <|-- SteeringSensor : implements
    Sensor <|-- CurrentSensor : implements

```

```mermaid
flowchart TD

```