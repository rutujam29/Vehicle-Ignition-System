#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial fingerSerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingerSerial);

int ignitionPin = 8; // Connected to relay or ignition

void setup() {
  pinMode(ignitionPin, OUTPUT);
  digitalWrite(ignitionPin, LOW); // Ignition off initially

  Serial.begin(9600);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Fingerprint sensor found!");
  } else {
    Serial.println("Fingerprint sensor not found :(");
    while (1);
  }
}

void loop() {
  Serial.println("Place finger on sensor...");
  int result = getFingerprintID();

  if (result == 1) {
    Serial.println("Access Granted - Starting Ignition");
    digitalWrite(ignitionPin, HIGH);
    delay(5000); // Simulate ignition on for 5 seconds
    digitalWrite(ignitionPin, LOW);
  } else {
    Serial.println("Access Denied");
    digitalWrite(ignitionPin, LOW);
  }

  delay(2000);
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return 0;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return 0;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return 0;

  // Found a match
  return 1;
}


//What extra Need:
//Arduino UNO or Nano

//R305 Fingerprint sensor

//Relay module (to simulate ignition)

//GPS module (optional, for extension)

//Adafruit Fingerprint Sensor Library