/*
DHT 11 on LCD
The goal of this program is to use a DHT to measure the temperature/humidity
 and display it on the LCD screen. The main theme is to get used to new libraries
*/
#include <DHT.h> //adding the library code of the DHT to this code
#include <DHT_U.h> //adding the library code of the DHT to this code

#define DHTPIN 8     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11, The type of sensor that can be chosen 

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

#include <LiquidCrystal.h>  //adding the library code of the LCD to this code
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 //all the pin locations fro the LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
//initialize the library to the pin numbers to the LCD
byte newChar[8] = {  //this is the setup for the symbol to the lcd, the degree symbol
  0b01100,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  dht.begin();// Initialize device.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);// Print humidity sensor details.
  delayMS = sensor.min_delay / 1000;
  // Set delay between sensor readings based on sensor details.
lcd.begin(16,2); // setting the peramiters for how big the LCD screen is
lcd.createChar(0,newChar); //this is what will creat the ohm symbol
}
void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.setCursor(0,0); 
    //is the location of where you will start, (0,0) is the first row begening of the screen
    lcd.print("Temp:"); //this will print the word "bit=" in the LCD screen
    lcd.print(event.temperature); 
    //this will print the value of the potentiometer on the LCD screen
    lcd.write((byte)0); //this will print the ohm symbol on the LCD screen
  }
  dht.humidity().getEvent(&event);// Get humidity event and print its value.
  
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(0,1); 
    //is the location of where you will start, (0,1) is the second row begening of the screen
    lcd.print("Humi:"); //this will print the word "volt=" in the LCD screen
    lcd.print(event.relative_humidity); //this will print the voltage value on the LDC screen
    lcd.print("%");
  }
}
