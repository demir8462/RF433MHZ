#include <RH_ASK.h>
RH_ASK driver;
char PAKET[15];
char PAKETLER[10][15];
void setup() {
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  if(driver.init())
  {
    Serial.println("BAŞARIYLA BASLATILDI");
    digitalWrite(6,HIGH);
  }

}
int PACKAGECOUNTER=0;
void veriYolla(const char * str) // STR MUST BE 14 CHARS AT MAX
{
  int len = strlen(str);
  for(int i =1;i<14;i++)
  {
      if(i < len)
      {
        PAKET[i] = str[i-1];
      }else
      {
        PAKET[i] = 0;
      }
    
  }
  PAKET[0] = PACKAGECOUNTER;
  PACKAGECOUNTER++;
  if(PACKAGECOUNTER == 10)
  {
    PACKAGECOUNTER = 0;
  }
  driver.send((uint8_t*)PAKET,sizeof(PAKET));
  driver.waitPacketSent();
}
bool PAKETVARMI[10] = {false,false,false,false,false,false,false,false,false,false};
void veriAl()
{
  uint8_t BUFFER[15];
  uint8_t BUFL = sizeof(BUFFER);
  if(driver.recv(BUFFER, &BUFL))
  {
    int index = BUFFER[14];
    strcpy(PAKETLER[index],BUFFER);
    PAKETVARMI[index] = true;
  }
}
int sira =0;
char *veriGetir()
{
  while(1)
  {
    if(PAKETVARMI[sira])
  {
    PAKETVARMI[sira] = false;
    sira++;
    if(sira == 10)
    {
      sira = 0;
    }
    return PAKETLER[sira];
  }
  delay(100);
  }
}
void loop() {
  veriYolla("Selamm !!!!!");

}
