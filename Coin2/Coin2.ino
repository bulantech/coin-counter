/*
 * 
 * 25วินาที
 * 1บาทรีเลย์ทำงาน 25วินาที
 * 1บาท 1พัล
 * 
 */

void ICACHE_RAM_ATTR doCounter();

const int Relay1 = D0; // กำหนดขาใช้งาน
const int sensor = D1; 

boolean isCounter = false;
int count = 0;
int countBuf = 0;
int countDelay = 0;
const int dalayVal = 250; // milisec
//bool firstInsert = false;
int firstInsertCount = 0; // 250ms per count, 4 count = 1 sec

void setup() {
  pinMode(Relay1, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา D0 เป็น OUTPUT
  digitalWrite(Relay1, HIGH);
  pinMode(sensor, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensor), doCounter, FALLING);
  Serial.begin(9600);
  
  Serial.println("======================");
  Serial.print("จำนวนเงิน: ");
  Serial.print(countBuf);
  Serial.println(" บาท");
  Serial.println();
}

void loop() {
  if(countBuf != count) {
    countBuf = count;
    Serial.print("จำนวนเงิน: ");
    Serial.print(countBuf);
    Serial.println(" บาท");
    Serial.println();
    Serial.printf("countDelay: %d \r\n", countDelay);
  }

  if(firstInsertCount) {
    firstInsertCount--;
    delay(250);
    return;
  }
  
  if(countDelay) {
    countDelay -= dalayVal;
    digitalWrite(Relay1, LOW); //close, on

    if(countDelay) {
      int modulo = countDelay % (dalayVal*100);
      if(!modulo) count--;  
    } else {
      count = 0;
    }  
    
  } else {   
    digitalWrite(Relay1, HIGH); //open, off
  }

  delay(dalayVal);

}

void doCounter() {
  count++; 
  countDelay = countDelay+(dalayVal*100); // 1บาทรีเลย์ทำงาน 25วินาที 
  if(count==1) {
    firstInsertCount = 40; // 40 count = 10 sec
  }
}
