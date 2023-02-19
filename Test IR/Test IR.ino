#define IR A3   //IR R sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed
#define EN A4

// Define colour sensor LED pins
int ledArray[] = { A0, A1 };
int truth[][2] = {{0,0},{0,1},{1,0},{1,1}};

void setup() {
  // put your setup code here, to run once:
  pinMode(EN,OUTPUT);
  digitalWrite(EN,LOW);
  for (int i=0;i<2;i++){
    pinMode(ledArray[i],OUTPUT);
    digitalWrite(ledArray[i],1);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(IR));

}
