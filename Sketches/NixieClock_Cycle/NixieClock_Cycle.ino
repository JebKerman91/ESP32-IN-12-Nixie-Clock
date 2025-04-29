// ESP32 pin numbering
#define A_1 A7
#define B_1 A6
#define C_1 A5
#define D_1 A4
#define A_2 A3
#define B_2 A2
#define C_2 A1
#define D_2 A0
#define A_3 D9
#define B_3 D8
#define C_3 D7
#define D_3 D6
#define A_4 D5
#define B_4 D4
#define C_4 D3
#define D_4 D2

char A[4] = { A_1, A_2, A_3, A_4 };
char B[4] = { B_1, B_2, B_3, B_4 };
char C[4] = { C_1, C_2, C_3, C_4 };
char D[4] = { D_1, D_2, D_3, D_4 };

int incomingByte = 0;  // for incoming serial data
int numberToDisplay = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(A_1, OUTPUT);
  pinMode(B_1, OUTPUT);
  pinMode(C_1, OUTPUT);
  pinMode(D_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(C_2, OUTPUT);
  pinMode(D_2, OUTPUT);
  pinMode(A_3, OUTPUT);
  pinMode(B_3, OUTPUT);
  pinMode(C_3, OUTPUT);
  pinMode(D_3, OUTPUT);
  pinMode(A_4, OUTPUT);
  pinMode(B_4, OUTPUT);
  pinMode(C_4, OUTPUT);
  pinMode(D_4, OUTPUT);

  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], HIGH);
    digitalWrite(B[i], HIGH);
    digitalWrite(C[i], HIGH);
    digitalWrite(D[i], HIGH);
  }

  Serial.begin(9600);
}

void loop() {
  for (int numberToDisplay = 0; numberToDisplay < 10; numberToDisplay++) {
    for (int m = 0; m < 4; m++) {
      writenumber(m, numberToDisplay);
    }
    delay(1000);
  }
}

void writenumber(int a, int b) {
  switch (b) {
    case 0:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 9:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 8:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], HIGH);
      break;
    case 7:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 6:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 5:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 4:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], HIGH);
      digitalWrite(D[a], LOW);
      break;
    case 3:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 2:
      digitalWrite(A[a], LOW);
      digitalWrite(B[a], HIGH);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
    case 1:
      digitalWrite(A[a], HIGH);
      digitalWrite(B[a], LOW);
      digitalWrite(C[a], LOW);
      digitalWrite(D[a], LOW);
      break;
  }
}