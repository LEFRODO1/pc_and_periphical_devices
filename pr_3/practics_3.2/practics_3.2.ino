#include <Accelerometer.h>
#include <Barometer.h>
#include <BaseIMU.h>
#include <Compass.h>
#include <GOST4401_81.h>
#include <Gyroscope.h>
#include <MadgwickAHRS.h>
#include <TroykaIMU.h>
#include <TroykaMeteoSensor.h>
#include <SPI.h>
#include <WiFi.h>
#include <string>
#include <TroykaIMU.h>
#include <TroykaMeteoSensor.h>
std::string ssid = "ASOIU";     
std::string pass = "kaf.asoiu.48";   
int status = WL_IDLE_STATUS;  

Barometer barometer;
TroykaMeteoSensor meteoSensor;

WiFiServer server(80);
int keyIndex = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    continue; 
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi Shield not present");
    // don't continue:
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid.c_str());
    status = WiFi.begin(ssid.c_str(), pass.c_str());

    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println(WiFi.localIP());
  server.begin();
  meteoSensor.begin();
  barometer.begin();
}

void loop() {
	int stateSensor = meteoSensor.read();
  float pressureMillimetersHg = barometer.readPressureMillimetersHg();
  float temperature = barometer.readTemperatureC();
	WiFiClient client = server.available();
	if (client) {
		Serial.println("Новый клиент");

		bool currentLineIsBlank = true;

		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);

				if (c == '\n' && currentLineIsBlank) {
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");
					client.println("Refresh: 5");
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
          client.println("<p>Meteo Sensor Data</p>");
					client.println("<p>Temperature = " + String(meteoSensor.getTemperatureC()) +  " C</p>");
          client.println("<p>Humidity = " + String(meteoSensor.getHumidity()) +  " %</p>");
          client.println("<p>Barometr Data</p>");
          client.println("<p>Pressure = " + String(pressureMillimetersHg) +  " mmHg</p>");
          client.println("<p>Temperature = " + String(temperature) +  " C</p>");
					client.println("</html>");
					break;
				}

				if (c == '\n') {
					currentLineIsBlank = true;
				} else if (c != '\r') {
					currentLineIsBlank = false;
				}
			}
		}

		delay(100);

		client.flush();
	}
}