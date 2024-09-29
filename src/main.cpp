// Declaración de librerías
#include <Arduino.h>
#include <SoftwareSerial.h>;


// Configura el puerto serial para el SIM GSM
SoftwareSerial SIM900(7, 8);

// VARIABLES QUE TOMAN LOS VALORES DE LAS ENTRADAS
unsigned char estado=0;
unsigned char estado1=0;
unsigned char estado2=0;
unsigned char estado3=0;
unsigned char estado4=0;
unsigned char estado5=0;
unsigned char estado6=0;
unsigned char estadoBAT=0;

// ENTRADAS
unsigned char entrada=0;
unsigned char entrada1=0;
unsigned char entrada2=0;
unsigned char entrada3=0;
unsigned char entrada4=0;
unsigned char entrada5=0;
unsigned char entrada6=0;
double Vbat;

// ASIGNACION DE PINES
unsigned char ent1=2;   // PIN2
unsigned char ent2=3;   // PIN3
unsigned char ent3=4;   // PIN4
unsigned char ent4=5;   // PIN5
unsigned char ent5=10;  // PIN10
unsigned char sal9=9;   // PIN9 Enciende al SIM900
unsigned char ent6=11;  // PIN11
unsigned char BAT=A1;   // PIN A1

// MENSAJES A ENVIAR
String outMessage="";
String outMessageF="";
String outMessageOK="";
String outMessage1F = "Falla freezer 1";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 1
String outMessage1OK = "Freezer 1 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 1 se encuenta ok
String outMessage2F = "Falla freezer 2";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 2
String outMessage2OK = "Freezer 2 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 2 se encuenta ok
String outMessage3F = "Falla freezer 3";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 3
String outMessage3OK = "Freezer 3 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 3 se encuenta ok
String outMessage4F = "Falla freezer 4";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 4
String outMessage4OK = "Freezer 4 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 4 se encuenta ok
String outMessage5F = "Falla freezer 5";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 5
String outMessage5OK = "Freezer 5 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 5 se encuenta ok
String outMessage6F = "Falla freezer 6";    // Variable que guarda los caracteres que envia el SIM GSM de falla del freezer 6
String outMessage6OK = "Freezer 6 ok";      // Variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 6 se encuenta ok
String outMessageOFF = "Sin energia";       // Variable que guarda los caracteres que envia el SIM GSM indicando que se corto la energia
String outMessageBAT = "BATERIA BAJA";      // Variable que guarda los caracteres que envia el SIM GSM indicando  bateria baja
String outMessageFUN = "FUNCIONANDO";       // Variable que indica que el equipo funciona en forma correcta

// TELEFONOS DE DESTINO
String destinationNumber = "";
String destinationNumber1 = "3406555888";   // número celular, telefónico de destino1.
String destinationNumber2 = "3415555700";   // número celular, telefónico de destino2.
String destinationNumber3 = "3413555771";   // número celular, telefónico de destino3. 
String destinationNumber4 = "3416555717";   // número celular, telefónico de destino4. 
String destinationNumber5 = "3415555692";   // número celular, telefónico de destino5.
String destinationNumber6 = "3415555692";   // número celular, telefónico de destino6.
String destinationNumber7 = "3415555692";   // número celular, telefónico de destino7.


// put function declarations here:
void mensaje_sms();

void analiza();


void setup() {
  Serial.begin(9600);   // Configura velocidad serial para el Arduino
  SIM900.begin(9600);   // Configura velocidad serial para el SIM
  delay(25000);         // Retardo para que encuentra a una RED

  // CONFIGURACION DE PINES
  pinMode(ent1,INPUT_PULLUP);
  pinMode(ent2,INPUT_PULLUP);
  pinMode(ent3,INPUT_PULLUP);
  pinMode(ent4,INPUT_PULLUP);
  pinMode(ent5,INPUT_PULLUP);
  pinMode(ent6,INPUT_PULLUP);
  pinMode(sal9,OUTPUT);
  pinMode(BAT,INPUT);

  // ENCENDIDO DEL SIM900
  digitalWrite(sal9,LOW);                   // Me aseguro de que este bajo por 1 segundo
  delay(1000);
  digitalWrite(sal9,HIGH);                  // Lo mantengo alto por 1 segundo
  delay(1000);
  digitalWrite(sal9,LOW);                   // Lo bajo
  delay(25000);
  delay(1000);
  SIM900.println("AT + CPIN = \"1234\"");   // Comando AT para introducir el PIN de la tarjeta
  delay(1000);

  // MENSAJE DE FUNCIONAMIENTO CORRECTO
  outMessage=outMessageFUN;
  destinationNumber=destinationNumber7;
  mensaje_sms();
  delay(1000);
}

