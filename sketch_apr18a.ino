// Tüm Hakları Saklıdır © 2021
//          _____  _____  _    _ _____ _   _  ____    _______ _    _ _____  _  __  ____       _______ _    _ 
//    /\   |  __ \|  __ \| |  | |_   _| \ | |/ __ \  |__   __| |  | |  __ \| |/ / |  _ \   /\|__   __| |  | |
//   /  \  | |__) | |  | | |  | | | | |  \| | |  | |    | |  | |  | | |__) | ' /  | |_) | /  \  | |  | |  | |
//  / /\ \ |  _  /| |  | | |  | | | | | . ` | |  | |    | |  | |  | |  _  /|  <   |  _ < / /\ \ | |  | |  | |
// / ____ \| | \ \| |__| | |__| |_| |_| |\  | |__| |    | |  | |__| | | \ \| . \  | |_) / ____ \| |  | |__| |
// /_/    \_\_|  \_\_____/ \____/|_____|_| \_|\____/     |_|   \____/|_|  \_\_|\_\ |____/_/    \_\_|   \____/ 
//
// Abone Ol Beğen Paylaş



#include <LiquidCrystal_I2C_AvrI2C.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>
int RST_PIN = 9; //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 10; //RC522 modülü chip select pinini tanımlıyoruz.
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);  
int kirmiziLed = 6;
int yesilLed = 7;

Servo motor; //Servo motor için değişken oluşturuyoruz.
MFRC522 rfid(SS_PIN, RST_PIN); //RC522 modülü ayarlarını yapıyoruz.
byte ID[4] = {
  195,
  118,
  114,
  2
}; //Yetkili kart ID'sini tanımlıyoruz. 

void setup() {


  lcd.begin(); //lcd'yi başlatıyoruz
  lcd.backlight(); //lcd arka ışığını açıyoruz.
  lcd.setCursor(0,0); //imleci 1.satır ilk karaktere getiriyoruz.
  lcd.print(" PERSONEL TAKiP"); //İlk satıra yazalım
  lcd.setCursor(0,1); //imleci 2.satır ilk karaktere getiriyoruz.
  lcd.print("   BATU AKYAR"); //İlk satıra yazalım  
  pinMode(kirmiziLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);
 
  motor.attach(servoPin); //Servo motor pinini motor değişkeni ile ilişkilendiriyoruz.
  Serial.begin(9600); //Seri haberleşmeyi başlatıyoruz.
  SPI.begin(); //SPI iletişimini başlatıyoruz.
  rfid.PCD_Init(); //RC522 modülünü başlatıyoruz.

    digitalWrite(yesilLed, LOW);
     
}
void loop() {
    digitalWrite(yesilLed, LOW);
   
  if (!rfid.PICC_IsNewCardPresent()) //Yeni kartın okunmasını bekliyoruz.
    return;
  if (!rfid.PICC_ReadCardSerial()) //Kart okunmadığı zaman bekliyoruz.
    return;
  if (rfid.uid.uidByte[0] == ID[0] && //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] &&
    rfid.uid.uidByte[2] == ID[2] &&
    rfid.uid.uidByte[3] == ID[3]) {
        digitalWrite(yesilLed, HIGH);
lcd.clear();
  lcd.setCursor(0,0); //imleci 1.satır ilk karaktere getiriyoruz.
  lcd.print(" GiRiS BASARILI"); //İlk satıra yazalım
  lcd.setCursor(0,1); //imleci 2.satır ilk karaktere getiriyoruz.
  lcd.print("  HOS GELDiNiZ"); //İlk satıra yazalım 

         
    delay(3000);
    lcd.clear();
  lcd.print(" PERSONEL TAKiP"); //İlk satıra yazalım
  lcd.setCursor(0,1); //imleci 2.satır ilk karaktere getiriyoruz.
  lcd.print("   BATU AKYAR"); //İlk satıra yazalım  


    
    digitalWrite(yesilLed, LOW);
    
    delay(500);
    motor.write(180); //Servo motoru 180 dereceye getiriyoruz.
    delay(3000);
    motor.write(0);
  } else { //Yetkisiz girişte içerideki komutlar çalıştırılır.
    Serial.println("Yetkisiz Kart");

    lcd.clear();
  lcd.setCursor(0,0); //imleci 1.satır ilk karaktere getiriyoruz.
  lcd.print("  GiRiS HATALI"); //İlk satıra yazalım
  lcd.setCursor(0,1); //imleci 2.satır ilk karaktere getiriyoruz.
  lcd.print("TEKRAR DENEYiNiZ"); //İlk satıra yazalım 

  
digitalWrite(yesilLed, LOW);
   digitalWrite(kirmiziLed, HIGH);
   
        delay(3000);
        lcd.clear();
  lcd.print(" PERSONEL TAKiP"); //İlk satıra yazalım
  lcd.setCursor(0,1); //imleci 2.satır ilk karaktere getiriyoruz.
  lcd.print("   BATU AKYAR"); //İlk satıra yazalım  

  
    digitalWrite(kirmiziLed, LOW);
 
    delay(500);
   digitalWrite(kirmiziLed, HIGH);
    delay(500);
    digitalWrite(kirmiziLed, LOW);
       
  }
  rfid.PICC_HaltA();
}
