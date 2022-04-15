
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "7GXP36JR4m7TzNXdjlKFZbRzm1CT3STr";

char ssid[] = "2PoInT0";
char pass[] = "akhilesh";

WidgetBridge Switch(V1);

BLYNK_CONNECTED() {
  Switch.setAuthToken("rKNLvAImJFUGLHwmrgZtNmh3MJhtCLaO");
}

void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
pinMode(D2,INPUT_PULLUP);
pinMode(D3,INPUT_PULLUP);
}

void loop()
{
  if(digitalRead(D2)==LOW)
{
  //Serial.println("Entered");
  Switch.virtualWrite(V1,1);
  delay(1000);
}
if(digitalRead(D3)==LOW)
{
  //Serial.println("Exited");
  Switch.virtualWrite(V1,0);
  delay(1000);
}
  Blynk.run();
}
