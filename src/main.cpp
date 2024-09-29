// Declaración de librerías
#include <Arduino.h>
#include <avr/wdt.h>
#include <SoftwareSerial.h>


// definiciones de variables y constantes
// variables de estado
unsigned char estado = 0;
unsigned char estado1 = 0;
unsigned char estado2 = 0;
unsigned char estado3 = 0;
unsigned char estado4 = 0;
unsigned char estado5 = 0;
unsigned char estado6 = 0;
unsigned char estadoBAT = 0;

// entradas
unsigned char entrada = 0;
unsigned char entrada1 = 0;
unsigned char entrada2 = 0;
unsigned char entrada3 = 0;
unsigned char entrada4 = 0;
unsigned char entrada5 = 0;
unsigned char entrada6 = 0;

// variables
SoftwareSerial SIM900(7, 8);        // Configura el puerto serial para el SIM GSM.
double Vbat;
double NETLIGHT = 1;
int senial = 0;
int dec = 0;
int uni = 0;
int senialf = 0;
String p = "";
char num;

// asignación de pines
unsigned char ent1 = 2;             // pin 02
unsigned char ent2 = 3;             // pin 03
unsigned char ent3 = 4;             // pin 04
unsigned char ent4 = 5;             // pin 05
unsigned char ent5 = 10;            // pin 10
unsigned char sal9 = 9;             // pin 09: enciende al SIM900
unsigned char ent6 = 11;            // pin 11
unsigned char LED = A0;             // pin A0: mide voltaje del led NetLight del SIM900
unsigned char BAT = A1;             // pin A1

// mensajes para enviar
String outMessage = "";
String outMessageF = "";
String outMessageOK = "";
String outMessage1F = "Falla freezer 1";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 1
String outMessage1OK = "Freezer 1 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 1 se encuenta ok
String outMessage2F = "Falla freezer 2";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 2
String outMessage2OK = "Freezer 2 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 2 se encuenta ok
String outMessage3F = "Falla freezer 3";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 3
String outMessage3OK = "Freezer 3 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 3 se encuenta ok
String outMessage4F = "Falla freezer 4";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 4
String outMessage4OK = "Freezer 4 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 4 se encuenta ok
String outMessage5F = "Falla freezer 5";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 5
String outMessage5OK = "Freezer 5 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 5 se encuenta ok
String outMessage6F = "Falla freezer 6";		              // variable que guarda los caracteres que envia el SIM GSM de falla del freezer 6
String outMessage6OK = "Freezer 6 ok";			              // variable que guarda los caracteres que envia el SIM GSM indicando que el freezer 6 se encuenta ok
String outMessageOFF = "Sin energia";	  		              // variable que guarda los caracteres que envia el SIM GSM indicando que se corto la energia
String outMessageBAT = "BATERIA BAJA";			              // variable que guarda los caracteres que envia el SIM GSM indicando  bateria baja
String outMessageFUN = "Funcionamiento normal!!!";		  	// variable que indica que el equipo funciona en forma correcta

// números de teléfonos de destino
String destinationNumber = "";
String destinationNumber1 = "3416550363";		// número celular, telefónico de destino1.
String destinationNumber2 = "3416555363";		// número celular, telefónico de destino2.
String destinationNumber3 = "3416555363";		// número celular, telefónico de destino3.
String destinationNumber4 = "3416555363";		// número celular, telefónico de destino4.
String destinationNumber5 = "3416555363";		// número celular, telefónico de destino5.
String destinationNumber6 = "3416555363";		// número celular, telefónico de destino6.
String destinationNumber7 = "3416555363";		// número celular, telefónico de destino7.

// variables para el watchdog
const unsigned long interval_wdt = 4000;	    // intervalo de tiempo de reset del watchdog (hacemos que sea 1/2 de WDTO=8000)
unsigned long previousMillis_wdt = 0;		      // valor millis antes del último reset del watchdog


// put function declarations here:
void check_wdt();

void delay_wdt(unsigned long);

bool sim900_onoff_check();

void sim900_on();

void sim900_reset();

void onoff_signal();

bool battery_check();

void mensaje_sms();

void nivelsenial();

void buscadorsenial();

void analiza();

void leer_entrada(char, unsigned char *, String, String, String);


