//Libraries to be included from GitHub
#include <Wire.h>
#include <Adafruit_ADS1015.h> // for the ADS1115
#include <DHT.h> //for Temperature and Humidity sensor
#include <DHT_U.h>// DHT unified sensor
#include <ESP8266WiFi.h>  //For Wi-Fi operations
#include <ESP8266HTTPClient.h> //needed for library
#include <DNSServer>
#include <ESP8266WebServer.h> // For creation of online web server
#include <WiFiManager.h>
#define DHTTYPE DHT11 // DHT 11 sensor by default, can change to DHT22
#define dht_dpin 13 // GPIO Pin on NodeMCU
DHT dht(dht_dpin, DHTTYPE);
Adafruit_ADS1115 ads; //for 16 bit ADS1115
String test=""; // global variable
void setup(void)
{
Wire.begin(D2, D1);
dht.begin(); //setup of DHT
Serial.begin(115200); //setting Baud rate
Serial.println("Getting single-ended readings from ADS");
Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
ads.begin(); //setup of ADS
Serial.println("Humidity and temperature\n\n");
WiFiManager wifiManager; //To create web server
wifiManager.resetSettings();
wifiManager.autoConnect("OCLEMS"); //access point name of the NodeMCU
Serial.println("connected...yay :)");
}
void loop() {
if (WiFi.status() == WL_CONNECTED) {
//Check WiFi connection status
HTTPClient http; //Declare an object of class
HTTPClient
int16_t adc0, adc1, adc2,adc3 // The analog pins of ADC defined as long integers
adc0 = ads.readADC_SingleEnded(0);
adc1 = ads.readADC_SingleEnded(1);
adc2 = ads.readADC_SingleEnded(2);
adc3 = ads.readADC_SingleEnded(2);

float v1= (adc0*0.1875)/1000;
float v2=(adc1*0.1875)/1000;
float v3=(adc2*0.1875)/1000;
float v4=(adc3*0.1875)/1000;

float h = dht.readHumidity(); // Relative Humidity
float t = dht.readTemperature(); //degree Celsius
delay(1000);

// Need to be converted to string to send to an API or webserver
String one = String(v1);//rain voltage
String two = String(v2); //ldr voltage
String three = String(v3); //uv voltage
String four= String(v4);//mq voltage
String test= one + "|" + two + "|" + three + "|" + String(t) + "|" +String(h);  // concatenation

http.begin("http://ocl-data-
server.herokuapp.com/sensor_read/" +  test); //Specify request destination
int httpCode = http.GET(); //Send the request
if (httpCode > 0) {   //Check the returning code
String payload = http.getString(); //Get the request response payload
Serial.println(payload); //Print the response payload
}
http.end(); //Close connection
}
delay(15000); // send data every 15 seconds (can be changed according to need)
}
