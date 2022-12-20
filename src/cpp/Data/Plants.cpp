#include "Plants.h"

// int Plants::m_defaultMoistureThreshold = 20;

namespace
{
    int DEFAULT_MOISTURE_THRESHOLD = 20;

    typedef struct Plant
    {
        int id;
        int moisturePercentage;
        int thresholdPercentage;
    } Plant;

    Plant m_plantArr[PLANT_COUNT];

    Preferences preferences;
}

Plants::Plants()
{
}

void Plants::Init()
{
    // TODO: UNSET ALL KEYS LIKE PLANT1, PLANT2, PLANT3

    // Open preferences using plant-data namespace.
    preferences.begin("plant-data", false);

    // Initialize Plant Array
    for (int i = 0; i < PLANT_COUNT; i++)
    {
        // Create key strings
        char moistureKey[12];
        char thresholdKey[12];
        CreateMoisturePercentageKey(i, moistureKey);
        CreateThresholdPercentageKey(i, thresholdKey);

        // Retrieve data using key and default value
        // percentage gets random default value for testing purposes.
        int percentage = preferences.getInt(moistureKey, random(1, 100));
        int threshold = preferences.getInt(thresholdKey, DEFAULT_MOISTURE_THRESHOLD);

        // Fill plant array with retrieved data.
        m_plantArr[i] = {i,
                         percentage,
                         threshold};
    }
}

////////////////////////////////////////

void Plants::GetPlant(int id, int *outPercentage, int *outThreshold)
{
    // Check if id is not out of range
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

////////////////////////////////////////

void Plants::SetThresholdPercentage(int id, int percentage)
{
    // Validate percentage value.

    m_plantArr[id].thresholdPercentage = percentage;

    char key[12];
    CreateThresholdPercentageKey(id, key);

    preferences.putInt(key, percentage);
}

void Plants::SetMoisturePercentage(int id, int percentage)
{
    // Validate percentage value.

    m_plantArr[id].moisturePercentage = percentage;

    char key[12];
    CreateMoisturePercentageKey(id, key);

    preferences.putInt(key, percentage);
}

////////////////////////////////////////
// PRIVATE METHODS
////////////////////////////////////////

void Plants::CreateThresholdPercentageKey(int id, char *outKey)
{
    sprintf(outKey, "plant%dtr", id);
}

void Plants::CreateMoisturePercentageKey(int id, char *outKey)
{
    sprintf(outKey, "plant%dmo", id);
}