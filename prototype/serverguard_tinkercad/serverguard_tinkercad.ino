/*
 * ServerGuard: Tinkercad prototype firmware
 * Author: Anthony Walston (April 2026)
 *
 * Monitors temperature and moisture. It lights a green LED when conditions
 * are normal, yellow and red LEDs for warnings and alarms, and beeps a
 * piezo when either reading reaches its alarm level. Readings are printed
 * to the serial monitor at 9600 baud.
 *
 * This sketch targets the Tinkercad simulation, which uses:
 *   - a TMP36 temperature sensor on A2
 *   - a soil moisture sensor on A1 (powered from A0) as the humidity input,
 *     because Tinkercad has no DHT11
 *
 * The ServerGuard PCB uses an LM35 (A2) and a DHT11 (A1) instead. Running
 * this code on the PCB needs two changes: read the DHT11 with a DHT
 * library, and convert the LM35 with tempC = voltage * 100.0.
 * The LED and piezo pins match the PCB.
 */

int moisture = 0;
int tempRaw = 0;
float voltage = 0.0;
float tempC = 0.0;

const int moisturePowerPin = A0;
const int moisturePin = A1;
const int tempPin = A2;

const int moistureYellowLed = 8;
const int moistureRedLed = 9;
const int tempYellowLed = 10;
const int tempRedLed = 11;
const int moistureGreenLed = 12;
const int piezoPin = 13;

// Server-room style thresholds
const float tempWarning = 27.0;
const float tempAlarm = 30.0;

// Adjust these if your moisture sensor reads differently
const int moistureWarning = 350;
const int moistureAlarm = 500;

void setup()
{
  pinMode(moisturePowerPin, OUTPUT);
  pinMode(moisturePin, INPUT);
  pinMode(tempPin, INPUT);

  pinMode(moistureYellowLed, OUTPUT);
  pinMode(moistureRedLed, OUTPUT);
  pinMode(tempYellowLed, OUTPUT);
  pinMode(tempRedLed, OUTPUT);
  pinMode(moistureGreenLed, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  // Read temperature from TMP36
  tempRaw = analogRead(tempPin);
  voltage = tempRaw * (5.0 / 1023.0);
  tempC = (voltage - 0.5) * 100.0;

  // Read moisture
  digitalWrite(moisturePowerPin, HIGH);
  delay(10);
  moisture = analogRead(moisturePin);
  digitalWrite(moisturePowerPin, LOW);

  bool tempTooHigh = tempC >= tempAlarm;
  bool tempWarningOn = tempC >= tempWarning && tempC < tempAlarm;

  bool moistureTooHigh = moisture >= moistureAlarm;
  bool moistureWarningOn = moisture >= moistureWarning && moisture < moistureAlarm;

  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print("   Moisture: ");
  Serial.println(moisture);

  // Reset outputs
  digitalWrite(moistureYellowLed, LOW);
  digitalWrite(moistureRedLed, LOW);
  digitalWrite(tempYellowLed, LOW);
  digitalWrite(tempRedLed, LOW);
  digitalWrite(moistureGreenLed, LOW);
  noTone(piezoPin);

  // Green only when everything is normal
  if (!tempWarningOn && !tempTooHigh && !moistureWarningOn && !moistureTooHigh) {
    digitalWrite(moistureGreenLed, HIGH);
  }

  // Moisture LEDs
  if (moistureWarningOn) {
    digitalWrite(moistureYellowLed, HIGH);
  }
  else if (moistureTooHigh) {
    digitalWrite(moistureRedLed, HIGH);
  }

  // Temp LEDs
  if (tempWarningOn) {
    digitalWrite(tempYellowLed, HIGH);
  }
  else if (tempTooHigh) {
    digitalWrite(tempYellowLed, LOW);
    digitalWrite(tempRedLed, HIGH);
  }

  // Alarm if either condition is too high
  if (tempTooHigh || moistureTooHigh) {
    tone(piezoPin, 900);
    delay(50);
    noTone(piezoPin);
    delay(50);
    tone(piezoPin, 900);
    delay(50);
    noTone(piezoPin);
    delay(300);
  }

  delay(100);
}
