#include <Keypad.h> 
#include <Servo.h>

int tru=0; // 비밀번호가 맞는지 확인
int count=0;
char PW[4]={'1','2','3','A'}; //비밀번호
const byte ROWS = 4; 
const byte COLS = 4; 
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

int check = 0;  // 블루투스랑 사전에 핸드폰에서 open 눌렀는지 안눌렀는지 체크 / check = 1이면 비밀번호 맞았을 때 문 열도록 할게요 
int isopen = 0; // 실시간 상태 확인 / isopen = 1이면 문 열려있는 것 

char keys[ROWS][COLS] = { 
  {'1','2','3', 'A'}, 
  {'4','5','6', 'B'}, 
  {'7','8','9', 'C'}, 
  {'*','0','#', 'D'} 
}; 

Servo myservo; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 
 
void setup(){ 
  Serial.begin(9600); 
  myservo.attach(11);
} 
   
void loop(){ 
  char key = keypad.getKey(); // 키패드 입력받는 부분
   
  if (key)
  { 
      Serial.println(key);
      if(key==PW[count]) //입력번호와 비밀번호가 맞을시 count,tru++
      {
        count++;
        tru++;
      }
      
      else if(key!=PW[count])//입력번호와 비밀번호가 틀릴시 count만 ++
      {
        count++;
      }

      if(key=='#')//초기화버튼
       re();//초기화 함수

      if(count==4)//count개수가 비밀번호 개수와 같을 시
      {
        if(tru==4)
          Open();//성공함수
        else
          Close();//실패함수

        tru=0;
        count=0;
      }
      
      
     
  } 
} 


void Open()//성공했을시 모터를 돌려주며 성공메세지 보내기
{
      myservo.write(180); 
      Serial.println("open the door"); 
      isopen = 1;         
      //myservo.write(0); -> 문 닫기     
      //Serial.println("close the door");                          
}

void Close()//실패했을시 모터를 돌려주며 실패메세지 보내기
{
      myservo.write(0);
      Serial.println("close the door");                                   
}

void re()//비밀번호 입력중 #을 입력하면 비밀번호 입력중인 비밀번호 초기화
{ 
        tru=0;
        count=0;
        Serial.println("password reset");  
}