#include "Potentiometer.h"

Potentiometer::Potentiometer(byte pin)
{
    m_pin = pin;

    m_valuePercentage = 0;

    xTaskCreate(
        Loop,            // Task to be executed
        "Potentiometer", // Name of task (for debugging)
        1000,            // Bytes to reserve for program
        this,            // Parameters
        1,               // Priority
        NULL);           // Handler
}

void Potentiometer::Loop(void *params)
{
    Potentiometer *instance = (Potentiometer *)params;

    int value = 0;
    int prevValue = -1;

    int change;

    for (;;)
    {
        value = analogRead(instance->m_pin);

        change = abs(value - prevValue);
        if (change > minChange)
        {
            int valuePercentage = ConvertToPercentage(value);

            if (valuePercentage != instance->m_valuePercentage)
            {
                prevValue = value;
                instance->m_valuePercentage = valuePercentage;
                instance->m_hasNewValue = true;
            }
        }

        // Delay to give IDLE task time to execute.
        vTaskDelay(250);
    }
}

int Potentiometer::GetValue() const
{
    return m_valuePercentage;
}

bool Potentiometer::IsChanged()
{
    if (m_hasNewValue)
    {
        m_hasNewValue = false;
        return true;
    }

    return false;
}

int Potentiometer::ConvertToPercentage(int num)
{
    num = map(num, 0, 4095, 0, 100);

    num = constrain(num, 0, 100);

    return num;
}