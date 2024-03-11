#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// Definiere die I²C-Adresse des Displays
#define I2C_ADDR    0x27
// Definiere die Anzahl der Spalten und Zeilen des Displays
#define LCD_COLUMNS 16
#define LCD_ROWS    2

// Erzeuge ein LiquidCrystal_I2C-Objekt
LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);

// Definiere die Pins für die IR-Sensoren
const int centerIR = A0;
const int rightIR = A1;
const int leftIR = A2;

void setup() {
  // Initialisiere das LCD-Display
  lcd.init();
  // Aktiviere die Hintergrundbeleuchtung des Displays
  lcd.backlight();
}

void loop() {
  // Deklariere Variablen für die Rohwerte und die neuen Werte der IR-Sensoren
  uint16_t ir_sensor_front_raw, ir_sensor_right_raw, ir_sensor_left_raw;
  uint16_t ir_sensor_front_new, ir_sensor_right_new, ir_sensor_left_new;

  // Lese den Rohwert des vorderen IR-Sensors
  ir_sensor_front_raw = analogRead(centerIR);
  // Berechne den neuen Wert für den vorderen IR-Sensor
  ir_sensor_front_new = (uint16_t) (16256 / (ir_sensor_front_raw - 22.8)) - 8;
  // Begrenze den neuen Wert für den vorderen IR-Sensor auf einen Bereich zwischen 19 und 151
  if(ir_sensor_front_new > 150)
    ir_sensor_front_new = 151;
  else if(ir_sensor_front_new < 20)
    ir_sensor_front_new = 19;

  // Lese den Rohwert des rechten IR-Sensors
  ir_sensor_right_raw = analogRead(rightIR);
  // Berechne den neuen Wert für den rechten IR-Sensor
  ir_sensor_right_new = (uint16_t) (5754.24 / (ir_sensor_right_raw - 11.44)) - 4;
  // Begrenze den neuen Wert für den rechten IR-Sensor auf einen Bereich zwischen 9 und 81
  if(ir_sensor_right_new > 80)
    ir_sensor_right_new = 81;
  else if(ir_sensor_right_new < 10)
    ir_sensor_right_new = 9;

  // Lese den Rohwert des linken IR-Sensors
  ir_sensor_left_raw = analogRead(leftIR);
  // Berechne den neuen Wert für den linken IR-Sensor
  ir_sensor_left_new = (uint16_t) (5754.24 / (ir_sensor_left_raw - 11.44)) - 4;
  // Begrenze den neuen Wert für den linken IR-Sensor auf einen Bereich zwischen 9 und 81
  if(ir_sensor_left_new > 80)
    ir_sensor_left_new = 81;
  else if(ir_sensor_left_new < 10)
    ir_sensor_left_new = 9;

  // Ausgabe der Werte auf dem I²C-Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("F: ");
  lcd.print(ir_sensor_front_new);
  lcd.setCursor(0, 1);
  lcd.print("R: ");
  lcd.print(ir_sensor_right_new);
  lcd.setCursor(10, 1);
  lcd.print("L: ");
  lcd.print(ir_sensor_left_new);

  // Verzögerung für 100 Millisekunden, bevor der Schleifendurchlauf erneut beginnt
  delay(100);
}
