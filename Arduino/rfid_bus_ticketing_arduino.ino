/*
 * vit id card UID : 06:5F:16:18
 * plain rfid tag UID: 29:08:51:B2
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *   MFRC522 RFID Reader          ESP32                  4-PIN OLED   
 *           Pin                  Pin                       Pin       
 * -----------------------------------------------------------------------------------------
 *         3.3V                   3V3                        -
 *         RST                    D4(GPIO4)                  -
 *         GND                    GND                        -
 *         RQ                     Not Connected              -
 *         MISO                   D19(GPIO19)                -
 *         MOSI                   D23(GPIO23)                -
 *         SCK                    D18(GPIO18)                -
 *         SDA                    D5(GPIO5)                  -
 *                                    
 *          -                     3V3                        VCC
 *          -                     GND                        GND
 *          -                     D22(GPIO22)                SCL
 *          -                     D21(GPIO21)                SDA
 */

#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <Esp32WifiManager.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
String Event_Name = "Customer_Entered";

String Key = "kKdkb3hT_ApvIwljstuo8X1ycV6ZcDO9gh5-nKYM-UN";

// Replace with your unique IFTTT URL resource
String resource = "https://maker.ifttt.com/trigger/Customer_Entered/with/key/kKdkb3hT_ApvIwljstuo8X1ycV6ZcDO9gh5-nKYM-UN" ;
String resource1 = "https://maker.ifttt.com/trigger/Message_User/with/key/nz11ISnKEJSiUIwdhv21uDA0QYv28mMGgpF0ANEp4Bu";
// Maker Webhooks IFTTT
// Maker Webhooks IFTTT
const char* server = "maker.ifttt.com";

// Replace with your SSID and Password
const char* ssid     = "Airtel_Home";
const char* password = "9910149273";
const char* NAME;
const char* ID;

// RFID PINS
#define SS_PIN 5
#define RST_PIN 4

// RFID Variable
MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup()
{
 

  // Initialize everything
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();
  Serial.print("Connecting to: ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  Serial.println("I am waiting for card...");
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("Hello, welcome!");
  display.display(); 
 
}

void loop()
{

  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
  // strID to store UID
  String strID = "";
  for (byte i = 0; i < 4; i++)
  {
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i], HEX) +
      (i != 3 ? ":" : "");
  }

  strID.toUpperCase();
  Serial.print("Tap card key: ");
  Serial.println(strID);
  delay(500);

  if (strID.indexOf("29:08:51:B2") >= 0)
  {
    Serial.println("****Authorised access****");
    Serial.println("*************************");
    delay(2000);
    NAME = "Vinayak";
    ID = "29:08:51:B2";
    display.clearDisplay();
    display.println("Hello Vinayak");
    display.setCursor(1,10);
    display.println("Authorised Access");
    display.display();
    makeIFTTTRequest();
    makeIFTTTRequest1();

  }

  else if(strID.indexOf("06:5F:16:18") >= 0)
  {
    Serial.println("****Authorised access****");
    Serial.println("*************************");
    delay(2000);
    NAME = "Chaitanya";
    ID = "06:5F:16:18";
    display.clearDisplay();
    display.println("Hello Chaitanya");
    display.setCursor(1,10);
    display.println("Authorised Access");
    display.display();
    makeIFTTTRequest();
    makeIFTTTRequest1();
  }
  else
  {
    Serial.println("******Access denied******");
    Serial.println("*************************");
    display.clearDisplay();
    display.setCursor(1,10);
    display.println("Access Denied");
    display.display();
    delay(500);
    return;
  }
}
//function to update entry in google sheets
void makeIFTTTRequest() {
  Serial.print("Connecting to ");
  Serial.print(server);
  
  // Wificlient type Variable
  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");
  Serial.println(resource);
  
  // Creating a json Object to send data over HTTP protocol
  String jsonObject = String("{\"value1\":\"") + NAME + "\",\"value2\":\"" + ID
                      + "\"}";
  //Post Request, HTTP Request, resource refers to protocol for updating entry in the google sheets
  client.println(String("POST ") + resource + " HTTP/1.1");
  client.println(String("Host: ") + server);
  client.println("Connection: close\r\nContent-Type: application/json");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  //Sending jsonObject
  client.println(jsonObject);


  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}
//function to send mail to the user
void makeIFTTTRequest1() {
  Serial.print("Connecting to ");
  Serial.print(server);

  WiFiClient client;
  int retries = 5;
  while (!!!client.connect(server, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if (!!!client.connected()) {
    Serial.println("Failed to connect...");
  }

  Serial.print("Request resource: ");

  Serial.println(resource1);
 
                      // Putting GET Request to HTTP server, resource1 refers to mail user
                     client.print(String("GET ") + resource1 + " HTTP/1.1\r\n" + 
                                    "Host: " + server + "\r\n" +   
                                           "Connection: close\r\n\r\n");    


  int timeout = 5 * 10; // 5 seconds
  while (!!!client.available() && (timeout-- > 0)) {
    delay(100);
  }
  if (!!!client.available()) {
    Serial.println("No response...");
  }
  while (client.available()) {
    Serial.write(client.read());
  }

  Serial.println("\nclosing connection");
  client.stop();
}
