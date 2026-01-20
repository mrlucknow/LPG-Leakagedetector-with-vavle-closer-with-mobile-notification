#include <ESP32Servo.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3XEi93bEb"
#define BLYNK_TEMPLATE_NAME "gas"
#define BLYNK_AUTH_TOKEN "mzv1mpMvJCI6jIqJoMXbgTWCOiPavdvy"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define MQ6_ANALOG 34
#define SERVO_PIN 2
#define FAN_PIN 5   // Relay IN connected here (low-level triggered)
int threshold = 2000;

char ssid[] = "Sahab";
char pass[] = "change@123";

const unsigned long readInterval = 900; // ms

Servo myServo;
bool actionActive = false;
bool readyToTrigger = true;         // only allow trigger when true (prevents immediate retrigger if gas stays high)
unsigned long actionStartTime = 0;
const unsigned long actionDuration = 10000UL; // 10 seconds

BlynkTimer timer;

void startAlarmAction() {
  // Move servo and activate low-trigger relay by changing pin to OUTPUT and pulling LOW
  myServo.write(90);                 // move servo to 90°
  pinMode(FAN_PIN, OUTPUT);          // actively drive pin
  digitalWrite(FAN_PIN, LOW);        // LOW triggers low-level relay
  actionStartTime = millis();
  actionActive = true;
  readyToTrigger = false;            // block retrigger until gas falls below threshold
  Blynk.logEvent("gas_alert", String("Gas detected!"));
  Serial.println("Action started: servo 90°, FAN_PIN -> OUTPUT LOW");
}

void stopAlarmAction() {
  // stop action: return servo, float the relay pin
  myServo.write(0);                  // return servo to 0°
  pinMode(FAN_PIN, INPUT);           // float the pin (high-Z) so relay input stops seeing driven LOW/HIGH
  actionActive = false;
  Serial.println("Action ended: servo 0°, FAN_PIN -> INPUT (floating)");
}

void readGasSensor() {
  int gasValue = analogRead(MQ6_ANALOG);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);

  Blynk.virtualWrite(V0, gasValue);

  // Trigger when value goes above threshold and we're allowed to trigger
  if (gasValue > threshold && readyToTrigger && !actionActive) {
    Serial.println("⚠️ Gas Detected!");
    startAlarmAction();
  }

  // If action is active, check duration
  if (actionActive && (millis() - actionStartTime >= actionDuration)) {
    stopAlarmAction();
    // do not set readyToTrigger true here — wait until gas drops below threshold
  }

  // Allow retrigger only when gas falls back below threshold
  if (!readyToTrigger && !actionActive && gasValue <= threshold) {
    readyToTrigger = true;
    Serial.println("Gas level OK — ready for next trigger.");
  }
}

// Control threshold from Blynk slider
BLYNK_WRITE(V1) {
  threshold = param.asInt();
  Serial.print("Threshold set to: ");
  Serial.println(threshold);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(MQ6_ANALOG, INPUT);
  
  // Start with FAN_PIN floating (high-impedance). Relay will not be actively driven.
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);
  // Servo setup
  myServo.attach(SERVO_PIN);
  myServo.write(0);       // Start servo at 0°

  Serial.println("Warming up sensor...");
  delay(20000); // 20 s preheat
  Serial.println("Connecting...");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect();

  timer.setInterval(readInterval, readGasSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
