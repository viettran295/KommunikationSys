uint8_t val[2] = {0,0};

void setup() {
  Serial.begin(115200);
}

int incoming;
uint8_t idx = 0;

void loop() {
  if(Serial.available()){
    int tmp = 0;
    while(1){
      incoming = Serial.read();
      if(incoming == '\t') break;
      if(incoming == -1) continue;
      if(incoming == '\n'){
        val[idx] = tmp;
        Serial.println(val[idx]);
        idx = 0;
        break;
      }
      tmp *= 10;
      tmp += incoming-'0';
    }
    if(incoming!='\n'){
      val[idx] = tmp;
      Serial.println(val[idx]);
      idx++;
    }
  }
}
