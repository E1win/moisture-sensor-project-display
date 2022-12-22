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
    if (IDOutOfRange(id))
    {
        Serial.println("WARNING: Plant ID out of range at GetPlant, given default values (0, 0)");

        *outPercentage = 0;
        *outThreshold = 0;

        return;
    }

    *outPercentage = m_plantArr[id].moisturePercentage;
    *outThreshold = m_plantArr[id].thresholdPercentage;
}

int Plants::GetMoisturePercentage(int id)
{
    if (IDOutOfRange(id))
    {
        Serial.println("WARNING: Plant ID out of range at GetMoisturePercentage, returned default value (0)");
        return 0;
    }

    return m_plantArr[id].moisturePercentage;
}

int Plants::GetThresholdPercentage(int id)
{
    if (IDOutOfRange(id))
    {
        Serial.println("WARNING: Plant ID out of range at GetThresholdPercentage, returned default value (0)");
        return 0;
    }

    return m_plantArr[id].thresholdPercentage;
}

////////////////////////////////////////

void Plants::SetThresholdPercentage(int id, int percentage)
{
    if (IDOutOfRange(id))
    {
        Serial.println("WARNING: ID out of range");
        return;
    }

    // Validate percentage value.

    m_plantArr[id].thresholdPercentage = percentage;

    char key[12];
    CreateThresholdPercentageKey(id, key);

    preferences.putInt(key, percentage);
}

void Plants::SetMoisturePercentage(int id, int percentage)
{
    if (IDOutOfRange(id))
    {
        Serial.println("WARNING: ID out of range");
        return;
    }

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

bool Plants::IDOutOfRange(int id)
{
    return id < 0 || id >= PLANT_COUNT;
}