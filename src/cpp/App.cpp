#include "App.h"

App::App() : m_btn1(BUTTON1_PIN),
             m_btn2(BUTTON2_PIN),
             m_ptnmtr(POTENTIOMETER_PIN)
{
}

void App::Run()
{
    Serial.begin(9600);

    m_display.Init();

    Plants::Init();

    m_display.ReloadPage();

    while (true)
    {
        if (m_btn1.IsPressed())
        {
            Serial.println("Button 1 pressed!");

            m_display.LoadNextPage();
        }

        if (m_btn2.IsPressed())
        {
            Serial.println("Button 2 pressed!");

            m_display.LoadPreviousPage();
        }

        if (m_ptnmtr.IsChanged() && m_display.GetPage() == Display::Plant)
        {

            Serial.println(m_ptnmtr.GetValue());
            int plantID = m_display.GetPageIndex();
            Plants::SetThresholdPercentage(plantID, m_ptnmtr.GetValue());
            m_display.ReloadPage();
        }
    }
}

////////////////////////////////////