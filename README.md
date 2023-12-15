# RTC Countdown Timer with Keypad and LCD Display
This Arduino sketch implements a countdown timer using an RTC (Real-Time Clock), a keypad for user input, an LCD display to show the time and date, and a buzzer to signal timer expiration. 
# Components Used 
RTC Module: DS3231 Keypad: 4x4 Matrix Keypad LCD Display: 16x2 Character LCD Buzzer 
# Functionality 
The code initializes the RTC and checks for RTC power loss, setting the time if necessary. The LCD displays the current time and date retrieved from the RTC. Pressing the 'A' button on the keypad allows the user to set a countdown timer. Pressing the 'B' button enables the user to set a specific date and time for the RTC. When setting a countdown timer ('A' button), the user enters the hour and minute. The countdown timer starts and displays the remaining time on the LCD. Upon expiration, the LCD shows "Timer Expired!" and triggers the buzzer.
