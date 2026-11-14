#include "setUpper.h"

#include <Arduino.h>
#include "model/config.h"
#include "taskSystem/RSUscheduler.h"

#include "taskSystem/tasks/Input.h"
#include "taskSystem/tasks/Controller.h"
#include "taskSystem/tasks/Radar.h"
#include "taskSystem/tasks/UI.h"
#include "taskSystem/tasks/Communication.h"

#include "devices/ServoMotor.h"
#include "devices/impl/TactileButton.h"
#include "devices/impl/Potentiometer.h"
#include "devices/impl/AnalogTemperatureSensor.h"
#include "devices/impl/UltrasonicSensor.h"
#include "devices/impl/Led.h"
#include "devices/impl/Lcd.h"
#include "communication/impl/SerialChannel.h"
#include "communication/CommandParser.h"

#define TASK_PERIOD 50 // ms

void setupSystem(RSUscheduler* scheduler) {
    Button* start = new TactileButton(PIN_BUTTON_1);
    Button* stop = new TactileButton(PIN_BUTTON_2);
    Button* reset = new TactileButton(PIN_BUTTON_3);
    AngleSensor* pot = new Potentiometer(PIN_POTENTIOMETER);
    TemperatureSensor* temp = new AnalogTemperatureSensor(PIN_TEMPSENSOR);
    DistanceSensor* sonar = new UltrasonicSensor(PIN_TIRGGER, PIN_ECHO);
    ServoMotor* servo = new ServoMotor(PIN_SERVO);
    Light* greenLed = new Led(PIN_LED_GREEN);
    Light* redLed = new Led(PIN_LED_RED);
    Screen* lcd = new Lcd(LCD_I2C_ADDRESS, 16, 2);
    MessageChannel* channel = new SerialChannel(9600);
    CommandParser* parser = new CommandParser();

    // tasks
    Input* input = new Input(TASK_PERIOD, start, stop, reset, pot, temp);
    Radar* radar = new Radar(TASK_PERIOD, sonar, servo);
    UI* ui = new UI(TASK_PERIOD, lcd, redLed, greenLed);
    Communication* communication = new Communication(TASK_PERIOD, channel, parser);
    Controller* controller = new Controller(TASK_PERIOD, input, radar, ui, communication);

    // init. Controller last
    Task* initOrder[] = {input, radar, ui, communication, controller};
    for (Task* task : initOrder) {
    task->init();
    }

    // tick order: inputs -> radar -> sensors/actuators -> console
    Task* tickOrder[] = {input, controller, radar, ui, communication};
    for (Task* task : tickOrder) {
    scheduler->registerTask(task);
    }
}