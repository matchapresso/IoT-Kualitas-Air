#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SimpleTimer.h>

char ssid[] = "POCO F4";
char pass[] = "12345678";

#define BLYNK_TEMPLATE_ID "TMPL6XYWmUcN3"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "H2Mfw1W--nUrvyYCC3dfAxGrtwyg76HT"

#define ONE_WIRE_BUS 14

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float Celsius = 0;
float Fahrenheit = 0;

BlynkTimer timer;

void temp() {
  sensors.requestTemperatures();
  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);
  Blynk.virtualWrite(V1, Celsius);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, temp);
}

void loop() {
  Blynk.run();
  timer.run();
}
