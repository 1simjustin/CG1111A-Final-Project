void loop() {
  switch_state();
  ultra();
  if (!on_line()) {
    if (dist != OUT_OF_RANGE) {
      Serial.println(dist);
      pd_control();
    } else {
      if (analogRead(IR) < (baseline * 0.85)) {
        move(200, 100);
      } else {
        // The things we need to do to go straight :(
        move(200, 160);
      }
    }
  } else {
    move(0, 0);
    delay(50);
    read_color();
    off_lights();
    color = knn();
    if (color == 0)
      left_turn();
    else if (color == 1)
      right_turn();
    else if (color == 2)
      u_turn();
    else if (color == 3)
      left_left_turn();
    else if (color == 4)
      right_right_turn();
    else if (color == 5)
      end_run();

    // Update baseline after every turn
    if (color < 6) {
      find_ir_baseline();
    }
  }
}