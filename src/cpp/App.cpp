#include "App.h"

App::App() : m_btn1(BUTTON1_PIN),
             m_btn2(BUTTON2_PIN)
{
}

void App::Run()
{
    Serial.begin(9600);

    m_display.Init();

    Plants::Init();

    while (true)
    {
        if (m_btn1.IsPressed())
        {
            Serial.println("Button 1 pressed!");

            NextPage();
        }

        if (m_btn2.IsPressed())
        {
            Serial.println("Button 2 pressed!");

            PreviousPage();
        }
    }
}

////////////////////////////////////

void App::NextPage()
{
    ChangePageIndex(pageIndex + 1);
    LoadPage(pageIndex);
}

void App::PreviousPage()
{
    ChangePageIndex(pageIndex - 1);
    LoadPage(pageIndex);
}

void App::LoadPage(int index)
{
    if (index == 0)
    {
        // LOAD ALL PLANTS PAGE
        for (int i = 0; i < PLANT_COUNT; i++)
        {
            int percentage, threshold;

            Plants::GetPlant(i, &percentage, &threshold);
            m_display.DrawBarWithThreshold(i, i, percentage, threshold);
        }
    }
    else if (index <= PLANT_COUNT)
    {
        int percentage, threshold;

        Plants::GetPlant(index - 1, &percentage, &threshold);
        m_display.DrawPlantPage(index - 1, percentage, threshold);
    }
}

void App::ChangePageIndex(int newIndex)
{
    if (newIndex > PLANT_COUNT)
    {
        pageIndex = 0;
    }
    else if (newIndex < 0)
    {
        pageIndex = PLANT_COUNT;
    }
    else
    {
        pageIndex = newIndex;
    }
}