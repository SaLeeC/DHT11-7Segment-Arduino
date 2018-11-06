/*
 * Spazio per la gestione del sensore DHT11
*/


// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - Adafruit Unified Sensor Library: https://github.com/adafruit/Adafruit_Sensor
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library

//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <DHT_U.h>

//#define DHTPIN 2         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
//#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

//DHT_Unified dht(DHTPIN, DHTTYPE);

//uint32_t delayMS;

void DHT11setup() 
{
  // Initialize device.
  dht.begin();
}


void DHT11loop() 
{
//___________________________________________________________________________________________________________
  // Controlla che sia passato il tempo miimo fra una misura e l'altra (per il sesore DHT11 1 secondo)
  if (millis() > DHT11AspettaFinoA)
  {
    //Aggiorna il puntatore temporale per la prossima misura
    DHT11AspettaFinoA = millis() + DHT11TempoAttesa;
    
    //Acquisisce i uovi campioi
    DHT11Acquisisci();
//___________________________________________________________________________________________________________
    //Se ci sono misure affidabili
    if (DHT11Status == 0)
    {
      //Fa un po di scena per far notare che funziona
      MAX7219FlashPoint();

      DHT11AggioraMisure();

      //Se è stato aggiiorato almeo u valore cotrolla i miimi e i massimi
      if (DHT11News != 0)
      {
        DHT11MiMax();
      }
    }
  }
}


void DHT11MiMax()
{
  //Controlla se abbiamo un nuovo minimo o massimo
  //per la Temperatura
  if (DHT11Temperatura[0] > DHT11Temperatura[3])
  {
    //Incrementa il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[0]++;
    if (DHT11ContatoreIsteresi[0] == DHT11IsteresiMinMax)
    {
      //Aggiorna il minimo
      DHT11Temperatura[3] = DHT11Temperatura[0];
      //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
      DHT11ContatoreIsteresi[0] = 0;
    }
  }
  else
  {
    //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[0] = 0;
  }

  if (DHT11Temperatura[0] < DHT11Temperatura[4])
  {
    //Incrementa il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[1]++;
    if (DHT11ContatoreIsteresi[1] == DHT11IsteresiMinMax)
    {
      //Aggiorna il minimo
      DHT11Temperatura[4] = DHT11Temperatura[0];
      //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
      DHT11ContatoreIsteresi[1] = 0;
    }
  }
  else
  {
    //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[1] = 0;
  }

  //Controlla se abbiamo un nuovo minimo o massimo
  //per la Temperatura
  if (DHT11Umidita[0] > DHT11Umidita[3])
  {
    //Incrementa il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[0]++;
    if (DHT11ContatoreIsteresi[2] == DHT11IsteresiMinMax)
    {
      //Aggiorna il minimo
      DHT11Umidita[3] = DHT11Umidita[0];
      //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
      DHT11ContatoreIsteresi[2] = 0;
    }
  }
  else
  {
    //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[2] = 0;
  }

  if (DHT11Umidita[0] < DHT11Umidita[4])
  {
    //Incrementa il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[1]++;
    if (DHT11ContatoreIsteresi[3] == DHT11IsteresiMinMax)
    {
      //Aggiorna il minimo
      DHT11Umidita[4] = DHT11Umidita[0];
      //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
      DHT11ContatoreIsteresi[3] = 0;
    }
  }
  else
  {
    //Azzera il contatore dei campioni consecutivi inferiori al minimo attuale
    DHT11ContatoreIsteresi[3] = 0;
  }
}


void DHT11AggioraMisure()
{
  //Controlla se ha accumulato il numero di campioni necessario ad una misura
  //E se è stato raggiunto procede a consolidare la misura
  if (DHT11CountCampioni == DHT11Campioni)
  {
    //Calcola la media dei campioni
    DHT11Temperatura[2] /= DHT11Campioni;
    DHT11Umidita[2] /= DHT11Campioni;

    //Azzera il registro che indica se una misura è stata aggiornata
    DHT11News = 0;

    //Controlla se è variato il valore della temperatura e, nel caso controlla se
    // la variazione è superiore alla Sensibilità, nel caso lo aggiorna
    if(abs(DHT11Temperatura[2] - DHT11Temperatura[0]) > DHT11TSensibilita)
    {
      DHT11Temperatura[0] = DHT11Temperatura[2];
      bitSet (DHT11News,DHT11NewsTemp);      
    }

    //Controlla se è variato il valore dellumidità e, nel caso controlla se
    // la variazione è superiore alla Sensibilità, nel caso lo aggiorna
    if(abs(DHT11Umidita[2] - DHT11Umidita[0]) > DHT11USensibilita)
    {
      DHT11Umidita[0] = DHT11Umidita[2];
      bitSet (DHT11News,DHT11NewsUmid);      
    }
    
    //Carica il primo valore della prossima serie di campioni negli accumulatori
    DHT11Temperatura[2] = DHT11Temperatura[1];
    DHT11Umidita[2] = DHT11Umidita[1];
    
    //Azzera il contatore dei campioni
    DHT11CountCampioni = 1;
  }
  
  //Altrimenti aggiorna gli accumulatori
  else
  {
    DHT11Temperatura[2] += DHT11Temperatura[1];
    DHT11Umidita[2] += DHT11Umidita[1];

    //Incrementa il contatore dei campioni
    DHT11CountCampioni++;
  }
}


void DHT11Acquisisci()
{
  //interroga il sensore di temperatura
  dht.temperature().getEvent(&DHT11Leggi);
  //Controlla se il sensore ha risposto o se in fault
  if (isnan(DHT11Leggi.temperature)) 
  {
    //setta il it di errore temperatura
    bitSet (DHT11Status,DHT11ErroreTemperratura);
  }
  else 
  {
    //resetta il bit di errore della temperatura
    bitClear (DHT11Status,DHT11ErroreTemperratura);
    //aggiorna la variaile temperonaea della temperature
    DHT11Temperatura[1] = DHT11Leggi.temperature;
  }
  
  //interroga il sensore di umidità
  dht.humidity().getEvent(&DHT11Leggi);
  //Controlla se il sensore ha risposto o se in fault
  if (isnan(DHT11Leggi.relative_humidity)) 
  {
    //setta il it di errore umidità
    bitSet (DHT11Status,DHT11ErroreUmidita);
  }
  else 
  {
    //resetta il bit di errore della umidità
    bitClear (DHT11Status,DHT11ErroreUmidita);
    //aggiorna la variaile temperonaea della umidità
    DHT11Umidita[1] = DHT11Leggi.relative_humidity;
  }
}

