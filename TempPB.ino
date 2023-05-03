/*
DHT 11 on LCD with PB
The goal of this program is to measure the temperature with the DHT and display it on to an 
LCD screen. Then use a push button to change between Celsius, Fahrenheit and humidity. Things 
to use are push buttons and use a debouncer, the LCD library and DHT library   
*/
#include <DHT.h> //adding the library code of the DHT to this code
#include <DHT_U.h> //adding the library code of the DHT to this code

#define DHTPIN 8     // Digital pin connected to the DHT sensor 
#define DHTTYPE    DHT11     // DHT 11, The type of sensor that can be chosen 

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

#include <LiquidCrystal.h>  //adding the library code of the LCD to this code
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //all the pin locations fro the LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //initialize the library to the pin numbers to the LCD
byte newChar[8] = { //this is the setup for the symbol to the lcd, the degree symbol
  0b01100,
  0b10010,
  0b01100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

int pushButton=9; //push buttons pin location
int buttonState;  // making the buttonstate a intiger
int lastbuttonstate; // making the lastbuttonstate a intiger
int buttonCount=0;   //location of pin number for Push button

void setup() {
 
pinMode(pushButton, INPUT_PULLUP);  //making it so that the push button is an input
dht.begin();// Initialize device.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);// Print humidity sensor details.
  delayMS = sensor.min_delay / 10000;// Set delay between sensor readings based on sensor details.
lcd.begin(16,2); // setting the peramiters for how big the LCD screen is
lcd.createChar(0,newChar); //this is what will creat the ohm symbol
}
void loop() {
lastbuttonstate=buttonState;
buttonState =digitalRead(pushButton); //Reading the pushbutton from its pin and moving it to a button state

if(lastbuttonstate==1 && buttonState==0){ //This is to make a push button to make sre it does not bounce
  buttonCount=buttonCount+1;
if(buttonCount>3){
   buttonCount=0; 
 }
}  
delay(delayMS);// Delay between measurements.
sensors_event_t event;// Get temperature event and print its value.
dht.temperature().getEvent(&event);
float Fahr = ((event.temperature*9/5)+32); // claculation to turn the DHT value to fahrenheit

if(buttonCount==1){
    lcd.clear(); //clearing everything on LCD screen
    lcd.setCursor(0,0); //is the location of where you will start, (0,0) is the first row begening of the screen
    lcd.print("Temp:"); //this will print the word "bit=" in the LCD screen
    lcd.print(event.temperature); //this will print the value of the DHT on the LCD screen
    lcd.write((byte)0); //this will print the degree symbol on the LCD screen
    lcd.print("C"); //this will print the word "C" for celsius symbol in the LCD screen  
}
else if(buttonCount==2){
    lcd.clear(); //clearing everything on LCD screen
    lcd.setCursor(0,0); //is the location of where you will start, (0,0) is the first row begening of the screen
    lcd.print("Temp:"); //this will print the word "Temp=" in the LCD screen  
    lcd.print(Fahr); //this will print the value of DHT turned to fahrenheit on the LCD screen
    lcd.write((byte)0); //this will print the ohm symbol on the LCD screen
    lcd.print("F"); //this will print the word "F" for fahrenheit symbol in the LCD screen    
}
 else if(buttonCount==3){
  lcd.clear(); //clearing everything on LCD screen
  lcd.setCursor(0,0); //is the location of where you will start, (0,1) is the second row begening of the screen
  lcd.print("Humi:"); //this will print the word "Humi=" in the LCD screen
  lcd.print(event.relative_humidity); //this will print the humidity value on the LDC screen
  lcd.print("%"); // printing the pertsent symbol
   
 }
}

          
