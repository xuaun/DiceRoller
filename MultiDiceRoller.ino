//Defines for 7-segment inputs
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
#define DP A2
#define B1 13
#define B2 9

//Functions headers
void rrrolando();
void setBlank();
void setZero();
void setOne();
void setTwo();
void setThree();
void setFour();
void setFive();
void setSix();
void setSeven();
void setEight();
void setNine();

long unsigned int seed{0};

//Variables
int selectDice(int);
int rollDice(int, int);
void displayNumber(int);

int diceoption{0};
int dice{4};
int readingB1{0};
int readingB2{0};
int number{0};

int b1State = 0;
int b2State = 0;
int b1LastState = 0;
int b3LastState = 0;

void setup() {
  //setting outputs
  for (int i = 2; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(DP, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  
  //acende os leds iniciais
  digitalWrite(10, HIGH);
  setFour();
  Serial.begin(9600);
  Serial.print(b1State);
  Serial.print(b2State);
  Serial.print(b1LastState);
  Serial.print(b3LastState);
  delay(1000);
}

void loop() {
  seed++;
  if(seed > 6000000) seed = 0;
  
  //choosing dice button state change 
  b1State = digitalRead(B1);
  if (b1State != b1LastState) {
    b1LastState = b1State;
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    if (b1State == HIGH){
      diceoption++;
      diceoption=diceoption%6;
    }
    dice = selectDice(diceoption);
    delay(50);
  }

  //diceRoll button change
  b2State = digitalRead(B2);
  if(b2State != b3LastState){
    b3LastState = b2State;
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    if (b2State == HIGH){
      rrrolando();
      number = rollDice(dice, seed);
    }
    displayNumber(number);
    delay(50);
  }
  
}

//////////////////////////////////////////////////////

// Funções responsaveis pela rolagem e escolha dos dados

void rrrolando(){
  setBlank();
  for (int j = 0; j<5; j++){
    for (int i = 2;i<8; i++){
      digitalWrite(i,HIGH);
      delay(50);
      digitalWrite(i,LOW);
    }
  }
  setEight();
  delay(200);
  setBlank();
  delay(200);
  setEight();
  delay(200);
  setBlank();
  delay(200);
}

int selectDice(int diceoption) {
  switch (diceoption) {
  case 0:
    setFour();
    return 4;
  case 1:
    setSix();
    return 6;
  case 2:
    setEight();
    return 8;
  case 3:
    setZero();
    return 10;
  case 4:
    setTwo();
    digitalWrite(A2, HIGH);
    return 12;
  case 5:
    setZero();
    digitalWrite(A2, HIGH);
    return 20;
  }
}

int rollDice(int dice, int t) {
  randomSeed(t);
  switch (dice) {
  case 4:
    return random(1, 5);

  case 6:
    return random(1, 7);

  case 8:
    return random(1, 9);

   case 10:
    return random(1, 11);
    
  case 12:
    return random(1, 13);

  case 20:
    return random(0, 20);
  }
}

void displayNumber(int n) {
  switch (n % 10) {
  case 0:
    setZero();
    break;
  case 1:
    setOne();
    break;
  case 2:
    setTwo();
    break;
  case 3:
    setThree();
    break;
  case 4:
    setFour();
    break;
  case 5:
    setFive();
    break;
  case 6:
    setSix();
    break;
  case 7:
    setSeven();
    break;
  case 8:
    setEight();
    break;
  case 9:
    setNine();
    break;
  }
  if ( n > 10) {
    digitalWrite(DP, HIGH);
  }
}

//////////////////////////////////////////////////////

// Funções responsaveis pelos leds

void setBlank() {
  digitalWrite(A2, LOW);
  for (int i = 2; i < 9; i++) {
    digitalWrite(i, LOW);
  }
}

void setZero() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
}

void setOne() {
  setBlank();
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void setTwo() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(D, HIGH);
}

void setThree() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(G, HIGH);
}

void setFour() {
  setBlank();
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void setFive() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
}

void setSix() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(G, HIGH);
}

void setSeven() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
}

void setEight() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void setNine() {
  setBlank();
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
