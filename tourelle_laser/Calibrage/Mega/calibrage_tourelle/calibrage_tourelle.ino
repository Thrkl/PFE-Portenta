#include <Servo.h>
// Script servant à contrôler les servomoteurs durant la phase de calibrage de la tourelle
//  Le script OpenMV sur la portenta affiche à la caméra des croix dont les coordonnées sont connues,
//    ce script permet de contrôler les servos avec le joystick pour viser cette croix et 
//    appuyer sur le joystick pour récupérer les angles actuels des servos afin de les sauvegarder comme données de calibrage.

// Ce script gère le contrôle des servos et l'affichage des angles sous appui du bouton.
//  Il peut aussi, avec quelques modifications recevoir en UART de la Portenta les coordonnées de la croix à viser mais ceci n'est pas activé.

int joystick_x = A5;
int joystick_y = A1;
int SW = 12;

int x = 0;
int y = 0;

float angle1 = 0;
float angle2 = 0;
float angletemp1 = 0;
float angletemp2 = 0;

int pin_servo1 = 9;
int pin_servo2 = 10;

Servo servo1;
Servo servo2;

int xTAG=0,yTAG=0; //Coordonnées de la croix à viser de 0 à 250 (non activé)

void setup() {
  //Initialisation des servos (et UART mais non utilisé)
  Serial.begin(9600);
  servo1.attach(pin_servo1);
  servo2.attach(pin_servo2);
  pinMode (SW, INPUT_PULLUP);

  //resetServos();
}

void loop() {
  // put your main code here, to run repeatedly:

  readJoystick();
  controlServos();
 // printServos();
  Print_Switch();
  delay(100);  // delai moyen, sert à contrôler la vitesse des servo

  //Recevoir_xy();   // Réception des coordonnées de la croix (non activé)
  Print_Switch();
  
}

void readJoystick(){

  x = analogRead(joystick_x);
  y = analogRead(joystick_y);
  
}

void printJoystick(){
  
  Serial.print("joystick_x : ");
  Serial.print(x);
  Serial.print(", joystick_y : ");
  Serial.println(y);
  
}

void resetServos () {

  angle1 = 90;
  angle2 = 90;
  servo1.write(angle1);
  servo2.write(angle2);
  
}

void controlServos(){
//Méthode pour contrôler l'angle des servos avec le joystick
  if(x>1000 && angle1<=186){
    angle1 += 1;
  } else if (x<100 && angle1>=-3){
    angle1 -= 1;
  }

  if(y>1000 && angle2<=186){
    angle2 += 1;
  } else if (y<100 && angle2>=-3){
    angle2 -= 1;
  }
  servo1.write(angle1);
  servo2.write(angle2);
  
}

void printServos(){

  Serial.print("angle1 : ");
  Serial.print(angle1);
  Serial.print(", angle2 : ");
  Serial.println(angle2);
  
}

boolean Print_Switch(){ // retourne TRUE si le switch est appuyé, FALSE sinon
  if(digitalRead(SW)==0){
    printServos();
    Print_xy();
    return true;
  }
  else{
    return false;
  }
  
}

void Print_xy(){
    Serial.print("xTAG = ");
    Serial.println(xTAG);
    Serial.print("yTAG = ");
    Serial.println(yTAG);
    Serial.println();
}

//On peut décider de recevoir les coordonnées de la croix à viser sur la mega pour faciliter le calibrage
void Recevoir_xy(){
  if (Serial.available()>0){
    xTAG=Serial.read();
  }  
  if (Serial.available()>0){
    yTAG=Serial.read();
  }
}
