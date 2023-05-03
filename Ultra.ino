/*
Ultrasonic on LCD
The reason for this program is to become comfortable with the ultrasonic 
sensor and its library. With the use of this sensor we shall measure 
and then calculate the distance with the help of the library.
Tried to use #include <Adafruit_Sensor.h>, but was too complicated because 
it was a library for all adafruit sensors and you needed to create 
your own functions
*/
#include <LiquidCrystal.h>  //adding the library code of the LCD to this code
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 //all the pin locations fro the LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 
//initialize the library to the pin numbers to the LCD
#include <NewPing.h> //adding the library of the ultrasonic to this code
#define TRIGGER_PIN 10  //the pin location 
#define ECHO_PIN 13 //the pin location 
#define MAX_DISTANCE 400 //will be the maximum distance
float distance; //maiking a value for distance
NewPing sonar (TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); 
//call the pins from the library

void setup() {
 lcd.begin(16,2); // setting the peramiters for how big the LCD screen is
}

void loop() {
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
  lcd.print(distance); //this will print the value of ultrasonic on the LCD screen
  lcd.print("cm"); //this will print the word "cm" in the LCD screen
  delay(500); //delay of half a sec
 }
}
