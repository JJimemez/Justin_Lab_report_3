/*
Ultrasonic on LCD with DHT 11
The purpose of this code is to bring together the power of different sensors to be able to 
get a more accurate reading of distance. The tools used in the code are the DHT 11 
temperature sensor, the ultrasonic sensor and lastly the LCD screen. The biggest struggle 
is to find the right library and the correct code to bring them all together.
*/
#include <DHT.h> //adding the library code of the DHT to this code
#include <DHT_U.h> //adding the library code of the DHT to this code
#include <NewPing.h> //adding the library of the ultrasonic to this code
#include <LiquidCrystal.h>  //adding the library code of the LCD to this code

#define DHTPIN 8     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11, The type of sensor that can be chosen 
#define TRIGGER_PIN 10  //the pin location 
#define ECHO_PIN 13 //the pin location 
#define MAX_DISTANCE 400 //will be the maximum distance

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

NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
//call the pins from the library

float distance; //maiking a value for distance
float newdistance; //maiking a newvalue for distance
float soundmath; //value for calculation 
//float soundcm; //value for calculation
//float humi;
//float temp;
//float duration;
//int iterations =5;

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

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
delay(delayMS);// Delay between measurements.
// Get temperature event and print its value.
sensors_event_t event;

newdistance= distance/(1+0.00016*event.temperature)+(0.00019*event.relative_humidity); 

if (isnan(event.temperature)) {
    lcd.print(F("Error reading temperature!"));
  }
  else {
    lcd.setCursor(0,1); 
    //is the location of where you will start, (0,0) is the first row begening of the screen
    lcd.print("T:"); //this will print the word "bit=" in the LCD screen
    lcd.print(event.temperature); 
    //this will print the value of the potentiometer on the LCD screen
    lcd.write((byte)0); //this will print the ohm symbol on the LCD screen
  }
  dht.humidity().getEvent(&event);// Get humidity event and print its value.
  
  if (isnan(event.relative_humidity)) {
    lcd.print(F("Error reading humidity!"));
  }
  else {
    lcd.setCursor(8,1); 
    //is the location of where you will start, (0,1) is the second row begening of the screen
    lcd.print("H:"); //this will print the word "volt=" in the LCD screen
    lcd.print(event.relative_humidity); //this will print the voltage value on the LDC screen
    lcd.print("%");
  }

distance = sonar.ping_cm();

if (distance >=400 && distance <=2){
  lcd.setCursor(0,0); 
  //is the location of where you will start, (0,0) is the first row begening of the screen
  lcd.print("out of range"); 
  //this will print the word "out of range" in the LCD screen
}
else{
  lcd.setCursor(0,0); 
  //is the location of where you will start, (0,0) is the first row begening of the screen
  lcd.print("D:");
  lcd.print(newdistance); //this will print the value of ultrasonic on the LCD screen
  lcd.print("cm"); //this will print the word "cm" in the LCD screen
  delay(500); //delay of half a sec
 }
}
