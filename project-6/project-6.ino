int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;
int sensorPin = A0;

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

   // calibrate during the first five seconds
  while (millis() < 5000) {
    int sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }

  digitalWrite(ledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
sensorValue = analogRead(sensorPin);

int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

tone(8, pitch, 20);

delay(10);
}
