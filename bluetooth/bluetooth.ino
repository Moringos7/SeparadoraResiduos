#include <SoftwareSerial.h>
SoftwareSerial mySerial(11,12);

int contador;
int contador2 = 20;

char stringM []= {};
int i;
int a;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
}
 
void loop()
{
  char buf[10]=" ";
  char* formato="Botellas: %i";
  sprintf(buf, formato, i);
  i++;
  mySerial.println(buf);

  //delay(1000);

  char buf2[10]=" ";
  char* formato2="Latas %i";
  sprintf(buf2, formato2, a);
  a+=5;
  mySerial.print(buf2);
  delay(1000);
}
