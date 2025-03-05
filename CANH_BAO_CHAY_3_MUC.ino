#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);

#include <SoftwareSerial.h>
// Khai báo đối tượng SoftwareSerial
SoftwareSerial sim800l(10,11); // RX, TX
#define coi 7
int muc1 = 35;
int muc2 = 40;
int muc3 = 45;
bool tt = false;
bool tt1 = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  sim800l.begin(9600);
  pinMode(coi, OUTPUT);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  dht.begin();
  delay(10000);
  Serial.println("Initializing SIM800L...");
  sim800l.println("AT");
  delay(1000);

  // Đặt chế độ văn bản
  sim800l.println("AT+CMGF=1");
  delay(1000);
}

void loop() {
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do:      *C");
  lcd.setCursor(10, 0);
  lcd.print(t);
  

  if(t > muc1){
    lcd.setCursor(0, 1);
    lcd.print("NHIET DO QUA CAO");
  }
  else {
  lcd.setCursor(0, 1);
    lcd.print("               ");
}
  if(t > muc2 && tt1 == false){
    digitalWrite(coi, HIGH);
  guitinnhan1();
    tt1 = true;
  }
  if(t < muc2){
    tt = false;
     digitalWrite(coi, LOW);}
  if(t > muc3 && tt == false){
    guitinnhan();
    tt = true;
  }
  if(t < muc3) tt = false;
  delay(100);
}

void guitinnhan() {
  // Đặt địa chỉ số điện thoại để gửi tin nhắn
  sim800l.println("AT+CMGS=\"+84385441135\""); // Thay số điện thoại bằng số muốn gửi
  delay(1000);
  // Nội dung tin nhắn
  sim800l.println("CANH BAO: PHAT HIEN NHIET DO VUOT QUA MUC 3");
  delay(1000);

  // Gửi Ctrl+Z để kết thúc tin nhắn và gửi đi
  sim800l.write(26);
}
void guitinnhan1() {
  // Đặt địa chỉ số điện thoại để gửi tin nhắn
  sim800l.println("AT+CMGS=\"+84385441135\""); // Thay số điện thoại bằng số muốn gửi
  delay(1000);
  // Nội dung tin nhắn
  sim800l.println("CANH BAO: PHAT HIEN NHIET DO VUOT QUA MUC 2");
  delay(1000);

  // Gửi Ctrl+Z để kết thúc tin nhắn và gửi đi
  sim800l.write(26);
}
