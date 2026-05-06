#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

int buttonPin = 2;
bool lastState = HIGH;

int track = 1; // 当前播放编号（1~3）

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer初始化失败!");
    while (true);
  }

  myDFPlayer.volume(5);
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  // 检测按下瞬间
  if (lastState == HIGH && currentState == LOW) {

    myDFPlayer.play(track);  // 播放当前编号

    track++;  // 切换到下一段

    if (track > 3) {  // 超过3就回到1
      track = 1;
    }

    delay(300); // 防抖
  }

  lastState = currentState;
}