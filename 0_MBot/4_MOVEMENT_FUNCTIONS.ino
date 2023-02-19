/**
 * This function is a general movement function used throughout the file.
 * Takes in values from -255 to 255 as input and writes it to the motors as PWM values
 * Switch state has to be ON for movement to be executed
 * 
 * @param[in] L_spd PWM speed of Left Motor
 *
 * @param[in] R_spd PWM speed of Right Motor
 */
void move(int L_spd, int R_spd) {
  if (STATE == ON) {
    leftMotor.run(-L_spd);
    rightMotor.run(R_spd);
  } else {
    leftMotor.run(0);
    rightMotor.run(0);
  }
}

/**
 * This function performs PD movement of the robot using ultrasonic sensor readings. Threshold found under INIT
 *
 * Theory
 * ------
 * Proportional: Use of difference between the expected threshold and actual ultrasonic distance to influence level of correction
 * Helps to increase correction as error increases
 *
 * Derivative: Use of difference between current error and previous error to influence level of correction
 * Helps to smooth out correction as robot approaches threshold
 */
void pd_control() {
  // Calculate error as difference between ultrasonic and expected threshold
  // Calculate derivative as difference between current error and previous error
  // Calculate correction as a summation of P component and D component and typecast to int
  if (dist != OUT_OF_RANGE) {
    error = dist - threshold;
    error_delta = error - prev_error;
    correction_dble = kp * error + kd * error_delta;
    correction = (int)correction_dble;

    // Determine direction of correction and execute movement
    if (correction < 0) {
      L_motorSpeed = 255 + correction;
      R_motorSpeed = 255;
    } else {
      L_motorSpeed = 255;
      R_motorSpeed = 255 - correction;
    }
    move(L_motorSpeed, R_motorSpeed);

    // Initialise current error as new previous error
    prev_error = error;
  } else {
    // Re-initialise previous error to zero to prevent past interference if ultrasonic sensor
    // goes out of range
    prev_error = 0;
  }
}
