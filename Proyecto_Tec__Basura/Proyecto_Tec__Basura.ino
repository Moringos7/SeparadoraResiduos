#include <Servo.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#define TRIGGER_PIN  8
#define ECHO_PIN     9
#define MAX_DISTANCE 500
SoftwareSerial mySerial(11,12);
//Barrera
Servo servo_1;
//Latas 
Servo servo_2;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int valor_cambio = 5;

const int pinCny = A1;

const int pinWifi = A3;
const int pinServo1 = 4;
const int pinServo2 = 6;
const int pinInductivo = 5;
const int pinBuzzer = 20;
const int pinRelevador = 3;
const int pinLedAbajo = 7;
const int TxBluetooth = 11;
const int RxBluetooth = 12;

//Variables de Latas y Botellas
int Lata = 0;
int Botella = 0;

void setup() {
  
  /////////// Pines Salidas \\\\\\\\\\\\
  pinMode(pinBuzzer,OUTPUT);
  pinMode(pinRelevador, OUTPUT);
  pinMode(pinLedAbajo,OUTPUT);
  //Configuración Servos
  servo_1.attach(pinServo1);
  servo_2.attach(pinServo2);

  /////////// Pines Entradas \\\\\\\\\\\\
  pinMode(pinCny, INPUT);
  pinMode(pinWifi,INPUT);
  pinMode(pinInductivo,INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  /////Interrupcion para cambio de luces \\\\\\
  attachInterrupt(pinWifi,CambioLuces,CHANGE);
  servo1(0);
  servo2(0);
  //////// Pines Bluetooth \\\\\\\\\\
  
}


boolean verificadorCny(){
  int contCNY = 0;
  while(true){
    if (sonar.ping_cm() < valor_cambio){
      if(contCNY == 3){
        return true;  
      }
    }else{
      return false;
    }
    contCNY += 1;
    delay(300);
  }
}
boolean verificadorInductivo(){
  int contInductivo = 0;
  while(true){
    if (digitalRead(pinInductivo) == HIGH){
      if(contInductivo == 3){
        return true;  
      }
    }else{
      return false;
    }
    contInductivo += 1;
    delay(500);
  }
}
void Envio_Bluetooth(){
  //Botellas
  char buf[10]=" ";
  char* formato="Botellas: %i";
  sprintf(buf, formato, Botella);
  mySerial.println(buf);

  //Latas
  char buf2[10]=" ";
  char* formato2="Latas %i";
  sprintf(buf2, formato2, Lata);
  mySerial.print(buf2);
  //Agregar Delay despues
  delay(1000);
}
void loop(){
  //Serial.println(sonar.ping_cm());
  //Serial.print("---");
  //Serial.println(pinCny);
  //Serial.print("WIFI: ");
  //Serial.println(analogRead(pinWifi));
  if(analogRead(pinWifi)< 20){
    digitalWrite(pinRelevador,HIGH);
  }else{
    digitalWrite(pinRelevador,LOW);
  }
  if(analogRead(pinCny) < 70){
    digitalWrite(pinLedAbajo,HIGH);
  }else{
    digitalWrite(pinLedAbajo,LOW);
  }
  if(sonar.ping_cm() < valor_cambio){
    Serial.println("Verificando CNY");
    Serial.print("  --");
    Serial.println(sonar.ping_cm());
    if(verificadorCny()){
          Serial.println("VerificandO Inductivo");
      if(verificadorInductivo()){  
        Serial.println("Es una lata");
        buzzer();
        servo2(50);
        delay(1000);
        buzzer();
        servo1(110);
        delay(2000);
        servo2(0);
        Lata++;
        Envio_Bluetooth();
      }else{
        Serial.println("Es una Botella");
        buzzer();
        servo1(110);
        delay(1000);
        Botella++;
        Envio_Bluetooth();
      }
      servo1(0);
      servo2(0);
    }
  }else{
    //Serial.println("Vacio");
  }
}
//Activación de Servo1
void servo1(int posicion){
  servo_1.write(posicion);
}

//Activación de Servo2
void servo2(int posicion){
  servo_2.write(posicion);
}

//Activación Buzzer
void buzzer(){
  //tone(pinBuzzer,1000);
  delay(300); 
 // noTone(pinBuzzer);
}

//Encendido y apagado de luces
//Relevador
void CambioLuces(){
  byte estado = digitalRead(pinWifi);
  digitalWrite(pinRelevador,estado);
}
