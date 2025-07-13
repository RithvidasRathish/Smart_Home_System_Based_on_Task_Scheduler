/**
 * @file smart_environmental_system.ino
 * @brief Smart environmental monitoring and control system using multiple sensors and TaskScheduler.
 * 
 * @details
 * This project monitors temperature, humidity, motion, gas levels, and ambient light.
 * Based on real-time sensor data, it controls relays, LEDs, and a buzzer.
 * TaskScheduler ensures periodic sensor reading and control actions without blocking.
 * 
 * - DHT11: Temperature and humidity
 * - IR Sensor: Motion detection
 * - LDR: Light level detection
 * - Gas Sensor: Smoke detection
 * 
 * Tasks:
 * - t1: Controls task logic based on iteration (2s interval, runs 15 times)
 * - t2: DHT11 temperature and humidity reading (3s initially, then 0.5s)
 * - t3: Reads IR and LDR sensor states
 * - t4: Gas sensor monitoring
 * 
 * Author: Rithvidas Rathish
 */

#include <TaskScheduler.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// ========== Pin Definitions ==========
#define DHTPIN D7
#define IRSensor A1
#define LDR D6
#define GASSensor D2
#define RELAY_PIN1 D5
#define RELAY_PIN0 D4
#define BUZZER D10
#define LED1 D11
#define LED2 D12
#define LED3 D13
#define LED4 D9

#define DHTTYPE DHT11

// ========== Global Variables ==========
int a = 0;              ///< Temperature variable for FAN logic
int sensorStatus = 0;   ///< IR sensor value
int lightState = 0;     ///< LDR value
int gasState = 0;       ///< Gas sensor value

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// ========== Task Callback Prototypes ==========
void t1Callback();
void t2Callback();
void t3Callback();
void t4Callback();
void t5Callback(); // (Not used in this sketch)

// ========== Task Definitions ==========
Task t4(10000, TASK_FOREVER, &t4Callback);
Task t1(2000, 15, &t1Callback);
Task t2(3000, TASK_FOREVER, &t2Callback);
Task t3(500, TASK_FOREVER, &t3Callback);

Scheduler runner;

// ========== Task Implementations ==========

/**
 * @brief Manages task scheduling logic and modifies task intervals.
 */
void t1Callback() {
    Serial.print("t1: ");
    Serial.println(millis());

    if (t1.isFirstIteration()) {
        runner.addTask(t3);
        t3.enable();
        Serial.println("t1: enabled t3 and added to the chain");
    }

    if (t1.isLastIteration()) {
        runner.addTask(t4);
        t4.enable();
        t2.setInterval(500);
        Serial.println("t1: enabled t4 and changed t2 interval to 500ms");
    }
}

/**
 * @brief Reads temperature and humidity from DHT11 and prints it.
 */
void t2Callback() {
    delay(delayMS);

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (!isnan(event.temperature)) {
        a = event.temperature;
        Serial.print(F("Temperature: "));
        Serial.print(a);
        Serial.println(F("°C"));
    }

    dht.humidity().getEvent(&event);
    if (!isnan(event.relative_humidity)) {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
    }

    Serial.print("t2: ");
    Serial.println(millis());
}

/**
 * @brief Reads IR and LDR sensors.
 */
void t3Callback() {
    sensorStatus = digitalRead(IRSensor);
    lightState = digitalRead(LDR);
    Serial.println("t3: Sensor check (IR/LDR)");
    Serial.println(millis());
}

/**
 * @brief Reads the gas sensor.
 */
void t4Callback() {
    gasState = digitalRead(GASSensor);
    Serial.print("t4: ");
    Serial.println(millis());
}

// ========== Setup Function ==========

void setup () {
    Serial.begin(115200);

    // Sensor & actuator pin modes
    pinMode(LDR, INPUT);
    pinMode(IRSensor, INPUT); 
    pinMode(GASSensor, INPUT);
    pinMode(RELAY_PIN0, OUTPUT);
    pinMode(RELAY_PIN1, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(LED4, OUTPUT);

    dht.begin();
    Serial.println(F("DHTxx Unified Sensor Initialized"));

    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;

    runner.init();
    runner.addTask(t1);
    runner.addTask(t2);

    delay(5000); // Allow sensors to settle

    t1.enable();
    t2.enable();

    Serial.println("Scheduler initialized and tasks enabled");
}

// ========== Main Loop ==========
void loop () {
    runner.execute();

    // FAN control based on temperature
    if (a < 30) {
        digitalWrite(RELAY_PIN0, LOW);
        digitalWrite(LED2, LOW);
        Serial.println("Switching OFF FAN");
    } else {
        digitalWrite(RELAY_PIN0, HIGH);
        digitalWrite(LED2, HIGH);
        Serial.println("Switching ON FAN");
    }

    // Light control based on LDR
    if (lightState == 0) {
        digitalWrite(RELAY_PIN1, LOW);
        digitalWrite(LED3, LOW);
        Serial.println("Switching OFF Lights");
    } else {
        digitalWrite(RELAY_PIN1, HIGH);
        digitalWrite(LED3, HIGH);
        Serial.println("Switching ON Lights");
    }

    // Smoke detection
    if (gasState == 1) {
        digitalWrite(LED4, LOW);
        Serial.println("Smoke NOT Detected");
    } else {
        digitalWrite(LED4, HIGH);
        Serial.println("Smoke Detected");
    }

    // Motion detection
    if (sensorStatus == 1) {
        digitalWrite(LED1, LOW);
        digitalWrite(BUZZER, LOW);
        Serial.println("Motion NOT Detected!");
    } else {
        digitalWrite(LED1, HIGH);
        digitalWrite(BUZZER, HIGH);
        Serial.println("Motion Detected!");
    }
}
