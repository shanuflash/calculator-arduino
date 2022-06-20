#include < LiquidCrystal.h > #include < Keypad.h > const byte ROWS = 4;
const byte COLS = 4;
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

char keys[ROWS][COLS] = {
    {
        '1',
        '2',
        '3',
        '+'
    }, {
        '4',
        '5',
        '6',
        '-'
    }, {
        '7',
        '8',
        '9',
        '*'
    }, {
        'C',
        '.',
        '=',
        '/'
    }
};
byte rowPins[ROWS] = {
    13,
    12,
    11,
    10
};
byte colPins[COLS] = {
    9,
    8,
    7,
    6
};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

boolean presentValue = false;
boolean next = false;
boolean final = false;
String n1, n2, nd1 = ".", nd2 = ".";
int answer;
char op;

void setup() {
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("      4x4");
    lcd.setCursor(0, 1);
    lcd.print("   Calculator");
    delay(2500);
    lcd.clear();
}

void loop() {
    char key = myKeypad.getKey();
    if (key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '.')) {
        if (presentValue != true) {
            num1 = num1 + key;
            int numLength = num1.length();
            lcd.setCursor(15 - numLength, 0);
            lcd.print(num1);
        } else {
            num2 = num2 + key;
            int numLength = num2.length();
            lcd.setCursor(15 - numLength, 1);
            lcd.print(num2);
            final = true;
        }
    } else if (key != NO_KEY && key == '.') {
        n1 = n1 + nd1;
        int numLength = n1.length();
        lcd.setCursor(15 - numLength, 0);
        lcd.print(n1);
    } else if (key != NO_KEY && key == '.') {
        n2 = n2 + nd2;
        int numLength = n2.length();
        lcd.setCursor(15 - numLength, 1);
        lcd.print(n2);
    } else if (presentValue == false && key != NO_KEY && (key == '/' || key == '*' || key == '-' || key == '+')) {
        if (presentValue == false) {
            presentValue = true;
            op = key;
            lcd.setCursor(15, 0);
            lcd.print(op);
        }
    } else if (final == true && key != NO_KEY && key == '=') {
        if (op == '+') {
            answer = num1.toInt() + num2.toInt();
        } else if (op == '-') {
            answer = num1.toInt() - num2.toInt();
        } else if (op == '*') {
            answer = num1.toInt() * num2.toInt();
        } else if (op == '/') {
            answer = num1.toInt() / num2.toInt();
        }
        lcd.clear();
        lcd.setCursor(15, 0);
        lcd.autoscroll();
        lcd.print(answer);
        lcd.noAutoscroll();
    } else if (key != NO_KEY && key == 'C') {
        lcd.clear();
        presentValue = false;
        final = false;
        num1 = "";
        num2 = "";
        answer = 0;
        op = ' ';
    }
}