void setup() {
  Serial.println("inicio de setup");
  wdt_disable();                                // deshabilita watchdog
  previousMillis_wdt = millis();                // registramos el valor millis
  wdt_enable(WDTO_8S);                          // habilita watchdog configurando 8s. como tiempo límite
  Serial.println("delay_wdt configurado");

  Serial.begin(9600);			                      // configura velocidad serial para el Arduino
  SIM900.begin(9600);			                      // configura velocidad serial para el SIM
  Serial.println('\r');
  Serial.println("puertos serie configurados");


  // configuración de pines
  pinMode(ent1,INPUT_PULLUP);
  pinMode(ent2,INPUT_PULLUP);
  pinMode(ent3,INPUT_PULLUP);
  pinMode(ent4,INPUT_PULLUP);
  pinMode(ent5,INPUT_PULLUP);
  pinMode(ent6,INPUT_PULLUP);
  pinMode(sal9,OUTPUT);
  pinMode(BAT,INPUT);
  Serial.println("pines configurados");

  // encendemos el sim900
  sim900_on();

  // enviamos mensaje avisando inicio correcto
  outMessage=outMessageFUN;
  destinationNumber=destinationNumber7;
  mensaje_sms();
  delay_wdt(1000);  
  Serial.println("fin de setup");
}

void loop() {
  Serial.println("inicio loop");

  // Leo entrada 1
  leer_entrada(digitalRead(ent1), &estado1, outMessage1F, outMessage1OK, destinationNumber1);

  // Leo entrada 2
  leer_entrada(digitalRead(ent2), &estado2, outMessage2F, outMessage2OK, destinationNumber2);

  // Leo entrada 3
  leer_entrada(digitalRead(ent3), &estado3, outMessage3F, outMessage3OK, destinationNumber3);

  // Leo entrada 4
  leer_entrada(digitalRead(ent4), &estado4, outMessage4F, outMessage4OK, destinationNumber4);

  // Leo entrada 5
  leer_entrada(digitalRead(ent5), &estado5, outMessage5F, outMessage5OK, destinationNumber5);

  // Leo entrada 6
  leer_entrada(digitalRead(ent6), &estado6, outMessage6F, outMessage6OK, destinationNumber6);

  // leo el estado de la bateria
  leer_entrada(battery_check(), &estadoBAT, outMessageBAT, outMessageFUN, destinationNumber7);

  delay_wdt(5000);
  buscadorsenial();
  Serial.println("fin loop");
}


// put function definitions here:
// función que analiza si hay que resetear el watchdog
void check_wdt() {
	unsigned long CurrentMillis = millis();
	if ((CurrentMillis - previousMillis_wdt) >= interval_wdt) {
		previousMillis_wdt = CurrentMillis;
		wdt_reset();
	}
}

// función similar a delay, pero resetea el watchdog cuando corresponde
void delay_wdt(unsigned long t) {
	unsigned long q = t/interval_wdt;
	unsigned long resto;
	if( q>=1 ) {		
		for (int i = 0; i < int(q); i++) {
    			delay(interval_wdt);
    			check_wdt();			
  		}
		resto = int((q - int(q)) * 100);
		delay(resto);
		check_wdt();
	}
	else {
		delay(t);
		check_wdt();
	}
}

// función de chequeo de estado del sim900 (on/off)
bool sim900_onoff_check() {
  delay_wdt(5000);
  while ( SIM900.available() > 0 ) SIM900.read();       // Limpia el buffer de entrada
  SIM900.println( "AT + CSQ" );                         // Comando AT para saber el nivel de señal
  delay_wdt(1000);
  if (SIM900.available() > 0) {                         // Cargo todos los caracteres en el string p
    return HIGH;    
  }
  else {
    return LOW;
  }
}

// función para encender el sim900
void sim900_on() {
  if(sim900_onoff_check()) {
    Serial.println("sim900 encendido, apagando...");
    onoff_signal();
    delay_wdt(1000);
  }
  Serial.println("sim900 apagado, encendiendo...");
  onoff_signal();
  Serial.println("sim900 encendido!!!");
}

// función para reiniciar el sim900
void sim900_reset() {
  sim900_on();
  Serial.println("sim900 reiniciado!");
}

