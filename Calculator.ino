#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '.', '=', '/'}};
byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

boolean presentValue = false;
boolean final = false;
boolean hasdecimal = false;
boolean decimal1 = false, decimal2 = false;
String n1, n2, d = ".";
float answer;
char op;

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("       4x4");
  lcd.setCursor(0, 1);
  lcd.print("   Calculator");
  delay(2500);
  lcd.clear();
}

void loop()
{
  char key = myKeypad.getKey();

  if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9'))
  {
    if (presentValue != true)
    {
      n1 = n1 + key;
      int numLength = n1.length();
      lcd.setCursor(15 - numLength, 0);
      lcd.print(n1);
    }
    else
    {
      n2 = n2 + key;
      int numLength = n2.length();
      lcd.setCursor(15 - numLength, 1);
      lcd.print(n2);
      final = true;
    }
  }

  else if (decimal1 == false && final == false && key != NO_KEY && key == '.')
  {
    n1 = n1 + d;
    int numLength = n1.length();
    lcd.setCursor(15 - numLength, 0);
    lcd.print(n1);
    decimal1 = true;
  }

  else if (decimal2 == false && final == true && key != NO_KEY && key == '.')
  {
    n2 = n2 + d;
    int numLength = n2.length();
    lcd.setCursor(15 - numLength, 1);
    lcd.print(n2);
    decimal2 = true;
  }

  else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+'))
  {
    if (presentValue == false)
    {
      presentValue = true;
      op = key;
      lcd.setCursor(15, 0);
      lcd.print(op);
    }
  }

  else if (final == true && key != NO_KEY && key == '=')
  {
    if (op == '+')
    {
      answer = n1.toFloat() + n2.toFloat();
      int answerint=int(answer);
      if(answer-answerint != 0.00)
      {
        hasdecimal = true;
      }
    }
    else if (op == '-')
    {
      answer = n1.toFloat() - n2.toFloat();
      int answerint=int(answer);
      if(answer-answerint != 0.00)
      {
        hasdecimal = true;
      }
    }
    else if (op == '*')
    {
      answer = n1.toFloat() * n2.toFloat();
      int answerint=int(answer);
      if(answer-answerint != 0.00)
      {
        hasdecimal = true;
      }
    }
    else if (op == '/')
    {
      answer = n1.toFloat() / n2.toFloat();
      int answerint=int(answer);
      if(answer-answerint != 0.00)
      {
        hasdecimal = true;
      }
    }
    
    lcd.clear();
    lcd.setCursor(15, 0);
    lcd.autoscroll();
    if(hasdecimal != true)
    {
      int answerint=int(answer);
      lcd.print(answerint);
    }
    else
      lcd.print(answer);
    lcd.noAutoscroll();
  }
  else if (key != NO_KEY && key == 'C')
  {
    lcd.clear();
    presentValue = false;
    final = false;
    decimal1 = false;
    decimal2 = false;
    hasdecimal = false;
    n1 = "";
    n2 = "";
    answer = 0;
    op = ' ';
  }
}