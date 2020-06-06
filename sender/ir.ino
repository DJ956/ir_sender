void send_bits(char *data, int size){
  int i;
  for(i = 0; i < size - 1; i++){
    if(data[i] == '1'){
      //Serial.print("1");
      high_bit();
    }else{
      //Serial.print("0");
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
