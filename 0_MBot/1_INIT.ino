#include <MeMCore.h>
#include <Wire.h>
#include <Math.h>

/* PORT REFERENCE */
/* PORT1  {11,12} RJ25_1
   PORT2  {09,10} RJ25_2
   PORT3  {A2,A3} RJ25_3 INPUT
   PORT4  {A0,A1} RJ25_4 OUTPUT
   PORT5  {NC,NC}
   PORT6  {08,A6} BUZZER, LIGHT SENSOR
   PORT7  {A7,13} BUTTON, 2LED
   PORT8  {08,A6} BUZZER, LIGHT SENSOR
   PORT9  {06,07} PWM M2, DIR M2
   PORT10 {05,04} PWM M1, DIR M1
*/

/* MOTOR SETUP */
MeDCMotor leftMotor(M1);   // assigning leftMotor to port M1
MeDCMotor rightMotor(M2);  // assigning RightMotor to port M2

int L_motorSpeed;
int R_motorSpeed;

/* MOVEMENT VARS */
// Vars used for PD control
const double ku = 175;
const double tu = 10.5 / 17;
const double kp = ku * 0.8;
const double kd = 0.1 * ku * tu;

const double threshold = 10.5;
double error;
double prev_error = 0;
double error_delta;

double correction_dble;
int correction;

/* LINE FOLLOW SETUP */
MeLineFollower lineFinder(PORT_1);  // assigning lineFinder to RJ25 port 2
int sensorState;
int status = 0;  // global status; 0 = do nothing, 1 = mBot runs

/* ULTRASONIC VARS */
#define TIMEOUT 2000        // Max microseconds to wait; choose according to max distance of wall, 2000 corresponds to 34cm
#define SPEED_OF_SOUND 340  // Update according to your own experiment
#define ULTRASONIC 10
// If you are using Port 1 of mCore, the ultrasonic sensor uses digital pin 12
// If you are using Port 2 of mCore, the ultrasonic sensor uses digital pin 10
#define OUT_OF_RANGE 100
double dist;

/* COLOR SENSOR SETUP */
#define RGBWait 150
#define LDRWait 10
#define LDR A2
#define EN A4
// Define colour sensor LED pins
const int ledArray[] = { A0, A1 };
const int truth[][2] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };  // R,G,B,IR
// placeholders for colour detected
int red = 0;
int green = 0;
int blue = 0;
// floats to hold colour arrays
float colourArray[] = { 0, 0, 0 };
// const float whiteArray[] = { 979.25, 986.5, 984.75 };
const float blackArray[] = { 964, 909, 920 }; // { 939, 907.5, 913.5 };  // { 964, 897, 904 };  // { 960.25, 902, 907.25 };
const float greyDiff[] = { 19, 81, 68 }; // { 32.5, 79, 71.25 };      // { 17, 91, 82 };       // { 19, 84.5, 77.5 };

/* COLOR VARS */
#define knn_k 8
#define dataset_count 7 * 10
#define num_color 7
int color;

/* IR SETUP */
#define IR A3

/* IR VARS */
int baseline;
// IR value will drop below baseline if in close proximity

/* BUTTON SWITCH SETUP */
#define OFF 0
#define ON 1
int BUTTON = A7;
int STATE = 0;
// Button has 1023 when not pressed, 0 when pressed

/* BUZZER SETUP */
MeBuzzer buzzer;  // create the buzzer object
//Constants for Music
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_F5S 740
#define NOTE_G5 784
#define NOTE_A5 880
#define NOTE_B5 988
#define NOTE_C6S 1109
#define NOTE_D6 1175
#define NOTE_DURATION 359

// Both song segments are arrays of notes to be played followed
// by the duration to play them
float song_1[][2] = {
  { NOTE_D5, NOTE_DURATION * 1.5 },
  { NOTE_F5S, NOTE_DURATION / 2 },
  { NOTE_E5, NOTE_DURATION },
  { NOTE_D5, NOTE_DURATION },
  { NOTE_F5S, NOTE_DURATION },
  { NOTE_G5, NOTE_DURATION },
  { NOTE_A5, NOTE_DURATION * 2 }
};

float song_2[][2] = {
  { NOTE_A5, NOTE_DURATION },
  { NOTE_B5, NOTE_DURATION * 1.5 },
  { NOTE_D6, NOTE_DURATION * 0.5 },
  { NOTE_C6S, NOTE_DURATION },
  { NOTE_A5, NOTE_DURATION },
  { NOTE_B5, NOTE_DURATION },
  { NOTE_E5, NOTE_DURATION },
  { NOTE_E5, NOTE_DURATION },
  { NOTE_F5S, NOTE_DURATION * 0.5 },
  { NOTE_G5, NOTE_DURATION * 0.5 },
  { NOTE_F5S, NOTE_DURATION * 0.5 },
  { NOTE_E5, NOTE_DURATION * 0.5 },
  { NOTE_D5, NOTE_DURATION },
  { NOTE_D5, NOTE_DURATION * 2 }
};
