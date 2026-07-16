#include <AccelStepper.h>


// ==============================
// BUTTON INPUTS
// ==============================

#define BTN_UP       1
#define BTN_DOWN     2
#define BTN_LEFT     3
#define BTN_RIGHT    42


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

  // A4988 enable is active LOW
  digitalWrite(ENABLE_PIN, LOW);



  // Motor configuration

  XMotor.setMaxSpeed(MAX_SPEED);
  YMotor.setMaxSpeed(MAX_SPEED);


  XMotor.setAcceleration(ACCELERATION);
  YMotor.setAcceleration(ACCELERATION);



  Serial.println("XY Plotter Ready");
}



// ==============================
// MAIN LOOP
// ==============================

void loop()
{

  int xMovement = 0;
  int yMovement = 0;



  // =====================
  // READ BUTTONS
  // =====================


  if(!digitalRead(BTN_RIGHT))
  {
    xMovement = MAX_SPEED;
  }


  if(!digitalRead(BTN_LEFT))
  {
    xMovement = -MAX_SPEED;
  }



  if(!digitalRead(BTN_UP))
  {
    yMovement = MAX_SPEED;
  }


  if(!digitalRead(BTN_DOWN))
  {
    yMovement = -MAX_SPEED;
  }



  // =====================
  // COMMAND MOTORS
  // =====================

  XMotor.setSpeed(xMovement);
  YMotor.setSpeed(yMovement);



  // Must constantly run

  XMotor.runSpeed();
  YMotor.runSpeed();

}