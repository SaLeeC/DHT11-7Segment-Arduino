/*
 *Monitor Temperatura e Umidità basato su DHT11
 *Dotato di display 7 segmenti
*/

//============================================================================
//DHT11
//============================================================================

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 2         // Pin which is connected to the DHT sensor.

sensors_event_t DHT11Leggi;   

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

DHT_Unified dht(DHTPIN, DHTTYPE);

#define DHT11TempoAttesa 1000
long int DHT11AspettaFinoA = millis() + DHT11TempoAttesa;

//Bit che indica l'errore restituito nel ciclo di lettura della temperatura 
#define DHT11ErroreTemperratura 0 
//Bit che indica l'errore restituito nel ciclo di lettura della umidità 
#define DHT11ErroreUmidita 1

//Vale 0 se non è camiato nessun valore
byte DHT11News;
//Bit che indica laggiornamento della temperatura 
#define DHT11NewsTemp 0 
//Bit che indica l'aggiornamento dell'umidità 
#define DHT11NewsUmid 1

//contiene lo stato (erroere o ok) delle sottounità del sensore
byte DHT11Status;
//Bit che indica l'errore restituito nel ciclo di lettura della temperatura 
#define DHT11ErroreTemperratura 0 
//Bit che indica l'errore restituito nel ciclo di lettura della umidità 
#define DHT11ErroreUmidita 1

//La cella 0 fornisce il valore verificato
//La cella 1 contiene il valore appena letto
//La cella 2 contiene l'accumulatore
//La cella 3 contiene il minimo
//La cella 4 contiene il massimo
int DHT11Temperatura[5] = {0, 0, 0, 99, -99};
byte DHT11Umidita[5] = {0, 0, 0, 99, 0};

//Sensibilità per Temperatura ovvero, il delta
//minimo che deve essere rilevato per considerare un valore cambiato
byte DHT11TSensibilita = 1;

//Sensibilità per Umidità ovvero, il delta
//minimo che deve essere rilevato per considerare un valore cambiato
byte DHT11USensibilita = 2;

//Isteresi per le registrazione dei minimi e dei massimi ovvero,
//numero dei campioni consecutivi che devono risultare diversi dall'ultimo registrato
//per cambiare il minimo o il massimo corrente
#define DHT11IsteresiMinMax 3

//La cella 0 conta l'isteresi del MINIMO TEMPERATURA
//La cella 1 conta l'isteresi del MASSIMO TEMPERATURA
//La cella 2 conta l'isteresi del MINIMO UMIDITA
//La cella 3 conta l'isteresi del MASSIMO UMIDITA
byte DHT11ContatoreIsteresi[4] = {0, 0, 0, 0};

//Campioni per misura
#define DHT11Campioni 3
byte DHT11CountCampioni = 1;


//============================================================================
//MAX7219 7 segmenti 8 digit
//============================================================================

#include "DigitLedDisplay.h"

/* Arduino Pin to Display Pin
   12 to DIN,
   10 to CS,
   11 to CLK */
DigitLedDisplay ld = DigitLedDisplay(12, 10, 11);

//Contatore per il flash dei punti
byte MAX7219Flash = 0;

//============================================================================
//Pulsante Minimo e Massimo 
//============================================================================

#define PulsanteMinimo 3
#define PulsanteMassimo 4


//============================================================================

void setup() 
{
  pinMode(PulsanteMinimo, INPUT_PULLUP);
  pinMode(PulsanteMassimo, INPUT_PULLUP);

  DHT11setup();
  MAX7219setup();
}

void loop() 
{
  DHT11loop();
  if(DHT11News != 0)
  {
    MAX7219TempUmid();
  }
  
  //Controlla se è richiesta la visualizzazione dei minimi e dei massimi
  
  //Tutti e due premuti azzerano i valori di minimo e massimo
  if ((digitalRead(PulsanteMinimo) == LOW) | (digitalRead(PulsanteMassimo) == LOW))
  {
    DHT11Temperatura[3] = 99;
    DHT11Umidita[3] = 99;
    DHT11Temperatura[4] = -99;
    DHT11Umidita[4] = 0;
    MAX7219Min();
    for (;digitalRead(PulsanteMinimo) == LOW;)
    {
      delay(300);
    }
  }

  //Minimo premuto
  if (digitalRead(PulsanteMinimo) == LOW)
  {
    MAX7219Min();
    for (;digitalRead(PulsanteMinimo) == LOW;)
    {
      delay(300);
    }
    delay(2000);
    MAX7219TempUmid();
  }

  //Minimo premuto
  if (digitalRead(PulsanteMassimo) == LOW)
  {
    MAX7219Max();
//    for (byte ccc; digitalRead(PulsanteMassimo) == LOW; ccc++)
    for (; digitalRead(PulsanteMassimo) == LOW;)
    {
      delay(300);
    }
    delay(2000);
    MAX7219TempUmid();
  }
}

