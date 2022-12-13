#pragma once

#include "config.h"
#include "Interface/SimpleButton.h"
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

    Display m_display;

    int pageIndex = 0;

private:
    void NextPage();
    void PreviousPage();

    void ChangePageIndex(int newIndex);

    void LoadPage(int index);
};