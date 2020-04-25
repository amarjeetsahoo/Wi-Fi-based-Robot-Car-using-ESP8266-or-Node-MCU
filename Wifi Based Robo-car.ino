#include<ESP8266WiFi.h>
int lm1=D5;
int lm2=D6;
int rm1=D7;
int rm2=D8;
String clientresponse;
WiFiServer server(80);
void setup() 
{
  Serial.begin(9600);
  WiFi.disconnect();
  delay(20);
  Serial.println("START");
  WiFi.begin("Your SSID","Your Password");
  while(!(WiFi.status()==WL_CONNECTED))
  {
    delay(20);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("CONNECTED");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available();
  if(!client)
  {
    delay(30);
    return;
  }
  while(!client.available())
  {
    delay(30);
  }

  //A WEB-UI IS CREATED BELOW TO CONTROL THE MOVEMENTS OF THE ROBO-CAR: left,right,forward,backward and stop.
    clientresponse="";
    clientresponse=client.readStringUntil('/r');
    Serial.println(clientresponse);
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //to start html code we write this
    client.println("<!DOCTYPE html>");
    client.println("<html>");
    client.println("<head>");
    client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
    client.println("<style>");
    client.println(".btn {background-color: red;border: none;color: white;padding: 16px 32px;text-align: center;font-size: 16px;margin: 4px 2px;opacity: 0.6;transition: 0.3s;}");
    client.println(".btn:hover {opacity: 1}");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<a href=\"forward\"><button class='btn'>Forward</button></a><br>");
    client.println("<a href=\"backward\"><button class='btn'>Backward</button></a><br>");
    client.println("<a href=\"left\"><button class='btn'>Left</button></a>");
    client.println("<a href=\"right\"><button class='btn'>Right</button></a><br>");
    client.println("<a href=\"stop\"><button class='btn'>Stop</button></a>");
    client.println("</body>");
    client.println("</html>");
    client.println(" ");
  client.stop();
    delay(20);
}
