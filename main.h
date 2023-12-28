#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DFRobot_PH.h>

// OLED Configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// OneWire Configuration for DS18B20
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// pH Sensor Configuration
#define PH_SENSOR_PIN A0
DFRobot_PH ph;

// Dissolved Oxygen Sensor Configuration
#define DO_SENSOR_TX 4
#define DO_SENSOR_RX 3
SoftwareSerial mySerial(DO_SENSOR_RX, DO_SENSOR_TX);

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  // OLED Setup
  if(!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  
  // DS18B20 Setup
  sensors.begin();

  // pH Sensor Setup
  ph.begin();
  
  // Dissolved Oxygen Sensor Setup
  mySerial.print("O,cal\r\n");
}

void loop() {
  // Read DS18B20 temperature
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // Read pH value
  float phValue = ph.readPH();

  // Read Dissolved Oxygen
  mySerial.print("O,r\r\n");
  delay(1000);
  String doData = mySerial.readStringUntil('\r');
  float dissolvedOxygen = doData.toFloat();

  // Display readings on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(temperature);
  display.println(" C");

  display.print("pH: ");
  display.println(phValue);

  display.print("DO: ");
  display.print(dissolvedOxygen);
  display.println(" mg/L");

  display.display();

  delay(5000); // Adjust the delay according to your needs
}
