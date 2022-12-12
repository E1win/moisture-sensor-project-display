#include "Potentiometer.h"

Potentiometer::Potentiometer(byte pin)
{
    m_pin = pin;

    value = 0;
    prevValue = -1;

    minChange = 250;

    valuePercentage = 0;
}

void Potentiometer::Loop()
{
    value = analogRead(POTENTIOMETER_PIN);

    hasNewValue = false;

    if (abs(value - prevValue) > minChange)
    {
        prevValue = value;

        int newValuePercentage = map(prevValue, 0, 4095, 0, 100);

        newValuePercentage = constrain(newValuePercentage, 0, 100);

        if (newValuePercentage != valuePercentage)
        {
            valuePercentage = newValuePercentage;

            hasNewValue = true;
        }
    }
}

int Potentiometer::GetValue() const
{
    return valuePercentage;
}

bool Potentiometer::IsChanged() const
{
    return hasNewValue;
}