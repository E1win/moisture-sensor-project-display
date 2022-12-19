#pragma once

#include <TFT_eSPI.h>
#include "cpp/Data/Plants.h"
#include "config.h"

class Display
{
public:
    enum Pages
    {
        AllPlants,
        Plant
    };

public:
    Display();

    void Init();

    void Reset();

    void ReloadPage();
    void LoadNextPage();
    void LoadPreviousPage();

    Pages GetPage();
    int GetPageIndex() const;

private:
    TFT_eSPI m_tft;

    TFT_eSprite m_page;

    float m_defaultBarWidth;

    int pageIndex;
    int prevPageIndex;

    Pages currentPage = AllPlants;
    Pages previousPage = AllPlants;

private:
    void LoadPage();
    void ChangePageIndex(int newIndex);

    void DrawPlantPage(int id, int percentage, int threshold);
    void DrawBarWithThreshold(int id, int row, int percentage, int threshold);
    void DrawPlantInformation(int percentage, int threshold);
};