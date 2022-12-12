#pragma once

#include "config.h"
#include "Interface/SimpleButton.h"
#include "Interface/Display.h"

class App
{
public:
    App();
    // App(Display *display);

    void Run();

private:
    // User Interface
    SimpleButton m_btn1;
    SimpleButton m_btn2;

    Display m_display;
};