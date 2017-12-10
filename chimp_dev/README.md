# PSU_WowweeChimpProject
This repo is for ECE4/578 Robotics Fall 2017: Project 2.

Hack the Wowwee Chimpanzee and make it portable for future additions.
A Raspberry Pi 3 will be used to interface with the Chimp

## Team Members
- Aaron Chan (chanaar@pdx.edu)
- Julian Saunders (sjulian@pdx.edu)

## Chimp Dev Code
We will be using wiringPi to control the Chimp head. 
Motor controls done with MCP3008 ADC and four L293D H-bridges.
This section will be updated again if any further work will be done.

Update 2017-12-09
- Code interfaces with a MCP3008 ADC and four L293D H-bridges
- There is no control for eyelids yet due to problems with motors
- Rotary encoders are read in to determine position of the motors and used for test params for movement.
- Motor controls are done with functions that take degrees as input. Degrees input are absolute positions of motors and are not adjustments relative to the current position.

