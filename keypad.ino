#include <Keypad.h>
#include <Servo.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {39, 41, 43, 45}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {47, 49, 51, 53}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

Servo servo;

/** CHANGE IF SERVO MOTOR PIN IS NOT 2 **/
const int SERVO_MOTOR_PIN = 2;

void runServo(int secs, int value) {
  int delay_time = secs*1000 / 2;
  Serial.print("Starting servo...");
  servo.write(value);
  delay(delay_time);
  servo.write(-value);
  delay(delay_time);
  Serial.print("Turning off servo...");
}

void flashLED(int times) {
  if (times == 0) return;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(125);
  digitalWrite(LED_BUILTIN, LOW);
  delay(125);
  flashLED(times-1);
}

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(SERVO_MOTOR_PIN,INPUT_PULLUP);
  //int mode = digitalRead(SERVO_MOTOR_PIN);
  servo.attach(SERVO_MOTOR_PIN);
  runServo(2, 180);
  Serial.begin(9600);
}

void loop(){
  char key = keypad.getKey();

  /*if (key){
    Serial.println(key);
  }*/
  if (key == 'A') {
    Serial.println("A was pressed.");
    runServo(5, 90);
    Serial.println("Done\n");
  }
  int num = (int)key - 48;
  String s = String(num);
  if (num > 0 && num < 10) { //check if key pressed is number
    Serial.println(s + " was pressed");
    Serial.print("Flashing LED " + s + " times...");
    flashLED(num);
    Serial.println("Done\n");
  }
}
