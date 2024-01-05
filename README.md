new MCU code:
- component definition:
     an abstract sub-system of the physical car or the code that requires logic to be evaluated by the MCU to determine what input to give it or logic required to handle output from.
- driver definition:
    - code required to purely unpack / pack data into internal structs / classes for use by components or logic
    - I think the best way to handle the driver level is that all the drivers 

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
- __Reason for abstraction__: allows for easy swapping and adding of different portable components and better [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns) from [business logic](https://www.techtarget.com/whatis/definition/business-logic) of the car to the business logic of the component.


Any firmware project that needs to have different states needs each component that creates outputs and / or controls real components of the car needs can be thought of as each component being controlled by the state machine. What I am thinking is that in a similar fashion to the shared bus, each component can contain a shared pointer to the state machine. The component can know what state the car is in and based on the state it can determine how to behave. Obviously the state machine also needs to know about what the component is doing as well to determine the state, so the component also needs to be able to pass back data to the state machine. 

For example, our state machine needs to handle understand the state of the pedals component. The pedals dont know about the state of the car, but it does know whether or not the pedals are outputting valid data. Each component can manage their own state and the abstract component base class could contain the set of component-agnostic states through which the statemachine evaluates.

It is only within the logic of our state machine that the components are allowed to communicate with one another. 

The main idea is that each firmware project has a specific implementation of a state machine, however the components are portable between firmware projects. Additionally, the components remain as concrete 




```mermaid
---
title: state machine and component state abstraction
---
classDiagram

    
    class car_state{
        <<enumeration>>
        STARTUP
        INITIALIZING 
        READY_TO_DRIVE
        ERROR
    }
    class StateMachine {
        
        BMSComponent* bms
        VectornavComponent* vectornav
        PedalsComponent* pedals
        DashComponent* dashboard


        InverterComponent* left_front
        InverterComponent* right_front
        InverterComponent* left_rear
        InverterComponent* right_rear

        TorqueVectoringControllerComponent* tvc
        LaunchControlComponent* launch_control

        car_state state
        void init()
        void loop()
        bool set_state(car_state state)
    }
    

    car_state "1" *-- StateMachine : contains

```



#### level 2 portable components: interfaces, logic and structure

- __Reason for abstraction__: these components allow us to have board portable pieces so that when newer iterations of boards are made, the same components that the previous iteration handled can be kept while only the hardware specific code changes. 

For instance, when a new MCU board is created with a new steering sensor input, code within the controller components will not need to change, only that a new sensor component will be used within the state machine to feed the controller input.

below are some hypothetical component class definitions.
```mermaid
---
title: components
---
classDiagram
    class PedalsComponent{
        -void validate_accel_pedals()
        -void validate_brake_pedals()

        +void set_accel_pedal_values(float apps1, float apps2)
        +void set_brake_pedal_values(float brake1, float brake2)
        +float get_desired_throttle()
        +void validate()
    } 
    class TorqueVectoringControllerComponent{
        
        +void init(torque_vectoring_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void calculate_estimated_wheel_slip()
        -void predict()
        -void run_pid()
    }
    
    class LaunchControlComponent{
        
        +void init(launch_control_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void pull_from_table(float current_speed)
    }
    
    
```

#### level 2 SPI / i2c data bus abstraction from hardware specific implementations

- __Reason for abstraction__: this allows us to create a specific type of component that uses a shared resource, for example multiple sensors on a SPI bus, that each have their own scaling to produce data for feeding other components.

This is currently aimed at our use of a SPI bus. The read data functions are what convert the data gotten from the shared bus to the real-world values for each one of the sensors. This was being attempted with ADC_SPI versus STEERING_SPI using just copies of the class. 

```mermaid
---
title: shared data bus class inheritting
---
classDiagram
    
    class Sensor~SharedDataBusType~{
        SharedBusType* bus
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