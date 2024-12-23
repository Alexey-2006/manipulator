#include <SoftwareSerial.h>
SoftwareSerial blutoooth(10, 11);
#include <Wire.h>                 //  Подключаем библиотеку для работы с аппаратной шиной I2C, до подключения библиотеки iarduino_MultiServo.
#include <iarduino_MultiServo.h>  //  Подключаем библиотеку iarduino_MultiServo

enum MoveCommand {
  Undefined,
  StepForward,
  StepBackward,
  MoveGradus
};

iarduino_MultiServo MSS;  //  Создаём объект MSS, для работы с библиотекой
char bt_input;
int angle_0 = 151;
int angle_1 = 55;
int angle_2 = 100;
int angle_3 = 90;
int step1 = 11;
int step = 1;
int time = 10;

void setup() {
  // Указываем какой тип сервопривода подключен к выводам MultiServoShield
  MSS.servoSet(0, SERVO_SG90);    //  Сервопривод SG90 подключён к выводу № 0 MultiServoShield.
  MSS.servoSet(1, SERVO_SG90);    //  Сервопривод SG90 подключён к выводу № 1 MultiServoShield.
  MSS.servoSet(2, SERVO_SG90);    //  Сервопривод SG90 подключён к выводу № 2 MultiServoShield.
  MSS.servoSet(3, SERVO_MG90);    //  Сервопривод MG90 подключён к выводу № 3 MultiServoShield.  //  Сервопривод MG996R подключён к выводу № 4 MultiServoShield.
                                  // MSS.servoSet(SERVO_ALL, SERVO_SG90); //  На любом выводе используются только сервоприводы SG90
  MSS.begin(&Wire);

  Serial.begin(9600);
  blutoooth.begin(9600);  //  Инициируем работу с MultiServoShield, указав ссылку на объект для работы с шиной I2C на которой находится модуль (по умолчанию &Wire)
}

void move_case(char command) {
  switch (command) {
    case 'B':
      while (command != 'S') {
        angle_1 = angle_1 - step;
        if (angle_1 < 0) {
          angle_1 = 0;
        }                                       //первый выход
        MSS.servoWrite(1, angle_1);
        delay(time);
        command = (char)blutoooth.read();
      }
      break;

    case 'F':
      while (command != 'S') {
        angle_1 = angle_1 + step;                   
        if (angle_1 > 102) {
          angle_1 = 102;
        }
        MSS.servoWrite(1, angle_1);
        delay(time);
        command = (char)blutoooth.read();
      }
      break;

      case 'L':
      while (command != 'S') {
        angle_3 = angle_3 - step;
        if (angle_3 < 45) {
          angle_3 = 45;
        }                                      
        MSS.servoWrite(3, angle_3);
        delay(time);
        command = (char)blutoooth.read();
      }
      break;

    case 'R':
      while (command != 'S') {
        angle_3 = angle_3 + step;                   
        if (angle_3 > 150) {
          angle_3 = 150;
        }
        MSS.servoWrite(3, angle_3);
        delay(time);
        command = (char)blutoooth.read();
      }
      break;

    case 'X':
      
        angle_0 = angle_0 - step;
        if (angle_0 < 151) {                              
          angle_0 = 151;
        }
        MSS.servoWrite(0, angle_0);
        delay(time);
        command = (char)blutoooth.read();
      
      break;

    case 'Y':
      
        angle_0 = angle_0 + step;
        if (angle_0 > 179) {
          angle_0 = 179;
        }
        MSS.servoWrite(0, angle_0);
        delay(time);
        command = (char)blutoooth.read();
      
      break;





       case 'M':
      
        angle_2 = angle_2 - step1;
        if (angle_2 < 0) {                              
          angle_2 = 0;
        }
        MSS.servoWrite(2, angle_2);
        delay(time);
        command = (char)blutoooth.read();
      
      break;

    case 'N':
      
        angle_2 = angle_2 + step1;
        if (angle_2 > 180) {
          angle_2 = 180;
        }
        MSS.servoWrite(2, angle_2);
        delay(time);
        command = (char)blutoooth.read();
      
      break;

       case 'm':
      
        angle_2 = angle_2 - step1;
        if (angle_2 < 0) {                              
          angle_2 = 0;
        }
        MSS.servoWrite(2, angle_2);
        delay(time);
        command = (char)blutoooth.read();
      
      break;

    case 'n':
      
        angle_2 = angle_2 + step1;
        if (angle_2 > 180) {
          angle_2 = 180;
        }
        MSS.servoWrite(2, angle_2);
        delay(time);
        command = (char)blutoooth.read();
      
      break;


    
  }
}




void loop() {
  if (blutoooth.available()) {
    

    char bt_input = (char)blutoooth.read();
    Serial.println(bt_input);
    move_case(bt_input);
    MSS.servoWrite(0, angle_0);
    MSS.servoWrite(1, angle_1);
    MSS.servoWrite(2, angle_2);
  }
}