void loop() {
  // Leo entrada 1 
  entrada = digitalRead(ent1);
  delay(100);
  estado= estado1;
  outMessageF =outMessage1F;
  outMessageOK=outMessage1OK;
  destinationNumber=destinationNumber1;
  analiza();
  estado1=estado;

  // Leo entrada 2
  entrada = digitalRead(ent2);
  delay(100);
  estado= estado2;
  outMessageF =outMessage2F;
  outMessageOK=outMessage2OK;
  destinationNumber=destinationNumber2;
  analiza();
  estado2=estado;

  // Leo entrada 3
  entrada = digitalRead(ent3);
  delay(100);
  estado= estado3;
  outMessageF =outMessage3F;
  outMessageOK=outMessage3OK;
  destinationNumber=destinationNumber3;
  analiza();
  estado3=estado;

  // Leo entrada 4
  entrada = digitalRead(ent4);
  delay(100);
  estado= estado4;
  outMessageF =outMessage4F;
  outMessageOK=outMessage4OK;
  destinationNumber=destinationNumber4;
  analiza();
  estado4=estado;

  // Leo entrada 5
  entrada = digitalRead(ent5);
  delay(100);
  estado= estado5;
  outMessageF =outMessage5F;
  outMessageOK=outMessage5OK;
  destinationNumber=destinationNumber5;
  analiza();
  estado5=estado;

  // Leo entrada 6
  entrada = digitalRead(ent6);
  delay(100);
  estado= estado6;
  outMessageF =outMessage6F;
  outMessageOK=outMessage6OK;
  destinationNumber=destinationNumber6;
  analiza();
  estado6=estado;

  // leo el estado de la bateria
  // Medición de la Tension
  for (int B = 0; B <= 499; B++) {
    Vbat = Vbat + analogRead(BAT); 
  }
  Vbat = Vbat / 500;
  Vbat= Vbat * 10 * 5 / 1024;           // Convertir a voltios
  Serial.print("Votaje de bateria");
  Serial.print(Vbat);
  if (Vbat < 11) {
    entrada = true;
    delay(100);
  }    
  else {
    entrada = false;
  }
  estado = estadoBAT;
  outMessageF = outMessageBAT;
  outMessageOK = outMessageBAT;
  destinationNumber = destinationNumber6;
  analiza();
  estadoBAT = estado;
}


// put function definitions here:
// Funcion para mandar mensaje de texto
void mensaje_sms() {
  SIM900.print("AT+CMGF=1\r");                                  // AT command to send SMS message
  delay(1000);
  SIM900.println("AT+CMGS= \"" + destinationNumber + "\"");     // recipient's mobile number, in international format
  delay(3000);
  SIM900.println(outMessage);                                   // message to send
  delay(3000);
  SIM900.println((char)26);                                     // End AT command with a ^Z, ASCII code 26 //Comando de finalizacion
  Serial.println((char)26);
  delay(100);
  SIM900.println();
  delay(25000);                                                 // Tiempo para que se envie el mensaje
  Serial.println("SMS sent successfully");
}

// Funcion que analiza si hay que mandar mensaje
void analiza() {
  if (entrada != estado) {
    if (entrada == true) {
      Serial.println(outMessageF);
      outMessage = outMessageF;
      mensaje_sms();
      estado = entrada;
    }
    else {
      Serial.println(outMessageOK);
      outMessage = outMessageOK;
      mensaje_sms();
      estado = entrada;
    }
  }
else {}  
}