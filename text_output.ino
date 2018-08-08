#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];                              // подключаем большой шрифт
extern uint8_t SevenSegNumFont[];                      // подключаем цифровой шрифт
// Remember to change the model parameter to suit your display module!
UTFT myGLCD (ILI9486,38,39,40,41);

void setup()
{
  myGLCD.InitLCD();                                    // инициируем дисплей (в качестве параметра данной функции можно указать ориентацию дисплея: PORTRAIT или LANDSCAPE), по умолчанию LANDSCAPE - горизонтальная ориентация
}
void loop()
{
//Стираем все с экрана
  myGLCD.clrScr();                                     // стираем всю информацию с дисплея
  myGLCD.setFont(SmallFont);                           // устанавливаем маленький шрифт
  myGLCD.setColor(VGA_WHITE);                          // устанавливаем цвет текста
  myGLCD.print("PIZDEC", CENTER, 50); // выводим текст на дисплей
  myGLCD.setFont(BigFont);                             // устанавливаем большой шрифт
  myGLCD.setColor(VGA_BLUE);                           // устанавливаем цвет текста
  myGLCD.print("VI VIKRUCHIVAETE MNE YAYTSA", CENTER, 100);                // выводим текст на дисплей
  myGLCD.print("SER", CENTER, 115);            // выводим текст на дисплей
  myGLCD.setFont(SevenSegNumFont);                     // устанавливаем цифровой шрифт
  myGLCD.setColor(VGA_FUCHSIA);                        // устанавливаем цвет текста
  myGLCD.print("1234567890", CENTER, 150);             // выводим текст на дисплей
  delay(20000);
}
