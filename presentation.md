
Hytech Racing: a firmware refocus


- slide 1:

Agenda:

Overview
Board Job Descriptions
Motivation for change
Generic Structure
Main ECU refactor
Proposed Timeline

- Overview:

This presentation contains a car firmware study to show what we have currently and understand what we handle through code, what we need to change and why, how we could restructure and change, an example implementation of the change and an estimated timeline.

- Board Job Descriptions:

main ecu:

- reads imu data from SPI
- reads load cell data
- reads pedal data
- reads steering data
- reads dashboard data
- reads bms data
- reads current data
- reads voltage data
- reads potentiometer data

- handles launch mode inverter controller
- handles skidpad mode inverter controller
- handles autocross inverter controller
- handles endurance inverter controller
- handles pedal evaluation logic
- handles watchdog logic
- manages a car state machine
- manages a drivetrain state machine

- commands ready to drive horn
- commands a watchdog
- commands BSPD
- commands IMD
- commands BMS
- commands brake light
- commands 4 inverters
- sends telemetry data