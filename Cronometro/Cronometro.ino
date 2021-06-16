#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);   //Incluye la libreria y conecta los siguientes pines a cada digito

int led = 13;                       //LED a pin 13
int boton = 2;                      //Boton a pin 2
int value = LOW;                    //Valor anterior del led
int estado;                         //Almacena el estado del boton
int ultimoestado;                   //Almacena el ultimo estado del boton
int parpadea;                       
int frameRate = 100;                //Los frames a los que corre el cronometro

long intervalo = (1000/frameRate);   
long previousMillis = 0;            //Almacena el anterior uso del led
long start ;                        //Empieza el cronometro
long tiempoPasado ;                 //Tiempo que ha pasado

int fractional;                     //Almacena una fraccion de los frames
int fractionalSegs;                 //Almacena una fraccion de los segundos
int fractionalMins;                 //Almacena una fraccion de los minutos
int tiempoFrames;                   //Frames que han pasado
int tiempoSegs;                     //Segundos que han pasado
int timepoMins;                     //Minutos que han pasado

char buf[10];                                       //Es una funcion llamada itoa que convierte cualquier int a una cadena de caracteres

void setup()
{
   lcd.begin(16, 2);                                //Inicia el led
   pinMode(led, OUTPUT);                            //Ahora el pin del led es un output
   digitalWrite(boton, HIGH);                       //Usa las resistencias de pullup
}

void loop()
{
   digitalWrite(led, LOW);                          //Inicia el led

   estado = digitalRead(boton);                     //Lee y almacena el estado del boton

   if (estado == LOW && ultimoestado == HIGH  &&  parpadea == false){    //Si pasa de high a low entonces empieza a contar el cronometro  
   
   start = millis();                                //Almacena cuando empieza
   parpadea = true;                                 //Empieza a parpadear
   delay(10);                                       //Este delay evita el rebote del switch
   ultimoestado = estado;                           //Almacena el estado y el ultimo estado del boton para comparar 
 }

   else if (estado == LOW && ultimoestado == HIGH && parpadea == true)   //Si pasa de high a low esta vez para el cronometro
   {  
   parpadea = false;                                //Se apaga el parpadeo
   ultimoestado = estado;                           //Almacena de nuevo los estados para comparar
          
   tiempoPasado =   millis() - start;               //Almacena el tiempo transcurrido
   timepoMins = (tiempoPasado / 60000);             //Division entre 60000 milisegundos para pasar a minutos
   tiempoSegs = (tiempoPasado / 1000);              //Division entre 1000 milisegundos para pasar a segundos
   tiempoFrames = (tiempoPasado / intervalo);       //Division entre 100 milisegundos para pasar a una centesima de segundo
   fractional = (int)(tiempoFrames % frameRate);    //Hacemos una fraccion de la centesima de segundo
   fractionalSegs = (int)(tiempoSegs % 60);         //Hacemos una fraccion de los 60 segundos
   fractionalMins = (int)(timepoMins % 60);         //Hacemos una fraccion de los 60 minutos
   lcd.clear();                                     //Limpia el lcd

 if (fractionalMins < 10){                          //Sirve para añadir un cero a la izquierda si es menor de 10
   lcd.print("0");                                 
      }

   lcd.print(itoa(fractionalMins, buf, 10));        //Usa la funcion itoa para colocar un : al poner los minutos
   lcd.print(":");       
                             
 if (fractionalSegs < 10){                          //Sirve para añadir un cero a la izquierda si es menor de 10
   lcd.print("0");                                 
      }

 lcd.print(itoa(fractionalSegs, buf, 10));          //Usa la funcion itoa para colocar un : al poner los segundos
   lcd.print(":");                                    

 if (fractional < 10){                              //Sirve para añadir un cero a la izquierda si es menor de 10 
   lcd.print("0");                                 
      }     

   lcd.print(itoa(fractional, buf, 10));            //Pasa el int a string and print a fractional part of 25 Frames to the LCD
   }

 else{
      ultimoestado = estado;                        //Almacena el estado y ultimo estado del boton
   }

 if ( (millis() - previousMillis > intervalo) ) 
{

    if (parpadea == true){
       previousMillis = millis();                   //Recuerda el ultimo parpadeo

       digitalWrite(led, HIGH);                     //Activa el led para ver el resultado

       tiempoPasado =   millis() - start;           //Almacena el tiempo transcurrido
       timepoMins = (tiempoPasado / 60000);         //Division entre 60000 milisegundos para pasar a minutos - then cast to an int to print
       tiempoSegs = (tiempoPasado / 1000);          //Division entre 1000 milisegundos para pasar a segundos - then cast to an int to print
       tiempoFrames = (tiempoPasado / intervalo);   //Division entre 40 para pasar a 1/25 de segundo - then cast to an int to print
       fractional = (int)(tiempoFrames % frameRate);//Hacemos una fraccion de los 25 Frames
       fractionalSegs = (int)(tiempoSegs % 60);     //Hacemos una fraccion de los 60 segundos
       fractionalMins = (int)(timepoMins % 60);     //Hacemos una fraccion de los 60 minutos
       lcd.clear();                                 //Limpia el Lcd
                }
             }
         }                                 
