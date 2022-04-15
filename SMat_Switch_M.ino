#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

int count=0;
int threshold=1;
int trigger;
int p=0;

char auth[] = "rKNLvAImJFUGLHwmrgZtNmh3MJhtCLaO";
char ssid[] = "2PoInT0";
char pass[] = "akhilesh";

WidgetLED statLED(V3);

void SwitchF(int input)
{
if(input)
{digitalWrite(D1,HIGH);
statLED.on();
}
else
{digitalWrite(D1,LOW);
statLED.off();
}
}

void TriggerF()
{
if(p==0)
{if(count>=threshold)
{digitalWrite(D1,HIGH);
statLED.on();
Blynk.virtualWrite(V1,1);
Blynk.notify("Fan has been turned ON");
p++;}
}
if(p==1)
{if(count==0)
{digitalWrite(D1,LOW);
statLED.off();
Blynk.virtualWrite(V1,0);
Blynk.notify("Everyone has left.Fan has been turned OFF");
p--;}
}
}

BLYNK_WRITE(V1)
{
 int pinData = param.asInt();
 if(pinData==1)
 {count=count+1;
 Blynk.virtualWrite(V4,count);}
 else
 {count=count-1;
 if(count<0)
 count=0;
 Blynk.virtualWrite(V4,count);}
 if(trigger==1)
 {TriggerF();}
}

BLYNK_WRITE(V2)
{
  int ButtonData = param.asInt();
  SwitchF(ButtonData);
}

BLYNK_WRITE(V4)
{
  count=param.asInt();
}

BLYNK_WRITE(V5)
{
  threshold=param.asInt();
}

BLYNK_WRITE(V6)
{
  trigger=param.asInt();
}

BLYNK_WRITE(V7)
{
  count=0;
  Blynk.virtualWrite(V4,count);
}

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V4,V2,V6,V5,V3);
}

void setup()
{
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(D1,LOW);
}

void loop()
{
  Blynk.run();
}
