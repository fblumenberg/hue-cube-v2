#include <Arduino.h>
#include <Wire.h>

#include "hue_cube.h"
#include "modes.h"

#define MPUADDR 0x68

cRGB leds[NR_OF_LED];
cRGB white = {255, 255, 255};
cRGB black = {0, 0, 0};

WS2812 LED(NR_OF_LED);

// the MPU values for each module
int16_t AcX, AcY, AcZ, Temp, GyX, GyY, GyZ;
int16_t AcXf, AcYf, AcZf;

static void readMPUValues()
{
    Wire.beginTransmission(MPUADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPUADDR, 14);          // request a total of 14 registers
    AcX = (Wire.read() << 8 | Wire.read()); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = (Wire.read() << 8 | Wire.read()); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = (Wire.read() << 8 | Wire.read()); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Temp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyX = Wire.read() << 8 | Wire.read();   // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read() << 8 | Wire.read();   // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read() << 8 | Wire.read();   // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    // low pass filter to remove noise:
    AcXf = AcXf * 0.7 + 0.3 * (AcX); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcYf = AcYf * 0.7 + 0.3 * (AcY); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZf = AcZf * 0.7 + 0.3 * (AcZ); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}

LightMode *currentMode;

void setup()
{
    Serial.begin(115200);
    Serial.println("Start the cube");

    Wire.begin();
    Wire.beginTransmission(MPUADDR);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
    LED.setOutput(LED_PIN);

    setupModes();
    currentMode = activeLightMode();
}

unsigned long nextModeLoop;
unsigned long tapTimeout;
bool need2ndTap;

void loop()
{
    readMPUValues();

    if (abs(AcX - AcXf) > 8000 || abs(AcX - AcXf) > 8000 || abs(AcX - AcXf) > 8000)
    {
        if (need2ndTap)
        {
            Serial.print("Changed the mode ");

            currentMode = nextLightMode();

            Serial.println(currentMode->name());

            for (uint16_t i = 0; i < NR_OF_LED; i++)
            {
                leds[i] = black;
            }

            // for (int m = 0; m < currentMode; m++)
            {
                for (uint16_t i = 0; i < NR_OF_LED; i++)
                {
                    LED.set_crgb_at(i, white);
                }
                LED.sync();
                delay(100);
                for (uint16_t i = 0; i < NR_OF_LED; i++)
                {
                    LED.set_crgb_at(i, black);
                }
                LED.sync();
                delay(100);
            }
            need2ndTap = false;
        }
        else
        {
            need2ndTap = true;
            //delay(100);
            tapTimeout = millis() + 1000;
        }
    }

    if (need2ndTap && millis() >= nextModeLoop)
    {
        need2ndTap = false;
    }

    if (millis() >= nextModeLoop)
    {
        int delay = currentMode->loop();
        nextModeLoop = millis() + delay;
    }
    delay(1);
}