#include "DHT.h"
#define sensor A0
#define light_green 8
#define light_yellow 9
#define light_red 10
#define time_delay 150
#define DHTPIN A0
#define WelcomeCount 5

#define DHTTYPE DHT11

bool showWelcome = false;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(light_green, OUTPUT);
  pinMode(light_yellow, OUTPUT);
  pinMode(light_red, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}

void welcome() {
  for (int i = 0; i <= WelcomeCount; i++) {
    lights(LOW, LOW, HIGH);
    delay(time_delay);
    lights(LOW, HIGH, LOW);
    delay(time_delay);
    lights(HIGH, LOW, LOW);
    delay(time_delay);
    lights(LOW, LOW, LOW);
  }
}

void sensorTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  printTemperature();

  if (t < 32) {
    lights(LOW, LOW, HIGH);
  }
  else if (t > 32 && t < 38) {
    lights(LOW, HIGH, LOW);
  }

  else if (t > 38) {
    lights(HIGH, LOW, LOW);
  }
  delay(2000);

}

void lights(int red, int yellow, int green) {
  digitalWrite(light_red, red);
  digitalWrite(light_yellow, yellow);
  digitalWrite(light_green, green);
}

void printTemperature() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void loop() {
  if (!showWelcome) {
    welcome();
    showWelcome = true;
  }
  else {
    sensorTemperature();
  }
}
