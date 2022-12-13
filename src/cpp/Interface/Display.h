#pragma once

#include <TFT_eSPI.h>
#include "config.h"

class Display
{
public:
    Display();

    void Init();

    void Reset();

    void DrawPlantPage(int id, int percentage, int threshold);
    void DrawBarWithThreshold(int id, int row, int percentage, int threshold);

private:
    TFT_eSPI m_tft;

    TFT_eSprite m_page;

    float m_defaultBarWidth;

private:
};