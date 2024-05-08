#include <Servo.h>// servo motor kütüphanesi
#include <NewPing.h>

//motor pinleri
#define SolMotorileri 5
#define SolMotorGeri 4
#define SagMotorileri 3
#define SagMotorGeri 2

//sensör pinleri
#define USTrigger 6
#define USEcho 7
#define Maksimum_uzaklik 100

Servo servo; //servo motor z                             
NewPing sonar(USTrigger, USEcho, Maksimum_uzaklik);//ultrasonik sensör tanımlama
//kullanılacak eleman tanımı
unsigned int uzaklik;
unsigned int on_uzaklik;
unsigned int sol_uzaklik;
unsigned int sag_uzaklik;
unsigned int zaman;

// program ilk çalıştığında sadece bir kez çalışacak programlar
void setup()
{
  Serial.begin(9600);
  //motor çıkışları
  pinMode(SolMotorileri, OUTPUT);
  pinMode(SolMotorGeri, OUTPUT);
  pinMode(SagMotorileri, OUTPUT);
  pinMode(SagMotorGeri, OUTPUT);
  servo.attach(8); //servo pin tanımı
}

// sonsuz döngü
void loop()
{
  delay(500);
  servo.write(90);
  sensor_olcum();
  on_uzaklik = uzaklik;
  Serial.print("On uzaklik: " + String(on_uzaklik) + "\n");
  if(on_uzaklik > 35 || on_uzaklik == 0)
  {
    ileri();
    Serial.print("One git, On uzaklik: " + String(on_uzaklik) + "\n");
  }
  else
  {
    dur();
    servo.write(180);
    delay(500);
    sensor_olcum();
    sol_uzaklik = uzaklik;
    Serial.print("Sol uzaklik: " + String(sol_uzaklik) + "\n");
    servo.write(0);
    delay(500);
    sensor_olcum();
    sag_uzaklik = uzaklik;
    Serial.print("Sag uzaklik: " + String(sag_uzaklik) + "\n");
    servo.write(90);
    delay(300);
    if((sol_uzaklik < 15) && (sag_uzaklik < 15))
    {
      Serial.print("Geri git\n");
      geri();
    }
    else if (sag_uzaklik > sol_uzaklik)
    {
      Serial.print("Saga git\n");
      sag();
      delay(200);
      ileri();
    }
    else if (sol_uzaklik > sag_uzaklik)
    {
      Serial.print("Sola git\n");
      sol();
      delay(200);
      ileri();
    } else {
      Serial.print("Geri git\n");
      geri();
    }
  }
}
  
// robotun yön komutları
void ileri()
{
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);
}
  
void geri()
{
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}
  
void sol()
{
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SolMotorGeri, HIGH);
  digitalWrite(SagMotorGeri, LOW);
  digitalWrite(SagMotorileri, HIGH);
}
  
void sag()
{
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, HIGH);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, HIGH);
}
  
void dur()
{
  digitalWrite(SolMotorGeri, LOW);
  digitalWrite(SolMotorileri, LOW);
  digitalWrite(SagMotorileri, LOW);
  digitalWrite(SagMotorGeri, LOW);
}
// sensörün mesafe ölçümü
void sensor_olcum()
{
  delay(50);
  zaman = sonar.ping();
  uzaklik = zaman / US_ROUNDTRIP_CM;
}