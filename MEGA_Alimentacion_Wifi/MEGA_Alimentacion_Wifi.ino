


void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  Serial.print("Hola");
}
void loop() {
  CambioLuces();
  //Serial.println(analogRead(A0));
  //delay(500);
}
void CambioLuces(){
  byte estado_luces = LOW;
  if(analogRead(A0) > 150){
    estado_luces = HIGH; 
  }else{
    estado_luces = LOW;
  }
  digitalWrite(13,estado_luces);
}

