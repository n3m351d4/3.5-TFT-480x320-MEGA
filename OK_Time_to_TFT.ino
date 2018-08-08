//Sketch uses 23618 bytes (9%) of program storage space. Maximum is 253952 bytes.
//Global variables use 514 bytes (6%) of dynamic memory, leaving 7678 bytes for local variables. Maximum is 8192 bytes.
//Отказывается получать дату и время
#include <UTFT.h>                                                       // Библиотека для дисплея на ILI9486
#include <Wire.h>
#include "Sodaq_DS3231.h"                                               //Библиотека для часов и температуры
extern uint8_t SmallFont[];                                             //Подключаем маленький шрифт
extern uint8_t BigFont[];                                               //Подключаем большой шрифт
extern uint8_t SevenSegNumFont[];                                       //Подключаем цифровой шрифт
static uint8_t prevMinute=0;                                            //Переменная для сохранения секунд
static uint8_t prevSecond=0;                                            //Переменная для сохранения секунд
char weekDay[][8] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Saturday" }; //Имена дней недели

UTFT myGLCD (ILI9486,38,39,40,41);                                      //Пины дисплея

void setup () 
{
    myGLCD.InitLCD();                                                   // Инициируем дисплей (в качестве параметра данной функции можно указать ориентацию дисплея: PORTRAIT или LANDSCAPE), по умолчанию LANDSCAPE - горизонтальная ориентация
    Wire.begin();
    rtc.begin();
}
uint32_t old_ts;
void loop () 
{
  DateTime now = rtc.now();                                             //Получаем текущее время и дату    
  if((now.minute()) != prevMinute)                                      //Рефреш раз в минуту
    {
      myGLCD.setFont(BigFont);                                          // Задаем шрифт
      myGLCD.clrScr();                                                  // Очистка экрана
      myGLCD.printNumI(int(now.hour()), 0, 15);                         // Первая цифра - координата горизонтали, вторая - вертикали
      myGLCD.print(":", 30, 15);                                        // После знака делать промежуток в 15  
      prevMinute = now.minute();
      myGLCD.printNumI(int(now.minute()), 40, 15);                      // Можно сделать так, чтобы часы менялись раз в час так же, но может не хватить памяти
      myGLCD.print(":", 70, 15);
      myGLCD.printNumI(int(now.date()), 130, 15);
        myGLCD.print("/", 160, 15);
        myGLCD.printNumI(int(now.month()), 175, 15);
        myGLCD.print("/", 205, 15);
        myGLCD.printNumI(int(now.year()), 220, 15);
          myGLCD.print(weekDay[now.dayOfWeek()], 0, 45);
            rtc.convertTemperature();                                     //Получаем температуру в цельсиях
            myGLCD.printNumI(int(rtc.getTemperature()), 0, 75);       
            myGLCD.print("  deg C", 30, 75);  
    }
    prevMinute = now.minute();                                          //Возможно, лишние две строки
    rtc.clearINTStatus();
if((now.second()) !=  prevSecond )                                      //Цикл, для того, чтобы секунды менялись раз в секунду
  {
  myGLCD.setFont(BigFont);                                        
  myGLCD.printNumI(int(now.second()), 85, 15);
  } 
    prevSecond = now.second();
    rtc.clearINTStatus();
    }
