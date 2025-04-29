#include <NTP.h>  // https://github.com/sstaub/NTP/
#include <WiFi.h>
#include <WiFiUdp.h>

#include "secrets.h" // Secrets file for wifi data - provide your own or manually replace below
//----Example secrets.h----
//#define SECRET_SSID "ssid"
//#define SECRET_PASS "wifipassword"
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

WiFiUDP ntpUDP;

NTP ntp(ntpUDP);

// ESP32 pin numbering - reversed numbers due to mistake in v0.1 PCB
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

int hours;
int minutes;

int zero;
int one;
int two;
int three;

IPAddress ip;

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

  // Set CPU freq (240, 160, 80, 40, 20, 10 MHz)
  setCpuFrequencyMhz(80);

  for (char i = 0; i < 4; i++) {
    digitalWrite(A[i], HIGH);
    digitalWrite(B[i], HIGH);
    digitalWrite(C[i], HIGH);
    digitalWrite(D[i], HIGH);
  }

  // WiFi
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // Digit test
  // Write each number to be displayed j to each digit i
  for (int j = 0; j <= 9; j++) {
    for (int i = 0; i <= 3; i++) {
      writenumber(i, j);
    }
    delay(500);
  }

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    for (int i = 0; i <= 3; i++) {
      writenumber(i, 0);
    }
    delay(500);
    for (int i = 0; i <= 3; i++) {
      writenumber(i, 1);
    }
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  ip = WiFi.localIP();
  Serial.println(ip);

  for (int i = 0; i <= 3; i++) {
    writeByte(ip[i]);
    delay(2000);
  }

  // EU CET - same format as used by Timezone library, which can be useful with other time sources
  ntp.ruleDST("CEST", Last, Sun, Mar, 2, +120);  //Standard time = UTC + 2 hours
  ntp.ruleSTD("CET", Last, Sun, Oct, 3, +60);    //Daylight time = UTC + 1 hours
  ntp.begin();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.reconnect();
  }

  ntp.update();

  hours = ntp.hours();
  minutes = ntp.minutes();

  Serial.print("Hours: ");
  Serial.println(hours);
  Serial.print("Minutes: ");
  Serial.println(minutes);

  zero = (hours / 10) % 10;
  one = hours % 10;
  two = (minutes / 10) % 10;
  three = minutes % 10;

  writenumber(0, zero);
  writenumber(1, one);
  writenumber(2, two);
  writenumber(3, three);

  Serial.println(ip[0]);

  delay(1000);
}

void writeByte(int a) {
  zero = 0;
  three = a % 10;
  two = a / 10 % 10;
  one = a / 100 % 10;

  Serial.println(zero);
  Serial.println(one);
  Serial.println(two);
  Serial.println(three);

  writenumber(0, zero);
  writenumber(1, one);
  writenumber(2, two);
  writenumber(3, three);
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
