#include <Key.h>
#include <Keypad.h>

#include <Keypad.h>

const int ROW_NUM = 4; //cuatro filas
const int COLUMN_NUM = 4; //cuatro columnas

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','E', 'C'},
  {'H','G','F', 'D'}
};



byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //conectar las filas a los pines del keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //conectar las columnas a los pines del keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
  }
}
