#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_PH.h>
#include <GravityTDS.h>
#include <GravityDO.h>

// konfigurasi pin
#define ONE_WIRE_BUS 5  // DS18B20 data pin
#define PH_SENSOR_PIN A0
#define TURBIDITY_SENSOR_PIN A1
#define DO_SENSOR_PIN A2

// konfigurasi OLED display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// pengaturan sensor suhu DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Pengaturan sensor pH
DFRobot_PH ph;

// Pengaturan sensor Turbidity
int turbidityValue = 0;

// Pengaturan sensor Dissolved Oxygen
GravityTDS gravityTds;
GravityDO gravityDO;

void setup() {
  Serial.begin(115200);

  // Inisialisasi OLED display
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  // Inisialisasi sensor
  sensors.begin();
  ph.begin();
  gravityTds.begin();
  gravityDO.begin();

  display.clearDisplay();
  display.display();
}

void loop() {
  // membaca suhu air dari DS18B20
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // membaca pH
  float pHValue = ph.readPH();

  // membaca turbidity
  int turbidityValue = analogRead(TURBIDITY_SENSOR_PIN);

  // membaca dissolved oxygen and salinity
  float dissolvedOxygen = gravityDO.readDO();
  float salinity = gravityDO.readSalinity();

  // menampilkan hasil monitoring pada layar OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print(F("Temp: "));
  display.print(temperature);
  display.println(F(" C"));

  display.print(F("pH: "));
  display.println(pHValue);

  display.print(F("Turbidity: "));
  display.println(turbidityValue);

  display.print(F("DO: "));
  display.print(dissolvedOxygen);
  display.println(F(" mg/L"));

  display.print(F("Salinity: "));
  display.print(salinity);
  display.println(F(" ppt"));

  display.display();

  delay(5000); // Update setiap 5000 milisekon (5 detik, opsional dan dapat diubah)
}
