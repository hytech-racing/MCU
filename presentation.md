
Hytech Racing: a firmware refocus


- slide 1:

Agenda:

Overview
Main ECU Job Description
Motivation for change
Generic Structure
Main ECU refactor
Proposed Timeline

This presentation contains a car firmware study to show what we have currently and understand what we handle through code, what we need to change and why, how we could restructure and change, an example implementation of the change and an estimated timeline.

- Board Job Description:

main ecu:

imu data from SPI
load cell data
pedal data
steering data
dashboard data
bms data
current data
voltage data
potentiometer data

launch mode inverter controller
skidpad mode inverter controller
autocross inverter controller
endurance inverter controller
pedal evaluation logic
watchdog logic
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


- hardware abstraction

component definition

benefits:
1. testability
2. portability

- Rule of Separation

" Separate policy from mechanism; separate interfaces from engines "
- The Art of Unix Programming: Chapter 1



