#include <Arduino.h>
unsigned long g_millis=0; int g_pin[64]={0}; int g_duty[16]={0}; float g_simCm[64]={0};
SerialStub Serial; 
#include <WiFi.h>
WiFiStub WiFi;
#include "main.cpp"
#include <cassert>
int fails=0, passes=0;
#define CHECK(c,msg) do{ if(c){passes++; printf("  PASS  %s\n",msg);} else {fails++; printf("  FAIL  %s\n",msg);} }while(0)
void send(const char* j){ webSocket.cb(0,WStype_TEXT,(uint8_t*)j,strlen(j)); }
// jalankan loop selama ms, kirim pesan joystick tiap 100 ms kalau js != nullptr
void run(unsigned long ms, const char* js){
  unsigned long end=g_millis+ms, nextJs=g_millis;
  while(g_millis<end){ if(js && g_millis>=nextJs){ send(js); nextJs+=100; } loop(); g_millis+=5; }
}
void setDist(float bL,float bR,float fL,float fR){ g_simCm[PIN_ECHO_BIN_L]=bL; g_simCm[PIN_ECHO_BIN_R]=bR; g_simCm[PIN_ECHO_FRONT_L]=fL; g_simCm[PIN_ECHO_FRONT_R]=fR; }
bool has(const char* s){ return webSocket.last.find(s)!=std::string::npos; }
int main(){
  setDist(25,25,200,200);
  // simulasikan pin motor "HIGH mengambang" sebelum setup
  g_pin[PIN_IN1]=g_pin[PIN_IN2]=g_pin[PIN_IN3]=g_pin[PIN_IN4]=1; g_duty[0]=g_duty[1]=255;
  setup();
  printf("\n[1] Boot\n");
  CHECK(g_pin[PIN_IN1]==0&&g_pin[PIN_IN2]==0&&g_pin[PIN_IN3]==0&&g_pin[PIN_IN4]==0&&g_duty[0]==0&&g_duty[1]==0,"motor terkunci mati setelah setup()");
  CHECK(httpServer.root!=nullptr,"halaman UI terdaftar di '/'");
  httpServer.root(); CHECK(httpServer.sentBytes>20000,"webpage.h terkirim (>20 KB)");

  printf("\n[2] Kendali joystick -> L298N\n");
  webSocket.clients=1; webSocket.cb(0,WStype_CONNECTED,nullptr,0);
  run(80,"{\"type\":\"joystick\",\"x\":0,\"y\":-1}");
  CHECK(g_duty[0]>0&&g_duty[0]<255,"akselerasi bertahap (belum langsung 255 setelah 80 ms)");
  run(600,"{\"type\":\"joystick\",\"x\":0,\"y\":-1}");
  CHECK(g_pin[PIN_IN1]==1&&g_pin[PIN_IN2]==0&&g_pin[PIN_IN3]==1&&g_pin[PIN_IN4]==0,"MAJU: IN1=H IN2=L, IN3=H IN4=L");
  CHECK(g_duty[0]==255&&g_duty[1]==255,"MAJU penuh: ENA=ENB=255");
  run(300,"{\"type\":\"joystick\",\"x\":0,\"y\":1}");
  CHECK(g_pin[PIN_IN1]==0&&g_pin[PIN_IN2]==1&&g_pin[PIN_IN3]==0&&g_pin[PIN_IN4]==1,"MUNDUR: IN1=L IN2=H, IN3=L IN4=H");
  run(400,"{\"type\":\"joystick\",\"x\":0.5,\"y\":-1}");
  CHECK(g_duty[0]>g_duty[1],"joystick KANAN: motor kiri lebih kencang (belok kanan)");
  run(400,"{\"type\":\"joystick\",\"x\":-0.5,\"y\":-1}");
  CHECK(g_duty[1]>g_duty[0],"joystick KIRI: motor kanan lebih kencang (belok kiri)");
  run(400,"{\"type\":\"joystick\",\"x\":1,\"y\":0}");
  CHECK(g_pin[PIN_IN1]==1&&g_pin[PIN_IN2]==0&&g_pin[PIN_IN3]==0&&g_pin[PIN_IN4]==1,"putar di tempat ke kanan: kiri maju, kanan mundur");
  run(200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(g_duty[0]==0&&g_duty[1]==0&&g_pin[PIN_IN1]==0&&g_pin[PIN_IN2]==0,"joystick dilepas: motor berhenti");
  CHECK(has("\"motorL\":0")&&has("\"type\":\"telemetry\""),"telemetry mengirim motorL/motorR");

  printf("\n[3] Failsafe\n");
  run(300,"{\"type\":\"joystick\",\"x\":0,\"y\":-1}");
  run(500,nullptr); CHECK(g_duty[0]>0,"masih jalan 500 ms tanpa pesan (< 600 ms)");
  run(200,nullptr); CHECK(g_duty[0]==0&&g_duty[1]==0,"berhenti setelah >600 ms tanpa pesan dari HP");
  CHECK(beepUntil>g_millis-200,"buzzer bunyi saat failsafe");
  run(300,"{\"type\":\"joystick\",\"x\":0,\"y\":-1}"); CHECK(g_duty[0]==255,"jalan lagi begitu pesan masuk kembali");
  run(100,"{\"type\":\"joystick\",\"x\":0,\"y\":-1}");
  webSocket.clients=0; webSocket.cb(0,WStype_DISCONNECTED,nullptr,0); loop();
  CHECK(g_duty[0]==0&&g_duty[1]==0,"HP disconnect: motor langsung berhenti");
  webSocket.clients=1;

  printf("\n[4] Sensor HALANGAN (depan, kiri & kanan sendiri-sendiri, <= 40 cm)\n");
  setDist(25,25,35,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(obsL&&!obsR,"depan-kiri 35 cm, depan-kanan 200 cm -> hanya HALANGAN KIRI");
  CHECK(has("\"obsL\":true")&&has("\"obsR\":false")&&has("\"distFL\":35"),"telemetry: obsL=true obsR=false distFL=35");
  setDist(25,25,200,38); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!obsL&&obsR,"depan-kiri 200 cm, depan-kanan 38 cm -> hanya HALANGAN KANAN");
  setDist(25,25,40,40); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(obsL&&obsR,"keduanya tepat 40 cm -> KIRI & KANAN terdeteksi");
  setDist(25,25,41,41); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!obsL&&!obsR,"keduanya 41 cm -> aman");
  setDist(25,25,0,0); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!obsL&&!obsR,"tidak ada pantulan (timeout) -> dianggap aman (400 cm)");

  printf("\n[5] Sensor SAMPAH (bak, penuh kalau KEDUANYA <= 6 cm / ~5 cm)\n");
  setDist(5,20,200,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!binFull,"bak-kiri 5 cm, bak-kanan 20 cm -> belum penuh (baru satu sisi)");
  setDist(5,5,200,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(binFull&&has("\"binFull\":true"),"bak-kiri 5 cm, bak-kanan 5 cm -> PENUH");
  setDist(6,6,200,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(binFull,"keduanya 6 cm -> PENUH (toleransi +1 cm)");
  setDist(8,8,200,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!binFull,"keduanya 8 cm -> belum penuh");

  printf("\n[6] Filter glitch & buzzer\n");
  setDist(25,25,200,200); run(1200,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  g_simCm[PIN_ECHO_FRONT_L]=10; run(60,"{\"type\":\"joystick\",\"x\":0,\"y\":0}"); run(180,"{\"type\":\"joystick\",\"x\":0,\"y\":0}"); g_simCm[PIN_ECHO_FRONT_L]=200;
  run(1000,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(!obsL,"pembacaan palsu sekali (glitch) tidak memicu halangan");
  send("{\"type\":\"buzzer\",\"state\":true}"); run(50,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(g_pin[PIN_BUZZER]==(BUZZER_ACTIVE_LOW?0:1),"tombol buzzer ditekan -> buzzer ON (level aktif sesuai config)");
  send("{\"type\":\"buzzer\",\"state\":false}"); run(50,"{\"type\":\"joystick\",\"x\":0,\"y\":0}");
  CHECK(g_pin[PIN_BUZZER]==(BUZZER_ACTIVE_LOW?1:0),"tombol buzzer dilepas -> buzzer OFF");

  #ifdef ARCA_PCB_V1
  printf("\n[varian PIN: PCB ARCA MAIN v1]\n");
#else
  printf("\n[varian PIN: rakit kabel]\n");
#endif
  printf("HASIL: %d lulus, %d gagal\n",passes,fails);
  printf("contoh telemetry: %s\n",webSocket.last.c_str());
  return fails?1:0;
}
