#include "Display.h"

Display::Display() : m_tft(DISPLAY_WIDTH, DISPLAY_HEIGHT),
                     m_page(&m_tft)
{
    m_defaultBarWidth = 40;
}

void Display::Init()
{
    m_tft.init();

    m_tft.setRotation(1);
    m_tft.setTextDatum(MC_DATUM);

    m_page.createSprite(DISPLAY_HEIGHT, DISPLAY_WIDTH);

    Reset();
}

void Display::Reset()
{
    m_tft.fillScreen(TFT_BLACK);
    m_tft.setTextSize(2);
    m_tft.setTextColor(TFT_WHITE);
}

//////////////////////////////////////////////

void Display::DrawPlantPage(int id, int percentage, int threshold)
{
    float xPos = 0 * m_defaultBarWidth;

    // Fill Area of old bar with background color
    m_page.fillRect(xPos, DISPLAY_WIDTH - 100, m_defaultBarWidth, 100, TFT_BLACK);

    // Create bar
    m_page.fillRect(xPos, DISPLAY_WIDTH - percentage, m_defaultBarWidth, percentage, TFT_GREEN);

    // Create indicator showing threshold value
    m_page.fillRect(xPos, DISPLAY_WIDTH - threshold, m_defaultBarWidth, 5, TFT_WHITE);

    // Push sprite to screen.
    m_page.pushSprite(0, 0);
}