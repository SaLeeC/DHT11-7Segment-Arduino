# DHT11-7Segment-Arduino
Misuratore temepratura e umidità ambiente con sensore DHT11 e display 7 segmenti 8 digit basato su piastra Arduino compatibile
E' richiesto:
1 microcontrollore arduino compatibile (328 o 32u4 o 2560)
1 sensore DHT11 (sensore tempeatura e umidità azzurro o un DHT22 bianco)
1 display 7 segmenti 8 digit controllato con MAX7219
2 pulsanti
(2 resitenze da 10Kohm) (queste resistenze sono il Pull-Up dei pulsanti e non sono indispensabili in quanto è attivo il Pull-Up interno del microcontrollore)
1 resistenza da 4,7Kohm
materiale per i collegamenti (breadborad e jumper).

E' necessario aver installato l'IDE di arduino con le seguenti librerie:
Adafruit_Sensor
DHT
DHT_U
DigitLedDisplay
Le librerie si installano direttamente dal menù di gestione delle librerie dell'IDE e sono rintracciabili cercando DHT11 e MAX7219.

I pin di connessione sono indicati nel codice e comunque sono:
DHT11 data - Arduino pin 2

MAX7219 Data - Arduino pin 12
MAX7219 CS   - Arduino pin 10
MAX7219 CLK  - Arduino pin 11

Pulsante Temperatura - Arduino pin 3
Pulsante Umidità     - Arduino pin 4
