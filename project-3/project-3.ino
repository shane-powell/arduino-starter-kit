int sensorMin = 1023;
int sensorMax = 0;

const int sensorPin = A0;
float baselineTemp = 20.80;

void setup() {


  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.flush();
  Serial.println();
  calibrateSensor();

  for (int pinNumber = 2; pinNumber < 5; pinNumber ++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(sensorPin);

  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  Serial.print(", degrees C: ");

  float temperature = (voltage - .5) * 100;

  Serial.println(temperature);

  if (temperature < baselineTemp) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  delay(1);
}

void calibrateSensor()
{
  // calibrate during the first five seconds
  while (millis() < 5000) {
    int sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  float minVoltage = (sensorMin / 1024.0) * 5.0;
  float maxVoltage = (sensorMax / 1024.0) * 5.0;
  float minTemperature = (minVoltage - .5) * 100;
  float maxTemperature = (maxVoltage - .5) * 100;

  baselineTemp = (minTemperature + maxTemperature) / 2;

  Serial.println("Sensor Calibration");

  Serial.print("Min ");
  Serial.print(minTemperature);
  Serial.print (" / ");
  Serial.print("Max ");
  Serial.print(maxTemperature);
  Serial.print (" / ");
  Serial.print("AVG ");
  Serial.println(baselineTemp);
  delay(10000);
}
