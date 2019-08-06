const int switchPin = 8;

unsigned long previousTime = 0;
int switchState = 0;
int prevSwitchState = 0;

int ledPin = 2;

long interval = 6000;

void setup() {
  // put your setup code here, to run once:

  for (int x = 2; x < 8; x++) {
    pinMode(x, OUTPUT);
  }

  Serial.begin(9600);
  pinMode(switchPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  if (currentTime - previousTime > interval) {
    previousTime = currentTime;
    digitalWrite(ledPin, HIGH);
    ledPin++;
    if (ledPin == 7) {

    }
  }

  switchState = digitalRead(switchPin);

  if (switchState != prevSwitchState) {
    for (int x = 2; x < 8; x++) {
      digitalWrite(x, LOW);
    }

    ledPin = 2;
    previousTime = currentTime;
  }
  prevSwitchState = switchState;
  Serial.println(switchState);
}
