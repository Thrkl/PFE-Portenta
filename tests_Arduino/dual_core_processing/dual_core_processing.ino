//Exemple pour code exécuté par les deux coeurs en même temps
int led;
int delayTime;

void setup() {
  // put your setup code here, to run once:
  #ifdef CORE_CM7
    bootM4();
    led = LEDB;
    delayTime = 500;
  #endif

  #ifdef CORE_CM4
    led = LEDR;
    delayTime = 200;
  #endif

  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, LOW);
  delay(delayTime);
  digitalWrite(led, HIGH);
  delay(delayTime);
}
