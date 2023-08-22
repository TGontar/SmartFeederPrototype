# Smart bird feeder prototype

A prototype for smart bird feeder sofrware interface, which allows to scan sensors, take photos, store them on SD card an send all data to FTP server. 

The interface is implemented as an Arduino project, which should be uploaded on ESP8266 microchip. The program connects the chip to preset WIFI network, scans weather sensors readings, takes photos of birds and stores them on SD-card. Every preset period of time the program send collected data to web server, using FTP protocol.
