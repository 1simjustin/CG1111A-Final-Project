/*
This file contains the code for CG1111A Lab B03 Group 5A

@file: Code.ino
@author: Sim Justin

Team Members (4):
Sim Jun Hong
S Praneet
Sim Justin
Shao Sizhe

Tabs in this folder consist of details as follows

1 INIT
------
Initialisation of Global Variables
  Motor Setup
  Movement Vars
  Line Follower Setup
  Ultrasonic Vars
  Color Sensor Setup
  Color Vars
  IR Setup
  IR Vars
  Button Switch Setup
  Buzzer Setup

2 DATASET
---------
Contains dataset for use in KNN Algorithm for color detection

3 SENSOR FUNCTIONS
------------------
ultra()                   Returns distance between the wall and the sensor in cm. Times out at 34cm
off_lights()              Turns off all LED and emitters
find_ir_baseline()        Finds the baseline value of surrounding IR
get_avg(times)            Finds average reading of LDR across times iterations
read_color()              Returns the color which the LDR senses
knn()                     Performs KNN algorithm to determine color sensor color
button_press()            Returns a boolean for whether the button has been pressed
switch_state()            Implementation of an electrical switch to on/off the MBot
on_line()                 Returns a boolean state of whether the MBot is on the line

4 MOVEMENT FUNCTIONS
--------------------
move(a, b)        General movement functions. Takes in 2 integers as the PWM input for each motor
pid_control()              PD control using ultrasonic sensor readings to perform wall tracking


5 CHALLENGES
------------
left_turn()               Hard-coded to perform a 90 degree left turn
left_left_turn()          Hard-coded to perform 90 degree left turn, move forward 1 tile, 90 degree left turn
right_turn()              Hard-coded to perform a 90 degree right turn
right_right_turn()        Hard-coded to perform 90 degree right turn, move forward 1 tile, 90 degree right turn
u_turn()                  Hard-coded to perform a 180 degree right turn
end_run()                 Code to be executed at the end of the run. Consists of stop, music and switching STATE to OFF

6 SETUP
-------
// The MBot runs code in this section ONCE upon booting up
setup():
  Decoder pin initialisation
  IR baseline initialisation
  Serial initialisation

7 MAIN
------
// The MBot runs code in this section CONTINUOUSLY after setup
*/
