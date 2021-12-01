#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = A0; 
IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo;

check = 0;  // 블루투스랑 사전에 핸드폰에서 open 눌렀는지 안눌렀는지 체크 / check = 1이면 비밀번호 맞았을 때 문 열도록 할게요 
isopen = 0; // 실시간 상태 확인 / isopen = 1이면 문 열려있는 것 
        
void setup()
{
    Serial.begin(9600);
    myservo.attach(11);
    irrecv.enableIRIn(); // Start the receiver
}

void loop() {
    if (irrecv.decode(&results)) {
        int data = results.value;
      
        Serial.println(data,HEX);
        Serial.println(data);
        
        if(data == -23971 && check == 1){
          go();
        }
        else{
          Serial.println("fail");
        }
        
        irrecv.resume(); // Receive the next value
    }
}

void go(){  // 문 여는 함수
  myservo.write(180);
  isopen = 1;
  Serial.println("open the door");
  // myservo.write(0); -> 문 닫기 
}
