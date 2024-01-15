#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address for the LCD
#define I2C_ADDR 0x27

// Define analog pin numbers for sensors
const int frontSensorPin = A1;
const int leftSensorPin = A0;
const int rightSensorPin = A2;

// Initialize the LCD with the I2C address
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

void setup() {
  // Start the serial communication
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16, 2);

  // Display initial message on the LCD
  lcd.print("Sensors:");

  // Set the cursor position for the sensor values
  lcd.setCursor(0, 1);
}

void loop() {
  // Read sensor values
  int frontSensorValue = analogRead(frontSensorPin);
  int leftSensorValue = analogRead(leftSensorPin);
  int rightSensorValue = analogRead(rightSensorPin);

  // Clear the line before printing new values
  lcd.print("                ");

  // Print sensor values to the LCD
  lcd.setCursor(0, 1);
  lcd.print("F:");
  lcd.print(frontSensorValue);
  lcd.print(" L:");
  lcd.print(leftSensorValue);
  lcd.print(" R:");
  lcd.print(rightSensorValue);

  // Add a delay for better readability on the LCD
  delay(1000);
}
