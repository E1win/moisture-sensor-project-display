#include "SimpleButton.h"

SimpleButton::SimpleButton(byte pin)
{
    pinMode(pin, INPUT_PULLUP);

    m_pin = pin;

    xTaskCreate(
        Loop,     // Task to be executed
        "Button", // Name of task (for debugging)
        1000,     // Bytes to reserve for program
        this,     // Parameters
        1,        // Priority
        NULL);    // Handler
}

void SimpleButton::Loop(void *params)
{
    SimpleButton *instance = (SimpleButton *)params;

    int _prevState = HIGH;
    int _state = HIGH;

    for (;;)
    {
        _prevState = _state;

        _state = digitalRead(instance->m_pin);

        instance->m_pressed = false;

        if (_prevState == HIGH && _state == LOW)
        {
            instance->m_pressed = true;
        }

        // Delay to give IDLE task time to execute.
        vTaskDelay(100);
    }
}

bool SimpleButton::IsPressed()
{
    if (m_pressed)
    {
        m_pressed = false;
        return true;
    }

    return false;
}