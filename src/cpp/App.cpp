#include "App.h"

App::App() : m_btn1(BUTTON1_PIN),
             m_btn2(BUTTON2_PIN)
{
}

void App::Run()
{
    Serial.begin(9600);

    m_display.Init();

    int testPercentage = 50;
    int testThreshold = 20;
    m_display.DrawPlantPage(0, testPercentage, testThreshold);

    while (true)
    {
        if (m_btn1.IsPressed())
        {
            Serial.println("Button 1 pressed!");

            testPercentage = testPercentage + 5;
            Serial.println(testPercentage);
            m_display.DrawPlantPage(0, testPercentage, testThreshold);

            // Show previous page
        }

        if (m_btn2.IsPressed())
        {
            Serial.println("Button 2 pressed!");

            testPercentage = testPercentage - 5;
            Serial.println(testPercentage);
            m_display.DrawPlantPage(0, testPercentage, testThreshold);

            // Show next page
        }
    }
}