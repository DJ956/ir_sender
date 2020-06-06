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
