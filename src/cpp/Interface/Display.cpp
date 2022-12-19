#include "Display.h"

Display::Display() : m_tft(DISPLAY_WIDTH, DISPLAY_HEIGHT),
                     m_page(&m_tft)
{
    m_defaultBarWidth = DISPLAY_HEIGHT / PLANT_COUNT;

    pageIndex = 0;
    currentPage = AllPlants;
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

    m_page.setTextSize(2);
    m_page.fillRect(0, 0, DISPLAY_HEIGHT, DISPLAY_WIDTH, TFT_BLACK);
    m_page.pushSprite(0, 0);
}

//////////////////////////////////////////////

Display::Pages Display::GetPage()
{
    return currentPage;
}

int Display::GetPageIndex() const
{
    return pageIndex;
}

void Display::ReloadPage()
{
    LoadPage();
}

void Display::LoadNextPage()
{
    Serial.println("Load Next Page called");
    previousPage = currentPage;

    switch (currentPage)
    {
    case AllPlants:
        currentPage = Plant;
        pageIndex = 0;

        Reset();

        break;
    case Plant:
        if (pageIndex < PLANT_COUNT - 1)
        {
            pageIndex++;
        }

        break;
    default:
        Serial.println("Out of range page loaded");
        pageIndex = 0;
        currentPage = AllPlants;
    }

    LoadPage();
}

void Display::LoadPreviousPage()
{
    Serial.println("Load Previous Page called");
    previousPage = currentPage;

    switch (currentPage)
    {
    case AllPlants:
        // currentPage = Plant;
        // pageIndex = PLANT_COUNT - 1;

        // Reset();

        break;
    case Plant:
        pageIndex--;
        if (pageIndex < 0)
        {
            currentPage = AllPlants;
        }

        break;
    default:
        Serial.println("Out of range page loaded");
        pageIndex = 0;
        currentPage = AllPlants;
    }

    LoadPage();
}

void Display::LoadPage()
{
    switch (currentPage)
    {
    case AllPlants:
        Reset();

        // LOAD ALL PLANTS PAGE
        for (int i = 0; i < PLANT_COUNT; i++)
        {
            int percentage, threshold;

            Plants::GetPlant(i, &percentage, &threshold);
            DrawBarWithThreshold(i, i, percentage, threshold);
        }

        Serial.println("Loaded AllPlants Page at index: ");
        Serial.println(pageIndex);
        break;
    case Plant:
        int percentage, threshold;

        Plants::GetPlant(pageIndex, &percentage, &threshold);
        DrawPlantPage(pageIndex, percentage, threshold);

        Serial.println("Loaded Plant Page at index: ");
        Serial.println(pageIndex);
        break;
    }
}

void Display::ChangePageIndex(int newIndex)
{
    prevPageIndex = pageIndex;

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

//////////////////////////////////////////////

void Display::DrawPlantPage(int id, int percentage, int threshold)
{
    DrawBarWithThreshold(id, 0, percentage, threshold);
    DrawPlantInformation(percentage, threshold);
}

//////////////////////////////////////////////

void Display::DrawPlantInformation(int percentage, int threshold)
{
    float xPos = DISPLAY_HEIGHT / 2;
    float yPos = DISPLAY_WIDTH / 2.5;

    m_page.drawString("Moisture: ", xPos, DISPLAY_WIDTH / 4);
    m_page.drawString(String(percentage), xPos, DISPLAY_WIDTH / 2.5);
    m_page.drawString("Threshold:", xPos, DISPLAY_WIDTH / 1.5);
    m_page.drawString(String(threshold), xPos, DISPLAY_WIDTH / 1.25);

    m_page.pushSprite(0, 0);
}

//////////////////////////////////////////////

void Display::DrawBarWithThreshold(int id, int row, int percentage, int threshold)
{
    float xPos = row * m_defaultBarWidth;

    // Fill Area of old bar with background color
    m_page.fillRect(xPos, 0, m_defaultBarWidth, DISPLAY_WIDTH, TFT_BLACK);

    // Create bar
    m_page.fillRect(xPos, DISPLAY_WIDTH - percentage, m_defaultBarWidth, percentage, TFT_GREEN);

    // Create indicator showing threshold value
    m_page.fillRect(xPos, DISPLAY_WIDTH - threshold, m_defaultBarWidth, 5, TFT_WHITE);

    // Text showing plant ID.
    m_page.drawString(String(id), xPos + (m_defaultBarWidth / 2), 10);

    // Push sprite to screen.
    m_page.pushSprite(0, 0);
}