#pragma once

#include "config.h"
#include "Arduino.h"

class Potentiometer
{
public:
    Potentiometer(byte pin);

    void Loop();

    int GetValue() const;

    bool IsChanged() const;

private:
    byte m_pin;

    int value;
    int prevValue;
    int minChange = 100;

    int valuePercentage;

    bool hasNewValue = false;
};