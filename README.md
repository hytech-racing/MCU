### outline

Levels represent the layer of abstraction they are on. The reason for keeping track of this is to minimize the layers of abstraction for ease of understanding while also creating logical structure and getting maximum benefit per abstraction.

##### state diagram legend

`+`  = Public
`-`  = Private


#### level 1: state machine goals for interface design and implementation
- __Reason for abstraction__: allows for easy swapping and adding of different portable systems and better [separation of concerns](https://en.wikipedia.org/wiki/Separation_of_concerns) from [business logic](https://www.techtarget.com/whatis/definition/business-logic) of the car to the business logic of the system.


Any firmware project that needs to have different states needs each system that creates outputs and / or controls real systems of the car needs can be thought of as each system being controlled by the state machine. What I am thinking is that in a similar fashion to the shared bus, each system can contain a shared pointer to the state machine. The system can know what state the car is in and based on the state it can determine how to behave. Obviously the state machine also needs to know about what the system is doing as well to determine the state, so the system also needs to be able to pass back data to the state machine. 

For example, our state machine needs to handle understand the state of the pedals system. The pedals dont know about the state of the car, but it does know whether or not the pedals are outputting valid data. Each system can manage their own state and the abstract system base class could contain the set of system-agnostic states through which the statemachine evaluates.

It is only within the logic of our state machine that the systems are allowed to communicate with one another. 

The main idea is that each firmware project has a specific implementation of a state machine, however the systems are portable between firmware projects. Additionally, the systems remain as concrete 




```mermaid
---
title: state machine and system state abstraction
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
        
        
        VectornavSystem* vectornav
        PedalsSystem* pedals
        DashSystem* dashboard


        DrivetrainSystem* drivetrain

        TorqueVectoringControllerSystem* tvc
        LaunchControlSystem* launch_control

        car_state state
        void init()
        void loop()
        bool set_state(car_state state)
    }
    

    car_state "1" *-- StateMachine : contains

```



#### level 2 portable Systems: interfaces, logic and structure

- __Reason for abstraction__: these Systems allow us to have board portable pieces so that when newer iterations of boards are made, the same systems that the previous iteration handled can be kept while only the hardware specific code changes. 

For instance, when a new MCU board is created with a new steering sensor input, code within the controller systems will not need to change, only that a new sensor system will be used within the state machine to feed the controller input.

below are some hypothetical system class definitions.
```mermaid
---
title: systems
---
classDiagram
    class PedalsSystem{
        -void validate_accel_pedals()
        -void validate_brake_pedals()

        +void set_accel_pedal_values(float apps1, float apps2)
        +void set_brake_pedal_values(float brake1, float brake2)
        +float get_desired_throttle()
        +void validate()
    } 
    class TorqueVectoringControllerSystem{
        
        +void init(torque_vectoring_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void calculate_estimated_wheel_slip()
        -void predict()
        -void run_pid()
    }
    
    class LaunchControlSystem{
        
        +void init(launch_control_params params)
        +void set_state_estimate(car_state state)
        +torque_cmds get_torque_cmds(float desired_throttle)
        -void pull_from_table(float current_speed)
    }
    
    
```

#### level 2 SPI / i2c data bus abstraction from hardware specific implementations

- __Reason for abstraction__: this allows us to create a specific type of system that uses a shared resource, for example multiple sensors on a SPI bus, that each have their own scaling to produce data for feeding other systems.

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


### state machine documentation

```mermaid
stateDiagram-v2
    startup : STARTUP
    trac_sys_na : TRACTIVE_SYSTEM_NOT_ACTIVE
    trac_sys_a : TRACTIVE_SYSTEM_ACTIVE
    inv_en : ENABLING_INVERTERS
    rtd_s : WAITING_READY_TO_DRIVE_SOUND
    rtd : READY_TO_DRIVE

    startup --> trac_sys_na: first tick of state machine
    trac_sys_na --> trac_sys_a: drivetrain voltage over threshold 
    trac_sys_a --> trac_sys_na: drivetrain voltage _not_ over threshold
    trac_sys_a --> inv_en: brake and start button pressed
    inv_en --> trac_sys_na: drivetrain voltage _not_ over threshold
    inv_en  --> rtd_s: drivetrain enabled
    rtd_s --> trac_sys_na: drivetrain voltage _not_ over threshold
    rtd_s --> rtd: buzzer done buzzing
    rtd --> trac_sys_na: drivetrain voltage _not_ over threshold
    rtd --> trac_sys_a: drivetrain error occured
```
#### running the tests

This repo uses platformio testing for CI unit testing. these tests can be run locally with `pio test -e test_env`. The CI checks to ensure that the code both compiles for the teensy and ensures that the tests are passing.



#### notes
new MCU code:
- system definition:
     an abstract sub-system of the physical car or the code that requires logic to be evaluated by the MCU to determine what input to give it or logic required to handle output from.
- interface definition:
    - code required to purely unpack / pack data into internal structs / classes for use by systems or logic

- architecture:

    - over-arching state machine
    - systems level 
        - inverters (multiple)
        - pedals
        - torque / speed controller
        - dashboard interface
        
    - interface level:
        - hytech_can interface
        - spi interfaces: SPI adcs for load cells, steering input, glv, etc.
