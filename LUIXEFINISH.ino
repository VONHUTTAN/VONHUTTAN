int trig = 6;
int echo = 5;
int khoangcach;
long Duration;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousTimeLCD = 0;  
const long intervalLCD = 500;    
bool textOn = true;

int loa = 13;
bool loaon = true;
unsigned long timeloaxanh = 500;
unsigned long timeloavang = 100;
unsigned long timebatloa = 0;

int ledxanh = 12;
int ledvang = 9;
int leddo = 10;
unsigned long ledtimevang = 200;
unsigned long ledtimedo = 100;
unsigned long timebatden = 0;
bool denon = true;

int trangthai = -1;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  lcd.init();           
  lcd.backlight();     
  lcd.setCursor(0, 0);  
  lcd.print("Khoi dong...");
  delay(1000);
  lcd.clear();

  pinMode(loa, OUTPUT);
  pinMode(ledxanh, OUTPUT);
  pinMode(ledvang, OUTPUT);
  pinMode(leddo, OUTPUT);

 
}

void loop() {
  distance();

  if (khoangcach > 30) {
    if (trangthai != 0) {
      trangthai = 0;
      lcd.clear();
      tatca();
    }
    manhinhxanh();
    amthanhxanh();
    denxanh();
  }
  else if (khoangcach > 15 && khoangcach <= 30) {
    if (trangthai != 1) {
      trangthai = 1;
      lcd.clear();
      tatca();
    }
    manhinhvang();
    amthanhvang();
    denvang();
  }
  else if (khoangcach <= 15) {
    if (trangthai != 2) {
      trangthai = 2;
      lcd.clear();
      tatca();
    }
    manhinhdo1();
    amthanhdo();
    dendo();
  }

  delay(50);
}

void distance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  Duration = pulseIn(echo, HIGH);
  khoangcach = Duration * 0.034 / 2;
  
}

void amthanhxanh() {
  unsigned long curr = millis();
  if (curr - timebatloa >= timeloaxanh) {
    timebatloa = curr;
    if (loaon) {
      digitalWrite(loa, HIGH);
    } else {
      digitalWrite(loa, LOW);
    }
    loaon = !loaon;
  }
}

void amthanhvang() {
  unsigned long curr = millis();
  if (curr - timebatloa >= timeloavang) {
    timebatloa = curr;
    if (loaon) {
      digitalWrite(loa, HIGH);
    } else {
      digitalWrite(loa, LOW);
    }
    loaon = !loaon;
  }
}

void amthanhdo() {
  digitalWrite(loa, HIGH);
}

void manhinhxanh() {
  lcd.setCursor(0, 0);       
  lcd.print("DANG LUI XE ^o^   ");
  lcd.setCursor(3, 1);  
  lcd.print(khoangcach);
  lcd.print(" cm   ");
} 

void manhinhvang() {
  unsigned long now = millis();
  if (now - previousTimeLCD >= intervalLCD) {
    previousTimeLCD = now;
    if (textOn) {
      lcd.setCursor(0, 0);       
      lcd.print("DANG LUI XE ^o^   ");
      lcd.setCursor(0, 1);
      lcd.print("Chu y !");
      lcd.setCursor(9, 1);  
      lcd.print(khoangcach);
      lcd.print("cm ");
    } else {
      lcd.setCursor(0, 1);       
      lcd.print("                "); 
    }
    textOn = !textOn;
  }
}

void manhinhdo1() {
  unsigned long now = millis();
  if (now - previousTimeLCD >= intervalLCD) {
    previousTimeLCD = now;
    if (textOn) {
      lcd.setCursor(2, 0);       
      lcd.print("CHU Y !!!");
      lcd.setCursor(6, 1);  
      lcd.print("STOP");
      
    } else {
    
      lcd.setCursor(6, 1);
      lcd.print("                ");
    }
    textOn = !textOn;
  }
}

void denxanh() {
  digitalWrite(ledxanh, HIGH);
  digitalWrite(ledvang, LOW);
  digitalWrite(leddo, LOW);
}

void denvang() {
  unsigned long now = millis();
  if (now - timebatden >= ledtimevang) {
    timebatden = now;
    if (denon) {
      digitalWrite(ledvang, HIGH);
    } else {
      digitalWrite(ledvang, LOW);
    }
    denon = !denon;
  }
}

void dendo() {
  unsigned long now = millis();
  if (now - timebatden >= ledtimedo) {
    timebatden = now;
    if (denon) {
      digitalWrite(leddo, HIGH);
    } else {
      digitalWrite(leddo, LOW);
    }
    denon = !denon;
  }
}

void tatca() {
  digitalWrite(ledxanh, LOW);
  digitalWrite(ledvang, LOW);
  digitalWrite(leddo, LOW);
  digitalWrite(loa, LOW);
}