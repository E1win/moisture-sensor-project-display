#include "Plants.h"

Plants::Plants()
{
}

void Plants::Init()
{
    m_defaultMoistureThreshold = 20;

    // Initialize Plant Array
    for (int i = 0; i < PLANT_COUNT; i++)
    {
        m_plantArr[i] = {i,
                         random(1, 100),
                         m_defaultMoistureThreshold};
    }
}

////////////////////////////////////////

void Plants::GetPlant(int id, int *outPercentage, int *outThreshold)
{
    // Do check here if id is not out of range
    if (id < 0 || id >= PLANT_COUNT)
    {
        Serial.println("Plant ID out of range, given default values");

        *outPercentage = 0;
        *outThreshold = 0;

        return;
    }

    *outPercentage = m_plantArr[id].moisturePercentage;
    *outThreshold = m_plantArr[id].thresholdPercentage;
}

int Plants::GetMoisturePercentage(int id)
{
    return m_plantArr[id].moisturePercentage;
}

int Plants::GetThresholdPercentage(int id)
{
    return m_plantArr[id].thresholdPercentage;
}