#include <Arduino.h>

#include "ftp_client.hpp"
#include "ftp_credentials.hpp"
#include <SPI.h>
#include <SD.h>
#define SD_CS_PIN  A6    // Подключение SD Card      
  int i = 0;

namespace esp8266_arduino {
namespace ftp {
client test_client (
  server_ip{ IPAddress{145, 14, 144, 214} },
  server_port{21},
  user{USER},
  password{PASSWORD}
);
}
}

void setup() {

  
  // Begin serial communication
  Serial.begin(115200);
  Serial.println(F("FTP Client Project"));

  // Connect to Wifi
  String ssid = "Students";
  String password = "C12H22O11";
  WiFi.begin(ssid, password);
  Serial.print(F("Connecting"));
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(F("."));
    delay(100);
    yield();
  }
  Serial.print(F("\n"));
  Serial.println(F("Connected!"));





}



void loop() {
  i += 10;
   


  // Create a test file
  Serial.println(F("Creating test file."));
  SD.begin(SD_CS_PIN);
  File logFile = SD.open("log.txt", "w+");
  String a = String("This is a test file updated. ") + String(i)+ String(" seconds passed");
  logFile.println(a); // Записываем в файл строку data.
  logFile.close();       // Закрываем файл.

  String finalString = "";
  File logFile1 = SD.open("log.txt");
        // считываем все байты из файла и выводим их в COM-порт
        while (logFile1.available()) {
            finalString += (char)logFile1.read();
        }
        // закрываем файл
        logFile1.close();
  Serial.println(finalString);
  SPIFFS.begin();
  fs::File file_handler;
  file_handler = SPIFFS.open("/log1.txt", "w+");
  file_handler.println(finalString);
  file_handler.close();


  

  esp8266_arduino::ftp::test_client.upload_file("/log1.txt", "/public_html/log1.txt");
  
    
  Serial.print(F("Heap: "));
  Serial.println(ESP.getFreeHeap());

  Serial.print(F("Heap Fragmentation: "));
  Serial.print(ESP.getHeapFragmentation());
  Serial.println("%");
  i = int(i);
  delay(10000);
}
