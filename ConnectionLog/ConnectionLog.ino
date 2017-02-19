#include <SPI.h>
#include <Ethernet.h>
#include <Time.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 0, 177);

EthernetClient client;

//char server[] = "www.arduino.cc";
IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 10000;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);
  
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip);
}

void loop() {
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }
}

void httpRequest() {
  client.stop();

  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    client.println("GET /latest.txt HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
    digitalClockDisplay();
  } else {
    Serial.println("connection failed");
    digitalClockDisplay();
  }
}

void digitalClockDisplay() {
    // digital clock display of the time
//    Serial.print(hour());
//    printDigits(minute());
//    printDigits(second());
//    Serial.print(" ");
//    Serial.print(day());
//    Serial.print(" ");
//    Serial.print(month());
//    Serial.print(" ");
//    Serial.print(year());
//    Serial.println();
}
