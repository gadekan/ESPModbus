#include <ESP8266WiFi.h>
#include <ArduinoModbus.h>

const char* ssid = "ssid";//type your ssid
const char* password = "password";//type your password
 
const int ledPin = 2; // GPIO2 of ESP8266
WiFiServer server(502); // Modbus tcp port
ModbusTCPServer modbusTCPServer; // modbus server
 
void setup() {
  Serial.begin(115200);
  delay(5000);
  Serial.println("Modbus TCP Server");
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // you're connected now, so print out the status:
  printWifiStatus();
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.println(WiFi.localIP());

  // start the Modbus TCP server
  if (!modbusTCPServer.begin()) {
    Serial.println("Failed to start Modbus TCP Server!");
    while (1);
  }

  // configure a single coil at address 0x00
  modbusTCPServer.configureCoils(0x00, 1);
  
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    // Wait until the client sends some data
    Serial.println("new client");
    // let the Modbus TCP accept the connection 
    modbusTCPServer.accept(client);
    
    while (client.connected()) {
      // poll for Modbus TCP requests, while client connected
      modbusTCPServer.poll();
      
      // update the LED
      updateLED();
    }
    
    Serial.println("client disconnected");
  }
}

void updateLED() {
  // read the current value of the coil
  int coilValue = modbusTCPServer.coilRead(0x00);

  if (coilValue) {
    // coil value set, turn LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // coild value clear, turn LED off
    digitalWrite(ledPin, LOW);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
