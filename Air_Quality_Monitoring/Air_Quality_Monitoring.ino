#define BLYNK_TEMPLATE_ID " "//add your template id
#define BLYNK_TEMPLATE_NAME " "//add your template name
#define BLYNK_AUTH_TOKEN " "//add your blynk auth token
#define BLYNK_PRINT Serial
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

int sensor_input=34;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "  "; // type your wifi nano 
char pass[] = "  "; // type your wifi password

BlynkTimer timer;

#define DHTPIN 27 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

void sendsensor ()
{
 float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("     Humidity : ");
    Serial.println(h);
    
  int analog_data=analogRead(sensor_input);
  Serial.print("Air Quality : ");
  Serial.println(analog_data);
  delay(200);

  Blynk.virtualWrite(V0, analog_data); 
  delay(300);
}
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval (500L, sendsensor);

}

void loop()
{
Blynk.run();
timer.run();
}
