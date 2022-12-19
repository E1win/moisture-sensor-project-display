#pragma once

#include "config.h"
#include "Interface/SimpleButton.h"
#include "Interface/Potentiometer.h"
#include "Interface/Display.h"
#include "Data/Plants.h"

class App
{
public:
    App();

    void Run();

private:
    // User Interface
    SimpleButton m_btn1;
    SimpleButton m_btn2;

    Potentiometer m_ptnmtr;

    Display m_display;
};