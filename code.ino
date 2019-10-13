// Adafruit ESP8266 - Version: Latest 
#include <Adafruit_ESP8266.h>

// DHT_sensor_library-1.3.0 - Version: Latest 
#include <DHT.h>
#include <DHT_U.h>


// // DHT_sensor_library-1.3.0 - Version: Latest 
// #include <DHT.h>    //includes the dht.h Library
// #include <Adafruit_Sensor.h>

#define dataPin 8
#define dhttype DHT22

DHT dht(dataPin, dhttype);

const int AOUTpin = 0;  //the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
int hum = 0;
int temp = 0;
int value;    //reads the analog (sensor) value, exact value, not binary like digital
float RS_gas = 0;
float ratio = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

}


void loop() {    
 //since this is a void loop, our sensors just keeps on measuring CO concentration, temperature, and humidity until we turn the device off

  float sensorValue = analogRead(A0);
  float sensor_volt = sensorValue/1024*5.0;
  // float perc = (sensor_volt/ 5.0) * 100 ;
  // float ppm = perc * 10000;
  RS_gas = (5.0-sensor_volt)/sensor_volt;
  ratio = RS_gas/(-2.0); //Replace R0 with the value found using the sketch above
  float ppm = 100 *pow(-log10(40)/log10(0.09), ratio);
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("sensor_volt: ");
  Serial.println(sensor_volt);
  Serial.print("CO: ");
  Serial.print(ppm);
  Serial.println(" ppm");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println();

  delay(3000);

  if(ppm >= 50 && temp > 56 && hum < 27){  
    Serial.println("HIGH POSSIBILITY OF WILDFIRE");
  }

  else if ((ppm >= 50 && temp > 56) || (ppm >= 50 && hum < 27) || (temp > 56 && hum < 27)) {
    //if two of the three conditions are met, then print that the area is prone to a wildfire
    Serial.println("AREA WILDFIRE PRONE");
  }
}