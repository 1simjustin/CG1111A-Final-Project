/**
 * This function performs a hardcoded 90 degree left turn based on time
 * Delays can be removed where necessary
 */
void left_turn() {
  move(-200, 200);
  delay(390);
  move(0, 0);
  delay(50);
  move(200, 160);
  delay(1);
}

/**
 * This function performs a hardcoded 90 degree left turn , followed by
 * move straight, then another 90 degree left turn based on time
 * Delays can be removed where necessary
 */
void left_left_turn() {
  left_turn();
  move(200, 160);
  delay(1100);
  move(0, 0);
  delay(50);
  move(-200, 200);
  delay(390);
  move(0, 0);
  delay(50);
}

/**
 * This function performs a hardcoded 90 degree right turn based on time
 * Delays can be removed where necessary
 */
void right_turn() {
  move(200, -200);
  delay(425);
  move(0, 0);
  delay(50);
}

/**
 * This function performs a hardcoded 90 degree right turn , followed by
 * move straight, then another 90 degree right turn based on time
 * Delays can be removed where necessary
 */
void right_right_turn() {
  right_turn();
  move(200, 160);
  delay(900);
  move(0, 0);
  delay(50);
  move(200, -200);
  delay(410);
  move(0, 0);
  delay(50);
}

/**
 * This function performs a hardcoded 180 degree right turn based on time
 * Delays can be removed where necessary
 */
void u_turn() {
  move(-200, -200);
  delay(250);
  move(0, 0);
  delay(50);
  move(-200, 200);
  delay(695);
  move(0, 0);
  delay(50);
}

/**
 * This function executes the end of run sequence, inclusive of buzzer music
 * Music is followed by switch state being set to OFF
 */
void end_run() {
  // Calls brake
  move(0, 0);
  delay(50);

  // Each of the following "function calls" plays a single tone.
  // The numbers in the bracket specify the frequency and the duration (ms)
  if (STATE == ON) {
    // Set STATE to OFF to prevent further execution of movement
    STATE = OFF;
    off_lights();

    for (int i = 0; i < 7; i++) {
      buzzer.tone(song_1[i][0], (int)song_1[i][1]);
    }
    //buzzer.noTone();
    delay(NOTE_DURATION * 3.5);
    for (int i = 0; i < 14; i++) {
      buzzer.tone(song_2[i][0], (int)song_2[i][1]);
    }
    buzzer.noTone();
  }
}