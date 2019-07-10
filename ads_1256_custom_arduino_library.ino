#include <SPI.h>
#include <digitalWriteFast.h> // BE SURE YOU HAVE INSTALLED THE DIGITAL WRITE FAST LIBRARY FROM HERE: https://github.com/NicksonYap/digitalWriteFast

//IF YOU ARE USING TEENSY, CHECK OUT MY OTHER LIBRARY ON MY GITHUB: https://github.com/mbilsky/TeensyADS1256


//(other stuff for getting the ADS1526 to work is in the next tab
//IF YOU CHANGE THESE, YOU NEED TO UPDATE THE CODE ON THE NEXT TAB...
//ALL THE DIGITAL WRITE FAST NUMBERS NEED TO BE UPDATED TO MATCH YOUR DESIRED CS PIN
//THE DATA READY PIN NEEDS TO BE AN INTERRUPT PIN: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

#define ADS_RST_PIN    9 //ADS1256 reset pin
#define ADS_RDY_PIN    2 //ADS1256 data ready
#define ADS_CS_PIN    10 //ADS1256 chip select


/* Keep this commented...
 *  THESE ARE THE PINS ON THE ARDUINO UNO YOU SHOULD WIRE THESE TO
    CLK  - pin 13
    DIN  - pin 11 (MOSI)
    DOUT - pin 12 (MISO)

    //For MEGA:
    CLK  - pin 52
    DIN  - pin 51 (MOSI)
    DOUT - pin 50 (MISO)
    
*/


//put the ADC constants here

double resolution = 8388608.; //2^23-1

//this needs to match the setting in the ADC init function in the library tab
double Gain = 64.; //be sure to have a period 

double vRef = 5.0; //reference voltage

//we'll calculate this in setup
double bitToVolt = 0.;

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println("booting");
  //initialize the ADS
  pinMode(ADS_CS_PIN, OUTPUT);

  pinMode(ADS_RDY_PIN, INPUT);
  pinMode(ADS_RST_PIN, OUTPUT);

  SPI.begin();

  initADS();
  Serial.println("done init");

  //determine the conversion factor
    //do some calculations for the constants
  bitToVolt = resolution*Gain/vRef;
}

int32_t val1;
int32_t val2;
int32_t val3;

void loop() {
  // put your main code here, to run repeatedly:

double value = 0;
for (int i = 0; i <1; i++){
  read_three_values();
  value += val1;
}

value /=1.;

  Serial.print(value,8);
  Serial.print("\t");
  Serial.print(val2);
  Serial.print("\t");
  Serial.println(val3);

//
//double value = 0;
//for (int i = 0; i <10; i++){
//  value += read_Value();
//}
//
//value /= 10.;
//value /= bitToVolt;
//
//Serial.println(value,11);
}
