#define LED_S_R 2
#define LED_S_Y 3
#define LED_S_G 4
#define SOUTH_BUTTON_PIN 10

#define LED_W_R 5
#define LED_W_Y 6
#define LED_W_G 7
#define WEST_BUTTON_PIN 11

#define LED_w_R 8
#define LED_w_G 9
#define WALK_BUTTON_PIN 12

#define goW 0
#define waitW 1
#define goS 2
#define waitS 3
#define gow1 4
#define gow2 5
#define waitw1 6
#define gow3 7
#define waitw2 8
#define gow4 9
#define waitw3 10

struct State {
  unsigned long ST_Out;
  // 6-bit pattern to street output 
  unsigned long Time;      
  // delay in msunits
  unsigned long Next[8];
}; // next state for inputs 0,1,2,3
typedef const struct State SType;
SType FSM[11]={
  {B10110011,2000,{goW,goW,waitW,waitW,waitW,waitW,waitW,waitW}},
  {B10110101,300,{goS,goS,goS,goS,gow1,gow1,goS,goS}},
  {B10011110,2000,{goS,waitS,goS,waitS,waitS,waitS,waitS,waitS}},
  {B10101110,300,{goW,goW,goW,goW,gow1,goW,gow1,gow1}},
  {B01110110,2000,{gow1,waitw3,waitw3,waitw3,gow1,waitw3,waitw3,waitw3}},
  {B11110110,300,{gow1,goW,goS,goW,gow1,goW,goS,goW}},
  {B01110110,300,{gow2,gow2,gow2,gow2,gow2,gow2,gow2,gow2}},
  {B11110110,300,{waitw1,waitw1,waitw1,waitw1,waitw1,waitw1,waitw1,waitw1}},
  {B01110110,300,{gow3,gow3,gow3,gow3,gow3,gow3,gow3,gow3}},
  {B11110110,300,{waitw2,waitw2,waitw2,waitw2,waitw2,waitw2,waitw2,waitw2}},
  {B01110110,300,{gow4,gow4,gow4,gow4,gow4,gow4,gow4,gow4}}
};
unsigned long S=0;
// index to the current state   
void setup() {
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT);  
  pinMode(WEST_BUTTON_PIN, INPUT);  
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT);  
  pinMode(SOUTH_BUTTON_PIN, INPUT);
  pinMode(LED_w_R, OUTPUT);
  pinMode(LED_w_G, OUTPUT);  
  pinMode(WALK_BUTTON_PIN, INPUT);
}
int input,input1,input2,input3;
int test = 0;

void loop() {
  digitalWrite(LED_W_R, FSM[S].ST_Out& B00000001);
  digitalWrite(LED_W_Y, FSM[S].ST_Out& B00000010);
  digitalWrite(LED_W_G, FSM[S].ST_Out& B00000100);
  digitalWrite(LED_S_R, FSM[S].ST_Out& B00001000);
  digitalWrite(LED_S_Y, FSM[S].ST_Out& B00010000);
  digitalWrite(LED_S_G, FSM[S].ST_Out& B00100000);
  digitalWrite(LED_w_R, FSM[S].ST_Out& B01000000);
  digitalWrite(LED_w_G, FSM[S].ST_Out& B10000000);
  delay(FSM[S].Time);
  if(S == 0 || S == 2 || S == 4){
    test = 0;
    input = 0;
  input1 = digitalRead(WEST_BUTTON_PIN);
  input2 = digitalRead(SOUTH_BUTTON_PIN);
  input3 = digitalRead(WALK_BUTTON_PIN);
  input = input3*4+input2*2+input1;
  if(input == 0 ){
    if(test!=0){
      input = test;
    }
  }
  if(input != 0){
    test = input;
  }
  }
  S = FSM[S].Next[input];
}
