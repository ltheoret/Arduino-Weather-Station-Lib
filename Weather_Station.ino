#include "Weather_Lib.h"

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN  2         // Pin which is connected to the DHT sensor.
#define DHTTYPE DHT22     // DHT 22 (AM2302)

#define BACKLIGHT_PIN     13

#define ALTITUDE 735.0 //Station altitude in meters

int IsOn = 0;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Adafruit_BMP280 bme; // I2C

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

void setup() {
  Serial.begin(9600);
  lcd.init();
  //Print a message to the LCD
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello World!");
  lcd.setCursor(0,1);
  lcd.print(" By Luc Theoret");
  delay(1000);
  lcd.setCursor(0,2);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.print("  BMP280 test");

  if (!bme.begin()) {
    lcd.setCursor(0,0);
    lcd.print("Could not find a");
    lcd.setCursor(0,1);
    lcd.print("valid BMP280 sen");
    while(1);
  }

  // Initialize the DHT sensor
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,2);
  lcd.print("                ");
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  float BMPTemp, BMPPress, DHTTemp, DHTRH;
  delay(delayMS);
  BMPTemp = bme.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.setCursor(3,0);
  lcd.print(BMPTemp);
  lcd.setCursor(9,0);
  lcd.print("*C");

  BMPPress = bme.readPressure();
  lcd.setCursor(0,1);
  lcd.print("P:");
  lcd.setCursor(3,1);
  lcd.print(BMPPress / 3389.39);
  lcd.setCursor(9,1);
  lcd.print("in-Hg");

  Serial.print("temp: ");
  Serial.print(BMPTemp);
  Serial.println(" *C");
  Serial.print("Saturated Vapour Pressure: ");
  Serial.print( SaturatedVapourPressure(BMPTemp));
  Serial.println(" mb");

  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.setCursor(0,20);
    lcd.print("Error reading temperature!");
  }
  else {
    DHTTemp = event.temperature;
    Serial.print("Temperature: ");
    Serial.print(DHTTemp);
    Serial.print(" *C or ");
    Serial.print( DegCtoDegF(DHTTemp) );
    Serial.println ( " *F");
    lcd.setCursor(0,2);
    lcd.print("T:");
    lcd.setCursor(3,2);
    lcd.print(DHTTemp);
    lcd.setCursor(9,2);
    lcd.print("*C");
  }

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.setCursor(0,3);
    lcd.print("Error reading humidity!");
  }
  else {
    DHTRH = event.relative_humidity;
    Serial.print("Humidity: ");
    Serial.print(DHTRH);
    Serial.println("%");
    lcd.setCursor(0,3);
    lcd.print("RH:");
    lcd.setCursor(4,3);
    lcd.print(DHTRH);
    lcd.setCursor(10,3);
    lcd.print("%");
  }
  Serial.print("Dew Point: ");
  Serial.print(DewPoint(DHTTemp, DHTRH));
  Serial.println(" *C");
 
  Serial.print("Actual Vapour Pressure: ");
  Serial.print(ActualVapourPressure(DHTRH, DHTTemp));
  Serial.println(" mb");
  Serial.print("Hunidex: ");
  Serial.print(Humidex(DHTTemp, DHTRH));
  // Serial.print(Humidex(30, 15));
  Serial.println(" *C");
  
  Serial.println("");
  if (IsOn != 0)
  {
    digitalWrite(LED_BUILTIN, LOW);
    IsOn = 0;
  }
  
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    IsOn = 1;
  }
}