// función que envía señal on/off al sim900
void onoff_signal() {
  delay_wdt(25000);
  digitalWrite(sal9,LOW);                       // me aseguro de que este bajo por 1 segundo
  delay_wdt(1000);
  digitalWrite(sal9,HIGH);                      // lo mantengo alto por 1 segundo
  delay_wdt(1000);
  digitalWrite(sal9,LOW);                       // lo bajo
  delay_wdt(25000);
  delay_wdt(1000);
  SIM900.println("AT + CPIN = \"1234\"");       // comando AT para introducir el PIN de la tarjeta
  delay_wdt(1000);
  Serial.println("señal on/off enviada!");
}

// función que chequea la tensión de la batería
bool battery_check() {
  for (int B = 0; B <= 499; B++) {
	  Vbat = Vbat + analogRead(BAT);
  }
  Vbat = Vbat / 500;
  Vbat = Vbat * 10 * 5 / 1024;                                    // Convertir a voltios.
  Serial.print("Votaje batería: ");
  Serial.println(Vbat);
  if(Vbat < 11) {
  	delay_wdt(100);
    return true;
  }   
  else {
	  return false;
  }
}

// Funcion para mandar mensaje de texto
void mensaje_sms() {
  buscadorsenial();
  delay_wdt(1000);
  SIM900.print("AT+CMGF=1\r");			                              // AT command to send SMS message
  delay_wdt(1000);
  SIM900.println("AT+CMGS= \"" + destinationNumber + "\"");	      // recipient's mobile number, in international format
  delay_wdt(3000);
  SIM900.println(outMessage);				                              // message to send
  delay_wdt(3000);
  SIM900.println((char)26);					                              // End AT command with a ^Z, ASCII code 26 //Comando de finalizacion
  Serial.println((char)26);
  delay_wdt(100);
  SIM900.println();
  delay_wdt(25000);									                              // Tiempo para que se envie el mensaje
  Serial.println("SMS enviado exitosamente!");
}

// función que mide el nivel de señal
void nivelsenial() {
  delay_wdt(5000);
  while (SIM900.available() > 0) SIM900.read();         // Limpia el buffer de entrada
  SIM900.println( "AT + CSQ" );                         // Comando AT para saber el nivel de señal
  delay_wdt(1000);
  senial = 0;
  senialf = 0;
  p="";                                                 // Pongo en 0 al string p
  if (SIM900.available() > 0) {                         // Cargo todos los caracteres en el string p
    delay_wdt(1000);
    for(int i=0;i<23;i++) {
      num = SIM900.read();                              // Captura el caracter que manda el SIM900
      p += num;
    }
    if(p[19] == ',') {                                  // si el caracter 19 es (,) significa que no tengo decenas y la unidad se desplazo al lugar del caracter 18
      senial = String(p[18]).toInt();                   // Convierto al caracter en variable INT
    }
    else {                                              // si el caracter 19 no tiene coma, entonces el nº tiene decena y unidades
      dec = String(p[18]).toInt();
      delay_wdt(100);
      uni = String(p[19]).toInt();
      senial = 10 * dec + uni; 
    }
    Serial.print("Nivel de señal: ");
    senialf = senial;
    Serial.println(senialf);
    delay_wdt(100);
    Serial.print("Contenido de p: ");
    Serial.println(p); 
  }
  else {
    Serial.println("sim900 no respondió!");
  }
}

// función buscadora de "buena señal"
void buscadorsenial() {
  do {
    nivelsenial();                                                //Verifico si hay señal
    delay_wdt(5000);
    if (senialf <= 5) {
      sim900_reset(); 
    }
    Serial.print("Buscando valores aceptables de señal...");
  } while (senialf <= 5);  
}

// Funcion que analiza si hay que mandar mensaje
void analiza() {
	if (entrada != estado)  {
	  if (entrada == true){
	   	Serial.println(outMessageF);
		  Serial.println('\r');
	  	outMessage = outMessageF;
	   	mensaje_sms();
	    estado = entrada;
	  }
	  else {
      Serial.println(outMessageOK);
      Serial.println('\r');
      outMessage = outMessageOK;
      mensaje_sms();
      estado = entrada;
	  }        
	}
	else {
      Serial.println("sin cambios, no se enviará ningún SMS");
	}
	check_wdt();
}

// función para leer las entradas
void leer_entrada(char input, unsigned char *estadox, String outMessagexF, String outMessagexOK, String destinationNumberx) {
  entrada = input;
  delay_wdt(100);
  estado = *estadox;
  outMessageF = outMessagexF;
  outMessageOK = outMessagexOK;
  destinationNumber = destinationNumberx;
  analiza();
  *estadox = estado;
}