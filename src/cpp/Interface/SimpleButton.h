#pragma once

#include "Arduino.h"

class SimpleButton
{
public:
    SimpleButton(byte pin);

    bool IsPressed();

private:
    byte m_pin;
    bool m_pressed = false;

private:
    static void Loop(void *params);
};