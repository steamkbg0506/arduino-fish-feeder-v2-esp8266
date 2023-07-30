#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"

#define HOME_SSID "KDSJJH"
#define HOME_PWD  "rhakqek2@@"

int feedHour = 0;
int timeNow = 0;
const int timezone = 3;
const int dst = 0;
bool didFeed = false;
const int motorpin = 12; // D6
const int sensorpin = 13; // D7
ESP8266WebServer server(80);

void rootF(){
  server.send(200, "text/html", "Server Running <br> Use app to control");
}

void feedF(){
  //먹이는 모터 동작
  Serial.println("Feeding function, feeding");
  server.send(200, "text/html", "Feeding...");
  digitalWrite(12, HIGH);
  delay(3000);
  while(digitalRead(sensorpin) == LOW){
    delay(50);
    //wait until motor spin
  }
  digitalWrite(12, LOW);
}

void hsetF0(){
  feedHour = 0;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF1(){
  feedHour = 1;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF2(){
  feedHour = 2;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF3(){
  feedHour = 3;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF4(){
  feedHour = 4;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF5(){
  feedHour = 5;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF6(){
  feedHour = 6;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF7(){
  feedHour = 7;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF8(){
  feedHour = 8;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF9(){
  feedHour = 9;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF10(){
  feedHour = 10;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF11(){
  feedHour = 11;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF12(){
  feedHour = 12;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF13(){
  feedHour = 13;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF14(){
  feedHour = 14;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF15(){
  feedHour = 15;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF16(){
  feedHour = 16;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF17(){
  feedHour = 17;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF18(){
  feedHour = 18;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF19(){
  feedHour = 19;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF20(){
  feedHour = 20;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF21(){
  feedHour = 21;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF22(){
  feedHour = 22;
  server.send(200, "text/html", "Hour Set Success");
}

void hsetF23(){
  feedHour = 23;
  server.send(200, "text/html", "Hour Set Success");
}


void setup() {
  //기초 IO 셋업
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(16, OUTPUT);
  digitalWrite(16, LOW);
  pinMode(motorpin, OUTPUT);
  digitalWrite(motorpin, LOW);
  pinMode(sensorpin, INPUT);
  // 인터넷 접속 관련
  WiFi.begin(HOME_SSID, HOME_PWD);
  while (WiFi.status() != WL_CONNECTED) {  // WiFi 접속이 완료되었나?
    delay(500);
    Serial.print(".");
  }
  digitalWrite(2, HIGH);
  Serial.println("\nWifi Connected");
  Serial.print("IP Addr: ");
  Serial.println(WiFi.localIP());

  //서버 셋업
  server.on("/", rootF);
  server.on("/feed", feedF);
  server.on("/0h", hsetF0);
  server.on("/1h", hsetF1);
  server.on("/2h", hsetF2);
  server.on("/3h", hsetF3);
  server.on("/4h", hsetF4);
  server.on("/5h", hsetF5);
  server.on("/6h", hsetF6);
  server.on("/7h", hsetF7);
  server.on("/8h", hsetF8);
  server.on("/9h", hsetF9);
  server.on("/10h", hsetF10);
  server.on("/11h", hsetF11);
  server.on("/12h", hsetF12);
  server.on("/13h", hsetF13);
  server.on("/14h", hsetF14);
  server.on("/15h", hsetF15);
  server.on("/16h", hsetF16);
  server.on("/17h", hsetF17);
  server.on("/18h", hsetF18);
  server.on("/19h", hsetF19);
  server.on("/20h", hsetF20);
  server.on("/21h", hsetF21);
  server.on("/22h", hsetF22);
  server.on("/23h", hsetF23);
  server.begin();
  Serial.println("Server listening");
  digitalWrite(16, HIGH);
}

void loop() {
  // 서버 클라이언트 응답
  server.handleClient();
  //시간 받아오기
  configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");
  while(!time(nullptr)){
    Serial.print(".");
    delay(10);
  } Serial.println();
  time_t now = time(nullptr);
  struct tm * timeinfo;
  String a[3];
  timeinfo = localtime(&now); 

  if(timeinfo->tm_hour >= 18){
    timeNow = timeinfo->tm_hour - 18;
  } else {
    timeNow = timeinfo->tm_hour + 6;
  }

  a[0]=String(timeinfo->tm_sec, DEC); 
  a[1]=String(timeinfo->tm_min, DEC); 
  a[2]=String(timeNow, DEC);  //(timeinfo->tm_hour)

  if(timeinfo->tm_sec<10) a[0]="0"+a[0];
  if(timeinfo->tm_min<10) a[1]="0"+a[1];
  if(timeinfo->tm_hour<10) a[2]="0"+a[2];
  
  Serial.println(a[2] + ":" + a[1] + ":" + a[0]);
  
  //만약 밥줄 시간이라면
  if(timeNow == feedHour && didFeed == false){
    didFeed = true;
    Serial.println("Feeding time, feeding");
    feedF();
  }

  if(timeNow != feedHour){
    Serial.println("Integrity reset");
    didFeed = false;
  }

  delay(10);
}
