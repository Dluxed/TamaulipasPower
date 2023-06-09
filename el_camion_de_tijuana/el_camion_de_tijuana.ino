void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    //Lee el serial y lo guarda 
    String input = Serial.readStringUntil('\n');
    String ipString = input.substring(0,input.indexOf('/'));
    String maskString = input.substring(input.indexOf('/')+1);

    //Procesa la ip
    int dotIndex = 0;
    int prevDotIndex = 0;
    int octetValue[4];
    
    uint32_t ip32bits = 0;
    for(int i=0; i<4; i++){
      dotIndex = ipString.indexOf('.', prevDotIndex); //busca punto a partir del punto anteriro
      String octet = ipString.substring(prevDotIndex, dotIndex);
      octetValue[i] = octet.toInt();
      
      Serial.println(octetValue[i]);
      prevDotIndex = dotIndex +1;
    
      if(i!=0){
        ip32bits = (ip32bits << 8) | octetValue[i];        
      }else{
        ip32bits = octetValue[i];
      }
    }
    
    int maskValue = maskString.toInt();    
    uint32_t mascara = printMask(maskValue); //Llama la funcion mascara
    
    printNetwork(mascara, ip32bits);
    
    }
  }

  uint32_t printMask(int maskLenght){
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
    return mascara; //regresa el arreglo 
  }

  void printNetwork(uint32_t mask, uint32_t ip){    
    byte network[4];
    

    Serial.print("La red es: ");
    for(int i = 0; i<4; i++){
      if(i!=0){
        Serial.print(".");
      }
      network[i] = (mask >> (3 - i)*8) & (ip >> (3 - i)*8);
      Serial.print(network[i]);  
    }
    
  }

