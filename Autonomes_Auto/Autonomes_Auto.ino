 
// Pin-Definitionen für Motoren
#define motor1pin1 8
#define motor1pin2 7
#define motor2pin1 5
#define motor2pin2 4

// Pin-Definitionen für IR-Sensoren
#define leftIR A0
#define centerIR A1
#define rightIR A2
#define frontIR A3

// PWM-Geschwindigkeitspin-Definitionen
#define pwmMotor1 9
#define pwmMotor2 6

// Pin-Definition für den Button
#define buttonPin 2

// Geschwindigkeitswerte für Motoren
#define baseSpeed 150
#define turnSpeed 100

volatile bool isRunning = false;

void setup() {
  // Initialisierung der seriellen Kommunikation
  Serial.begin(9600);

  // Motor-Pins als Ausgänge festlegen
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // PWM-Pins als Ausgänge festlegen
  pinMode(pwmMotor1, OUTPUT);
  pinMode(pwmMotor2, OUTPUT);

  // Button-Pin als Eingang mit Pull-Up-Widerstand
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach Interrupt für den Button
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleCar, FALLING);

  uint16_t ir_sensor_front_raw, ir_sensor_right_raw, ir_sensor_left_raw;
  uint16_t ir_sensor_front_new, ir_sensor_right_new, ir_sensor_left_new;

  ir_sensor_front_new = analogRead(frontIR);
  ir_sensor_front_new = (uint16_t) (16256 / (ir_sensor_front_raw +22.8)) - 8;

  if(ir_sensor_front_new > 150)
    ir_sensor_front_new = 151;
    else if(ir_sensor_front_new < 20)
    ir_sensor_front_new = 19;
}

void loop() {
  if (isRunning) {
    // Lesen Sie die Werte der IR-Sensoren
    int leftValue = analogRead(leftIR);
    int centerValue = analogRead(centerIR);
    int rightValue = analogRead(rightIR);
    int frontValue = analogRead(frontIR);

    

    // Mittenzentrierung (Mittenregelung)
    int average = (leftValue + centerValue + rightValue) / 3;
    int difference = centerValue - average;

    if (frontValue < 300)  {
      if (difference > 0) {
        // Zu weit links, nach rechts lenken
        turnRight();
      }     
      else {
        // Zu weit rechts, nach links lenken
        turnLeft();
      }
    }
}

// Funktionen für die Fahrzeugbewegungen
void driveForward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pwmMotor1, baseSpeed);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pwmMotor2, baseSpeed);
}

void turnLeft() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  analogWrite(pwmMotor1, turnSpeed);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pwmMotor2, turnSpeed);
}

void turnRight() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pwmMotor1, turnSpeed);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  analogWrite(pwmMotor2, turnSpeed);
}

// Funktion zum Anhalten beider Motoren
void stopMotors() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pwmMotor1, 0);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pwmMotor2, 0);
}

// Interrupt Service Routine für den Button (Starten/Stoppen)
void toggleCar() {
  isRunning = !isRunning;
  delay(1000); // Debouncing-Zeit
}
