#include <WiFi.h>

const int AEHA = 0;
const int DAIKIN = 1;

const char* ssid = "aterm-a1abc8-g";
const char* pw = "0739fbe5afcfd";

const int IR = 23;

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
  if(cmd.length() > 0){
    int type = getType(cmd);
    
    cmd = cmd.substring(cmd.indexOf(":") + 1, cmd.length() + 1);

    int size = cmd.length() + 1;
    char data[size];
    cmd.toCharArray(data, size);
    execute(type, data, size);
  }
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

int getType(String str){
  char SPLIT = ':';
  char char_array[str.length() + 1];
  str.toCharArray(char_array, str.length() + 1);

  for(int i = 0; i < str.length(); i++){
    if(char_array[i] == SPLIT){
      return char_array[i - 1] - '0';
    }
  }
  
  return -1;
}

void execute(int type, char *data, int size){
  switch(type){
    case AEHA:{
      send_aeha_frame(data, size);
      Serial.println("AEHA");
      break; 
    }
    case DAIKIN:{
      break;
    }
    default:{
      break;
    }
  }
  Serial.println("execute");
}
