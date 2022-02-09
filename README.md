# ESPModbusServer
Modbus Server on ESP8266

In this example, ESP8266 connect to existing WiFi network.
ESP act as tcp modbus server.
COIL 0x0000 is mapped to GPIO2 of ESP8266.
Using any modbus client you can control LED.

1. Open ~\Documents\Arduino\libraries\ folder.
2. Copy "ArduinoModbus.zip" file & extract archive.
3. Open "TCPModbusServer.ino" and configure SSID and password of your wifi network.
4. Upload sketch.
5. After upload, set ESP in run mode.
6. Open Serial monitor in Arduino and check IP address.
7. Connect any TCP modbus client to ESP with above IP address.

References:
1. How to upload sketch : https://www.youtube.com/watch?v=cTfjqNFAkZ8
2. Modbus Client : https://www.win-tech.com/html/demos.htm
