#include <Ethernet.h>
#include <SoftwareSerial.h>
#include <SPI.h>
 
SoftwareSerial HM10(2,3); // RX, TX
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0E, 0xC2, 0x90 };    // mac 주소만 변경해주자

EthernetClient client;
byte server[] = {192, 168, 0, 26}; //서버의 ip를 적어주자


void setup(){
  HM10.begin(9600);

  Serial.begin(9600);
  
 

  Ethernet.begin(mac);                       //mac 주소 이용해 알아서 IP등록이 된다.

  Serial.println(Ethernet.localIP());       //할당된 내 IP주소를 시리얼모니터롤 볼 수 있다.

  delay(1000);
 

  Serial.println("connecting...");
  client.connect(server, 8080);             //연결시도  만약 연결이 안되면 오래 지연됨
  if (client.connected()) {
    Serial.println("connected");
  }

  else{ 
    Serial.println("fail");
  }
}

void loop()
{
  //String tmp = "AT";
  if (client.available()) {
    //Serial.write(" dttd  ");
    //char c = client.read();
    HM10.write((int)(client.read()));
    //c = client.read();
    HM10.write((int)(client.read()));
    //HM10.write(84);
    //Serial.write(" dttd  ");
    //HM10.write("AT");
    char c = HM10.read();
    Serial.write(c);
    if (c == 'O'){
      //client.write(c);
      c = HM10.read();
      Serial.write(c);
      if (c == 'K'){
        client.write("OK");
      }
      else{
        client.write("OCCUR NETWORK ISSUE\n");
      }
    }
    else{
      client.write("OCCUR NETWORK ISSUE\n");
    }
    
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for(;;)
      ;
  }
  delay(500);
}
