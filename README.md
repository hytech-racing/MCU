new MCU code:
- component definition:
     an abstract sub-system of the physical car or the code that requires logic to be evaluated by the MCU to determine what input to give it or logic required to handle output from.
- driver definition:
    - code required to purely unpack / pack data into internal structs / classes for use by components or logic

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
    
```mermaid
flowchart TD

```