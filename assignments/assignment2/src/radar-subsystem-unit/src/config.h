#ifndef __CONFIG__
#define __CONFIG__

// tasks
/** Maximum number of tasks the scheduler can hold. */
#define MAX_TASKS 10

// radar
/** Number of sectors the 180 degrees of the horizon are divided into. */
#define NUM_SECTORS 18

// pins
#define PIN_TEMPSENSOR A2 // pwm/analog capable
#define PIN_POTENTIOMETER A3 // pwm/analog capable
#define PIN_ECHO 6 // pwm/analog capable
#define PIN_TIRGGER 7
#define PIN_BUTTON_1 8
#define PIN_BUTTON_2 13
#define PIN_BUTTON_3 12
#define PIN_SERVO 9 // pwm capable

// consts
#define TENSION_MAPPING_FACTOR 0.004883f // 5.0V / (2^10) values;

// LCD
#define LCD_I2C_ADDRESS 0x27

//indexes
#define INDEX_BUTTON_START 0
#define INDEX_BUTTON_STOP 1
#define INDEX_BUTTON_RESET 2

// periods
#define LED_BLINK_PERIOD 250 // ms

#endif