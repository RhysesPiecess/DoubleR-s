/*
Rhys Manoj
Roshni Suresh

ENES100-23262
Professor Mellini

Code to run the Arduino Alarm
Utilizes membrane keypad switch and RTC
*/

#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <DS3231.h>
#include <pitches.h>

RTC_DS3231 rtc; // RTC object

// LCD Setup
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Keypad Setup
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[ROWS] = {37, 35, 33, 31};
byte rowPins[COLS] = {53, 51, 49, 47};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Buzzer Setup
const int buzzerPin =5;

void setup() {
// Initialize Serial Monitor
  Serial.begin(9600);
// Initialize LCD
  lcd.begin(16, 2); 
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now(); // Get current time from RTC
  int hour = now.hour(); // Get current hour
  int minute = now.minute(); // Get current minute
  int second = now.second(); // Get current second

  // Display current time on LCD
  lcd.setCursor(0, 0);
  lcd.print("TIME: ");
  lcd.print(now.timestamp(DateTime::TIMESTAMP_TIME)); // Display time
  lcd.setCursor(0, 1);
  lcd.print("DATE: ");
  lcd.print(now.timestamp(DateTime::TIMESTAMP_DATE)); // Display date

  char button = customKeypad.getKey();
  if (button == 'A') {
    int setHour = getData("Enter Hour: ");
    int setMinute = getData("Enter Minute: ");

    int remainingTime = ((setHour * 60 * 60) + (setMinute * 60)) - ((hour * 60 * 60) + (minute * 60) + second);

    while (remainingTime > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Time Remaining:");
      lcd.setCursor(0, 1);

      int displayHour = remainingTime / 3600;
      int displayMinute = (remainingTime % 3600) / 60;
      int displaySecond = remainingTime % 60;

      lcd.print(displayHour);
      lcd.print(":");
      if (displayMinute < 10) {
        lcd.print("0");
      }
      lcd.print(displayMinute);
      lcd.print(":");
      if (displaySecond < 10) {
        lcd.print("0");
      }
      lcd.print(displaySecond);

      delay(1000);
      now = rtc.now();
      hour = now.hour();
      minute = now.minute();
      second = now.second();
      remainingTime = ((setHour * 60 * 60) + (setMinute * 60)) - ((hour * 60 * 60) + (minute * 60) + second);
    }

    lcd.clear();
    lcd.print("Timer Expired!");
    playNote(NOTE_D1, 10000);
    delay(5000); // Display timer expiration for 5 seconds
  }
  if (button == 'B'){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Year: ");
      int year = getNewData();

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Month: ");
      int month = getNewData();

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Day: ");
      int day = getNewData();

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Hour: ");
      int hour = getNewData();

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter Minute: ");
      int minute = getNewData();


      rtc.adjust(DateTime(year, month, day, hour, minute, 0));
    }
}

int getData(String message) {
  String data = "";
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  while (true) {
    char button = customKeypad.getKey();
    if (button == '#') {
      break;
    } else if (isDigit(button)) {
      data += button;
      lcd.print(button);
    }
  }
  return data.toInt();
}

int getNewData(){
  String newData ="";
  lcd.setCursor(0,1);
  while(true){
    char button = customKeypad.getKey();
    if(button =='#'){
      break;
    }
    else if(isDigit(button)){
      newData+=button;
      lcd.print(button);
      }
    }
  return newData.toInt();
  }  

// Function to play a note on the buzzer
void playNote(int note, int duration) {
  tone(buzzerPin, note);
  delay(duration);
  noTone(buzzerPin);
}
