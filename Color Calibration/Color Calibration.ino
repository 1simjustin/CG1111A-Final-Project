// Define time delay before the next RGB colour turns ON to allow LDR to stabilize
#define RGBWait 150  //in milliseconds

// Define time delay before taking another LDR reading
#define LDRWait 10  //in milliseconds

#define LDR A2  //LDR sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed
#define EN A4

// Define colour sensor LED pins
int ledArray[] = { A0, A1 };
int truth[][2] = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };

//placeholders for colour detected
int red = 0;
int green = 0;
int blue = 0;

//floats to hold colour arrays
float colourArray[] = { 0, 0, 0 };
float whiteArray[] = { 0, 0, 0 };
float blackArray[] = { 0, 0, 0 };
float greyDiff[] = { 0, 0, 0 };

char colourStr[3][5] = { "R = ", "G = ", "B = " };

void setup() {
  //setup the outputs for the colour sensor
  for (int c = 0; c <= 2; c++) {
    // pinMode(ledArray[c], OUTPUT);
    for (int zz = 0; zz < 2; zz++) {
      pinMode(ledArray[zz], OUTPUT);
    }
  }
  pinMode(LED, OUTPUT);  //Check Indicator -- OFF during Calibration
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  //begin serial communication
  Serial.begin(9600);

  setBalance();             //calibration
  digitalWrite(LED, HIGH);  //Check Indicator -- ON after Calibration

  Serial.println("White Array");
  for (int c = 0; c < 3; c++) {
    Serial.print(colourStr[c]);
    Serial.print(whiteArray[c]);
  }
  Serial.println();
  Serial.println("Black Array");
  for (int c = 0; c < 3; c++) {
    Serial.print(colourStr[c]);
    Serial.print(blackArray[c]);
  }
  Serial.println();
  Serial.println("Grey Array");
  for (int c = 0; c < 3; c++) {
    Serial.print(colourStr[c]);
    Serial.print(greyDiff[c]);
  }
  Serial.println();
}

void loop() {
}

void setBalance() {
  //set white balance
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);             //delay for five seconds for getting sample ready
  digitalWrite(LED, LOW);  //Check Indicator OFF during Calibration
                           //scan the white sample.
                           //go through one colour at a time, set the maximum reading for each colour -- red, green and blue to the white array
  for (int i = 0; i <= 2; i++) {
    for (int zz = 0; zz < 2; zz++) {
      digitalWrite(ledArray[zz], truth[i][zz]);
    }
    // digitalWrite(ledArray[i], 255);
    delay(RGBWait);
    whiteArray[i] = getAvgReading(5);  //scan 5 times and return the average,
    // digitalWrite(ledArray[i], 0);
    for (int zz = 0; zz < 2; zz++) {
      digitalWrite(ledArray[zz], 1);
    }
    delay(RGBWait);
  }
  //done scanning white, time for the black sample.
  //set black balance
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000);  //delay for five seconds for getting sample ready
                //go through one colour at a time, set the minimum reading for red, green and blue to the black array
  for (int i = 0; i <= 2; i++) {
    // digitalWrite(ledArray[i], 255);
    for (int zz = 0; zz < 2; zz++) {
      digitalWrite(ledArray[zz], truth[i][zz]);
    }
    delay(RGBWait);
    blackArray[i] = getAvgReading(5);
    // digitalWrite(ledArray[i], 0);
    for (int zz = 0; zz < 2; zz++) {
      digitalWrite(ledArray[zz], 1);
    }
    delay(RGBWait);
    //the differnce between the maximum and the minimum gives the range
    greyDiff[i] = whiteArray[i] - blackArray[i];
  }

  //delay another 5 seconds for getting ready colour objects
  Serial.println("Colour Sensor Is Ready.");
  delay(5000);
}


int getAvgReading(int times) {
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