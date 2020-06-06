
void send_aeha_reader(){
  digitalWrite(IR, HIGH);
  delayMicroseconds(3400);
  digitalWrite(IR, LOW);
  delayMicroseconds(1700);
}

void send_aeha_frame(char *data, int size){
  //send_aeha_reader();
  send_bits(data, size);
  delay(10);
  send_bits(data, size);
}
