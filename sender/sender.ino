#include <WiFi.h>

const char* ssid = "aterm-a1abc8-g";
const char* pw = "0739fbe5afcfd";

const int IR = 36;

IPAddress ip(192,168,0,15);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

WiFiServer server(1234);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IR, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, pw);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  Serial.println("setup done");
}


void loop() {
  // put your main code here, to run repeatedly:
  String cmd;
  cmd = recv_cmd();

  delay(100);
}

String recv_cmd(){
  WiFiClient client = server.available();
  String str;
  if(client.connected()){
      Serial.println("Connected to client");
      str = client.readStringUntil('q');
      Serial.print("[");
      Serial.print(str);
      Serial.println("]");

      client.print("ok");

      client.stop();
      Serial.println("closed");
  }

  return str;
}

void send_aeha_reader(){
  digitalWrite(IR, HIGH);
  delayMicroseconds(3400);
  digitalWrite(IR, LOW);
  delayMicroseconds(1700);
}

void send_daikin_reader(){
  int i;
  for(i = 0; i < 5; i++){
    low_bit();
  }
  delay(25);
}

void send_daikin_frame(char *cs_code, int cs_size, char *data, int d_size){
  send_daikin_reader();
  send_aeha_reader();
  
  send_bits(cs_code, cs_size);
  delay(35);
  send_bits(data, d_size);
}

void send_bits(char *data, int size){
  int i;
  for(i = 0; i < size; i++){
    if(data[i] == '1'){
      high_bit();
    }else{
      low_bit();
    }
  }
}

void pwm_out(){
  uint8_t i;
  for(i = 0; i < 12; i++){
    digitalWrite(IR, HIGH);
    delayMicroseconds(25);
    digitalWrite(IR, LOW);
    delayMicroseconds(25);
  }
}

void high_bit(){
  pwm_out();
  digitalWrite(IR, LOW);
  delayMicroseconds(1275);
}

void low_bit(){
  pwm_out();
  digitalWrite(IR, LOW);
  delayMicroseconds(425);
}
