#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte BUTTON_PIN = 7;

int dieValue = 0; //Die value
int rollCount = 0; //Tracks number of rolls
int secret = 0; //Secret for checksum function
int checksum = 0; //Checksum anti-cheat method

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");
  pinMode(BUTTON_PIN, INPUT_PULLUP); //Uses built in pullup resistor
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);


//EEPROM.write(0, 58 >> 8);
//EEPROM.write(1, 58 & 0xFF);

secret = (EEPROM.read(0) << 8) + EEPROM.read(1);

Serial.println(secret);
delay(1000);
randomSeed(analogRead(A0));

display.clearDisplay();
display.setTextSize(3);
display.setTextColor(SSD1306_WHITE);
display.setCursor(20, 7);
display.print("READY");
display.display();

}

void loop() {

if (digitalRead(BUTTON_PIN) == LOW) {
Serial.println("Rolling...");
rollCount++;
dieValue = random(1, 21);
Serial.print("Die value: ");
Serial.println(dieValue);

checksum = ((dieValue+secret)*10)%(rollCount*3)+dieValue;
Serial.print("Checksum: ");
Serial.println(checksum);
display.clearDisplay();

// Draw square die
display.drawRect(2, 2, 50, 26, SSD1306_WHITE);

//Draw rolled value
display.setTextSize(3); 
display.setTextColor(SSD1306_WHITE);
//Determine if rolled value is 1 or 2 digits and set possition to start drawing
if (dieValue<10){
  display.setCursor(22, 5);
}
else {
  display.setCursor(11, 5);
}

display.print(dieValue);


//Draw roll counter and checksum
display.setTextSize(1);
display.setCursor(54, 2);
display.print("Roll #");
display.setCursor(93, 2);
display.print(rollCount);
display.setCursor(54, 12);
display.print("Chksum: ");
display.setCursor(98, 12);
display.print(checksum);

//Write to display
display.display();

//Pause while button is still held down
do {
  delay(200);
} while (digitalRead(BUTTON_PIN) == LOW);    
}
}
