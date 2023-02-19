/**
 * This function sets the global variable dist to correspond to the distance between the
 * ultrasonic sensor and the closest object (wall) to it. Sets dist to OUT_OF_RANGE if out of range
 */
void ultra() {
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);
  pinMode(ULTRASONIC, INPUT);

  long duration = pulseIn(ULTRASONIC, HIGH, TIMEOUT);
  if (duration > 0) {
    dist = duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
  } else {
    dist = OUT_OF_RANGE;
  }
}

/**
 * This function is used to toggle off the IR emitter and LEDs
 */
void off_lights() {
  digitalWrite(EN, HIGH);
}

/**
 * This function determines the baseline IR reading by turning off the IR emitter and reading
 * the analog value of surrounding IR during this time before turning the IR emitter back on
 */
void find_ir_baseline() {
  off_lights();
  delay(RGBWait);
  baseline = analogRead(IR);
  digitalWrite(EN, LOW);
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  delay(RGBWait);
}

/**
 * This function finds the average reading of LDR for greater accuracy of LDR readings
 *
 * @param[in] times Number of times to iterate and repeat before finding average
 *
 * @return Returns the averaged LDR values across times iterations
 */
int get_avg(int times) {
  //find the average reading for the requested number of times of scanning LDR
  int reading;
  int total = 0;
  //take the reading as many times as requested and add them up
  for (int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total = reading + total;
    delay(LDRWait);
  }
  //calculate the average and return it
  return total / times;
}

/**
 * This function sets the global array colourArray to reflect the RGB values sensed by the LDR with correspondence to
 * lighting up of the red, green and blue lights
 */
void read_color() {
  // turn on one colour at a time and LDR reads 5 times
  for (int c = 0; c <= 2; c++) {
    // Prepare LED to be turned on
    digitalWrite(EN, LOW);

    for (int zz = 0; zz < 2; zz++) {
      digitalWrite(ledArray[zz], truth[c][zz]);
    }
    delay(RGBWait);

    // get the average of 5 consecutive readings for the current colour and return an average
    colourArray[c] = get_avg(5);

    // the average reading returned minus the lowest value divided by the maximum possible range
    // multiplied by 255 will give a value between 0-255, representing the value for the current reflectivity
    colourArray[c] = (colourArray[c] - blackArray[c]) / (greyDiff[c]) * 255;

    off_lights();
    delay(RGBWait);
  }
}

/**
 * This function performs K-Nearest Neighbour algorithm, using the data set provided in DATASET to
 * determine the color on which the robot is currently on for decoding of challenges
 *
 * @return Returns an integer representing the color on which the robot is standing.
 * For map of integer to color, view DATASET
 */
int knn() {
  // Ordered from furthest k-th nearest neighbour to closest
  float closest_neighbour_dist[knn_k];
  int neighbour_index[knn_k];
  // Initialise Closest Neighbour Array
  for (int i = 0; i < knn_k; i++) {
    closest_neighbour_dist[i] = 450;  // 450 > sqrt(255 * 255 * 3) which is max possible value
  }

  // Find k closest neighbours
  float euclidean;
  for (int i = 0; i < dataset_count; i++) {
    for (int j = 0; j < 3; j++) {
      euclidean += sq(colourArray[j] - dataset[i][j]);
    }
    euclidean = sqrt(euclidean);
    // Compare to elements in closest_neighbour_dist
    for (int j = knn_k - 1; j >= 0; j--) {
      // Found desired position in closest_neighbour_dist
      if (euclidean < closest_neighbour_dist[j]) {
        // Shift elements in closest_neighbour_dist and neighbour_index
        for (int k = 0; k < j; k++) {
          closest_neighbour_dist[k] = closest_neighbour_dist[k + 1];
          neighbour_index[k] = neighbour_index[k + 1];
        }
        closest_neighbour_dist[j] = euclidean;
        neighbour_index[j] = i;
        break;
      }
    }
  }

  // Find mode color of k closest neighbours
  int neighbour_color[num_color] = { 0 };
  for (int i = 0; i < knn_k; i++) {
    neighbour_color[dataset[neighbour_index[i]][3]]++;
  }
  int closest_color = 0;
  for (int i = 1; i < num_color; i++) {
    if (neighbour_color[i] > neighbour_color[closest_color]) {
      closest_color = i;
    }
  }
  return closest_color;
}

/**
 * This function returns a boolean value of whether the button has been pressed
 */
bool button_press() {
  int press = analogRead(BUTTON);
  if (press < 512) {
    return true;
  }
  return false;
}

/**
 * This function is used to control the ON-OFF state of the robot based on the button switch
 */
void switch_state() {
  int i = 0;
  // use of dummy counter to iterate until button is let go
  if (button_press()) {
    while (button_press()) {
      i++;
    }

    // Switches STATE from 0 to 1 or 1 to 0 (OFF->ON OR ON->OFF)
    if (STATE == OFF) {
      STATE = ON;
      // Reacquire IR baseline when switching to ON state
      find_ir_baseline();
    } else {
      STATE = OFF;
      off_lights();
    }
  }
}

/**
 * This function returns a boolean value for whether the line tracking sensor detects
 * that the robot is fully on the line (i.e. reached a checkpoint)
 */
bool on_line() {
  sensorState = lineFinder.readSensors();
  if (sensorState != S1_OUT_S2_OUT) {
    return true;
  }
  return false;
}
