void setup() {
  // Initialise colour sensor and IR pins to output for controlling decoder
  for (int decoder_pin = 0; decoder_pin < 2; decoder_pin++) {
    pinMode(ledArray[decoder_pin], OUTPUT);
  }

  // Turn off MBot LEDs, annoying
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  pinMode(EN, OUTPUT);

  // Initialise IR baseline
  find_ir_baseline();

  // Initialise baudrate to prepare for printing to Serial Monitor
  Serial.begin(9600);
}
