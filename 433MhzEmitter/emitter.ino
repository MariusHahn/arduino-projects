#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RCSwitch.h>

 
const char ssid[] = "*";
const char pass[] = "*";
 
// Web server port
const uint16_t port = 80;

const uint16_t dataPin = D3;
const uint16_t transmitterProtocol = 4;
 
// Web server object declaration
ESP8266WebServer server(port);
RCSwitch mySwitch = RCSwitch();

String webPage =
    "<html>\r\n" \
    "<head>\r\n" \
    "<title>ESP8266 Basic Page LED</title>\r\n" \
    "</head>\r\n" \
    "<body>\r\n" \
    "<h1>LED</h1>\r\n" \
    "<form method=\"post\">\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2221916\" formtarget=\"response\">AON</button>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2416012\" formtarget=\"response\">AOFF</button>\r\n" \
    "<br>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2126053\" formtarget=\"response\">BON</button>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2263253\" formtarget=\"response\">BOFF</button>\r\n" \
    "<br>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2416014\" formtarget=\"response\">CON</button>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2309998\" formtarget=\"response\">COFF</button>\r\n" \
    "<br>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2263255\" formtarget=\"response\">DON</button>\r\n" \
    "<button type=\"submit\" name=\"code\" value=\"2126055\" formtarget=\"response\">DOFF</button>\r\n" \
    "<br>\r\n" \
    "</form>\r\n" \
    "<iframe id=\"response\" name=\"response\"></iframe>\r\n" \
    "</body>\r\n" \
    "</html>\r\n";
 
void handleRoot()
{        
    server.send(200, "text/html", webPage);
}

void handleLed(){
    if (server.hasArg("code")) {
        const String codeString = server.arg("code");
        const int code = codeString.toInt();
        if(code != 0){
          mySwitch.send(code, 24);
          server.send(200, "text/html", "Send: " + codeString);
        }
    server.send(200, "text/html", "Couldn't convert: " + codeString);
    }
    handleRoot();
}
 
void setup()
{
    // Set pin as output
    pinMode(dataPin, OUTPUT);
    mySwitch.enableTransmit(dataPin);
    mySwitch.setProtocol(transmitterProtocol);

    // Setup serial communication
    Serial.begin(74880);
 
    // *** Connect to a WiFi acces point ***
    Serial.printf("Connecting to %s ", ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.printf(" Connected\n");
    Serial.printf("IP address: %s\n", WiFi.localIP().toString().c_str());
 
    // *** Start web server ***
    server.on("/", HTTP_GET, handleRoot);
    server.on("/", HTTP_POST, handleLed);
    server.begin();
    Serial.printf("Web server started at port %d\n", port);
}
 
void loop()
{
    server.handleClient();
}
