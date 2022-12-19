#pragma once

// REMOVE ARDUINO.H WHEN RANDOM IS NO LONGER NECESSARY FOR TEST DATA.
#include "Arduino.h"

#include "config.h"

class Plants
{
public:
    Plants();

    static void Init();

    static void GetPlant(int id, int *outPercentage, int *outThreshold);

    static int GetMoisturePercentage(int id);
    static int GetThresholdPercentage(int id);

    static void SetThresholdPercentage(int id, int percentage);

private:
    typedef struct Plant
    {
        int id;
        int moisturePercentage;
        int thresholdPercentage;
    } Plant;

    static inline Plant m_plantArr[PLANT_COUNT];

    static inline int m_defaultMoistureThreshold;
};