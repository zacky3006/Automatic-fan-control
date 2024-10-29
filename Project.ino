#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int relayPin = 7;     // Pin ที่เชื่อมต่อกับ Relay
float tempThreshold = 30.0;  // อุณหภูมิที่พัดลมจะเปิด (ปรับได้)

void setup() {
  pinMode(relayPin, OUTPUT);   // ตั้งค่า pin relay เป็น output
  digitalWrite(relayPin, HIGH); // ปิดพัดลมในตอนเริ่มต้น
  dht.begin();                 // เริ่มต้นการทำงานของ DHT
  Serial.begin(9600);          // เริ่มต้น serial communication เพื่อดูค่า
}

void loop() {
  // อ่านค่าอุณหภูมิจากเซ็นเซอร์
  float temperature = dht.readTemperature();
  
  // ตรวจสอบว่าการอ่านถูกต้อง
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // แสดงค่าอุณหภูมิใน Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // ควบคุมพัดลมตามอุณหภูมิ
  if (temperature >= tempThreshold) {
    digitalWrite(relayPin, LOW);  // เปิดพัดลม
  } else {
    digitalWrite(relayPin, HIGH);   // ปิดพัดลม
  }

  delay(2000); // หน่วงเวลา 2 วินาทีเพื่ออ่านค่าใหม่
}
