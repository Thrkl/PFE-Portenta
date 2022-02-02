#include <Servo.h>
// Script qui reçoit les coordonnées de la cible envoyées par la Portenta
//  calcule l'ordre en angle à envoyer au servos et commande les servos.

// X : [ 1.14730671e-08 -4.27168815e-06  3.29982742e-04 -2.95334824e-01  1.24962198e+02] 1er calibrage, 1M50
// Y : [-6.47433714e-09  2.12844467e-07  6.04274189e-04  2.01742563e-01  5.29448454e+01]

// x : [ 3.24455563e-08 -1.36495527e-05  1.80801623e-03 -4.02306247e-01  1.32552893e+02] 2eme calibrage, 3M50
// y : [-4.02779748e-08  1.79546215e-05 -2.49648199e-03  3.99592025e-01  4.26138485e+01]

//Coefficients des polynômes issus de la régression polynôme (degré 4) avec les données du 2ème calibrage
double x4 = 3.24455563e-08;
double x3 = -1.36495527e-05;
double x2 = 1.80801623e-03;
double x1 = -4.02306247e-01;
double x0 = 1.32552893e+02;

double y4 = -4.02779748e-08;
double y3 = 1.79546215e-05;
double y2 = -2.49648199e-03;
double y1 = 3.99592025e-01;
double y0 = 4.26138485e+01;

int joystick_x = A5;
int joystick_y = A1;

int angleX=0;
int angleY=0;

int coordX = 0;
int coordY = 0;

float angle1 = 0;
float angle2 = 0;
float angletemp1 = 0;
float angletemp2 = 0;

int pin_servo1 = 9;
int pin_servo2 = 10;

Servo servo1;
Servo servo2;

int xTAG=0,yTAG=0; //Coordonnées reçues de la Portenta de 0 à 250 

// Communication UART
int UART_pin = 18;

void setup() {
  //Initialisation de l'UART et des servos
  Serial.begin(9600);
  servo1.attach(pin_servo1);
  servo2.attach(pin_servo2);

  resetServos();
}

void loop() {
  
  Recevoir_coord();  
  CalculPolynome();
  PiloterServos(); 
}

void resetServos () {

  angle1 = 87;
  angle2 = 177;
  servo1.write(angle1);
  servo2.write(angle2);
  
}

void Recevoir_coord(){
  //Réception des coordonnées dès qu'elles arrivent (elles arrivent toujours par deux, x puis y)
  while(!(Serial.available()>1)){
  }
  coordX=Serial.read();
  coordY=Serial.read();  
}

void CalculPolynome(){
  //Calcul des polynômes pour obtenir l'angle à envoyer aux servos
  angleX = (((coordX*x4+x3)*coordX+x2)*coordX+x1)*coordX+x0;
  angleY = (((coordY*y4+y3)*coordY+y2)*coordY+y1)*coordY+y0;
}

void PiloterServos(){
  servo1.write(angleX);
  servo2.write(angleY);
}
