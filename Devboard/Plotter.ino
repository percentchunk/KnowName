#include <AccelStepper.h>


// ==============================
// BUTTON INPUTS
// ==============================

#define BTN_UP       1
#define BTN_DOWN     2
#define BTN_LEFT     42
#define BTN_RIGHT    41


// ==============================
// A4988 X DRIVER
// ==============================

#define X_STEP_PIN   4
#define X_DIR_PIN    5


// ==============================
// A4988 Y DRIVER
// ==============================

#define Y_STEP_PIN   6
#define Y_DIR_PIN    7


// ==============================
// DRIVER ENABLE
// ==============================

#define ENABLE_PIN   8



// ==============================
// MOTION SETTINGS
// ==============================

#define MAX_SPEED        1000
#define ACCELERATION     500



// ==============================
// STEPS TO COORDINATE
// ==============================

// Change this depending on your motor setup
// Example: 200 step motor with 16x microstepping = 3200 steps/rev

#define STEPS_PER_PIXEL  1



// ==============================
// CREATE STEPPERS
// ==============================

AccelStepper XMotor(
  AccelStepper::DRIVER,
  X_STEP_PIN,
  X_DIR_PIN
);


AccelStepper YMotor(
  AccelStepper::DRIVER,
  Y_STEP_PIN,
  Y_DIR_PIN
);



// ==============================
// SERIAL TIMER
// ==============================

unsigned long lastPrint = 0;



// ==============================
// SETUP
// ==============================

void setup()
{
  Serial.begin(115200);


  // Buttons

  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_LEFT, INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);



  // Enable drivers

  pinMode(ENABLE_PIN, OUTPUT);

  // A4988 enable active LOW
  digitalWrite(ENABLE_PIN, LOW);



  // Motor settings

  XMotor.setMaxSpeed(MAX_SPEED);
  YMotor.setMaxSpeed(MAX_SPEED);

  XMotor.setAcceleration(ACCELERATION);
  YMotor.setAcceleration(ACCELERATION);



  // Start at top left

  XMotor.setCurrentPosition(0);
  YMotor.setCurrentPosition(0);



  Serial.println("XY Plotter Ready");
  Serial.println("(0,0)");
}



// ==============================
// MAIN LOOP
// ==============================

void loop()
{

  int xSpeed = 0;
  int ySpeed = 0;



  // =====================
  // BUTTON INPUT
  // =====================


  // Right = X increases

  if(!digitalRead(BTN_RIGHT))
  {
    xSpeed = MAX_SPEED;
  }


  // Left = X decreases

  if(!digitalRead(BTN_LEFT))
  {
    xSpeed = -MAX_SPEED;
  }



  // Down = Y increases

  if(!digitalRead(BTN_DOWN))
  {
    ySpeed = MAX_SPEED;
  }


  // Up = Y decreases

  if(!digitalRead(BTN_UP))
  {
    ySpeed = -MAX_SPEED;
  }



  // =====================
  // MOTOR CONTROL
  // =====================

  XMotor.setSpeed(xSpeed);
  YMotor.setSpeed(ySpeed);


  XMotor.runSpeed();
  YMotor.runSpeed();




  // =====================
  // OUTPUT COORDINATES
  // =====================

  if(millis() - lastPrint > 200)
  {

    long xCoordinate = XMotor.currentPosition() / STEPS_PER_PIXEL;
    long yCoordinate = YMotor.currentPosition() / STEPS_PER_PIXEL;


    Serial.print("(");
    Serial.print(xCoordinate);
    Serial.print(",");
    Serial.print(yCoordinate);
    Serial.println(")");



    lastPrint = millis();

  }

}