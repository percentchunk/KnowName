#define VRX_PIN 1
#define VRY_PIN 2

void setup() {
  Serial.begin(115200);
}

void loop() {
  int x = analogRead(VRX_PIN);
  int y = analogRead(VRY_PIN);

  Serial.print("VRx: ");
  Serial.print(x);

  Serial.print(" | VRy: ");
  Serial.println(y);

  delay(100);
}