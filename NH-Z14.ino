
uint16_t gas;   //variável global

void setup() {
  iniciaGas();
}

void loop() {  

      
}

void iniciaGas(){
  Serial.end();
  delay(50);
  Serial.begin(9600);
}

void leitura () {
  static uint8_t vezesVazio = 0;
  const uint8_t comando[9] = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  uint8_t response[9] = {0}, check = 0;
  uint32_t time = millis() + 200;

  if (vezesVazio == 5) {iniciaGas(); return;}
  else if (vezesVazio  > 9) {vezesVazio = 0; gas = 0; return;}
  
  for (uint8_t i=0; i < 9; i++) Serial.write(comando[i]);
  while (Serial.available() < 9) {
    if (millis() > time) {vezesVazio++; break;}
  }
  
  for(uint8_t i = 0; i < 9; i++) response[i] = Serial.read();
  for(uint8_t i = 1; i < 8; i++) check += response[i];
  if ((255 - check) + 1 == response[8]) {
    gas = word(response[2], response[3]);
    vezesVazio = 0;
  }
  else vezesVazio++;

}
