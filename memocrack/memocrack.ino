int azul = 13;
int verde = 12;
int amarillo = 11;
int rojo = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("escribale mijo");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
  int ip = Serial.parseInt();
  if (ip == 1 ){
    digitalWrite(azul, HIGH);
    delay(500);
    digitalWrite(azul,LOW);
    delay(500);
    Serial.println("red");
  }
  else if(ip == 2){
    digitalWrite(azul, HIGH);
    digitalWrite(verde, HIGH);
    delay(500);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
    delay(500);
    Serial.println("gateway");
  }
  else if(ip == 3){
    digitalWrite(azul, HIGH);
    digitalWrite(verde, HIGH);
    digitalWrite(amarillo, HIGH);
    delay(500);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
    digitalWrite(amarillo,LOW);
    delay(500);
    Serial.println("dispositivo");
  }
  else if(ip == 4){
    digitalWrite(azul, HIGH);
    digitalWrite(verde, HIGH);
    digitalWrite(amarillo, HIGH);
    digitalWrite(rojo, HIGH);
    delay(500);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
    digitalWrite(amarillo,LOW);
    digitalWrite(rojo,LOW);
    delay(500);
    Serial.println("broadcast");
  }
  }
  delay(500);
}
