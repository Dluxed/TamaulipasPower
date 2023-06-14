int azul = 13;
int verde = 12;
int amarillo = 11;
int rojo = 10;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(rojo, OUTPUT);

}

void loop() {
  if(Serial.available()){
    //Lee el serial y lo guarda 
    String input = Serial.readStringUntil('\n');
    String ipString = input.substring(0,input.indexOf('/'));
    String maskString = input.substring(input.indexOf('/')+1);

    //Llama a los elementos de la address
    uint32_t ip = getIp(ipString);
    int maskValue = maskString.toInt();//Convierte string a entero
    uint32_t mascara = getMask(maskValue); //Llama la funcion mascara
    uint32_t network = getNetwork(mascara, ip); //Imprime la network
    
    //Muestra el tipo de direccion
    addressType(ip, network, mascara);
    /* NOTA: Debido al ciclo "while (Serial available)" el resultado se imprime
    hasta la siguiente iteracion del ciclo... pero las luces jalan bien 
    (☞ﾟヮﾟ)☞  */ 
    }
  }

  // ---------------//  IP  //----------------------
  uint32_t getIp (String ip) {
    int dotIndex = 0;
    int prevDotIndex = 0;
    int octetValue[4];
    uint32_t ip32bits = 0;
    for(int i=0; i<4; i++){
      dotIndex = ip.indexOf('.', prevDotIndex); //busca punto a partir del punto anteriro
      String octet = ip.substring(prevDotIndex, dotIndex);
      octetValue[i] = octet.toInt();
      
      Serial.println(octetValue[i]);
      prevDotIndex = dotIndex +1;
    
      //Guarda cada octeto en un entero de 32bits
      if(i!=0){ 
        ip32bits = (ip32bits << 8) | octetValue[i];        
      }else{
        ip32bits = octetValue[i];
      }
    }
    return ip32bits;  
  }

  // ---------------//  MASK  //----------------------
  uint32_t getMask(int maskLenght){
    uint32_t mascara = 0xFFFFFFFF; //valor hex
    mascara = mascara << (32 - maskLenght); //Recorre la diferencia (Bits utilizables)
    byte maskBytes[4];
    for (int i = 0; i < 4; i++){
      maskBytes[i] = (mascara >> ((3 - i)*8)) & 0xFF; //Guarda caada octeto
      if (i != 0 ) {//Punto intermedio
        Serial.print(".");
      }
      Serial.print(maskBytes[i]); //Imprime el octeto
    }
    Serial.println();  
    return mascara; //regresa la mascara 
  }
  
  // ---------------//  NETWORK  //-----------------------
  uint32_t getNetwork(uint32_t mask, uint32_t ip){    
    byte networkArr[4];
    uint32_t network;
    Serial.print("La red es: ");
    for(int i = 0; i<4; i++){
    //Hace el and de las dos direcciones recorriendose 8 bits cada ciclo excepto el primero
      networkArr[i] = (mask >> (3 - i)*8) & (ip >> (3 - i)*8);
      if(i!=0){
        Serial.print(".");
        network = (network << 8) | networkArr[i];
      }else{
        network = networkArr[i];
      }
      Serial.print(networkArr[i]); 
    }
    Serial.print("\n");
    return network;
  }

  // Analiza eel tipo de direccion basandose en el ultimo octeto
  void addressType(uint32_t ip, uint32_t network, uint32_t mask){
    byte lastOctet = ip;
    byte netOctet = network;
    byte maskOctet = mask;    
    
    // ---------- Detecta si es red ------------ 
    //Nota: Este segmento aun no funciona con subnets
    if( lastOctet == netOctet) {
      while(Serial.available() == false){
      digitalWrite(azul, HIGH);
    delay(300);
    digitalWrite(azul,LOW);
    digitalWrite(verde,LOW);
    digitalWrite(amarillo,LOW);
    digitalWrite(rojo,LOW);
    delay(300);
      }
      Serial.println("Es red"); 
      
      // ---------- Detecta si es gateway ------------ 
    }else if(lastOctet == netOctet + 1){
      while(Serial.available() == false){
      digitalWrite(azul, HIGH);
      digitalWrite(verde, HIGH);
      delay(300);
      digitalWrite(azul,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(amarillo,LOW);
      digitalWrite(rojo,LOW);
      delay(300);
      }
      Serial.println("Es gateway");
      
     // ---------- Detecta si es bradcast ------------ 
    }else if((lastOctet + 1) % (256 - maskOctet) == 0){
      while(Serial.available() == false){
      digitalWrite(azul, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, HIGH);
      digitalWrite(rojo, HIGH);
      delay(300);
      digitalWrite(azul,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(amarillo,LOW);
      digitalWrite(rojo,LOW);
      delay(300);
      }
      Serial.println("Es broadcast");
      
      // ---------- Detecta si es dispositivo ------------ 
    }else{
      while(Serial.available() == false){
      digitalWrite(azul, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(amarillo, HIGH);
      
      delay(300);
      digitalWrite(azul,LOW);
      digitalWrite(verde,LOW);
      digitalWrite(amarillo,LOW);
      digitalWrite(rojo,LOW);
      delay(300);
      }
      Serial.println("Es dispositivo");      
    }
  delay(300);
    }

