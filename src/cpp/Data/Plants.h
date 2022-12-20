#pragma once

// REMOVE ARDUINO.H WHEN RANDOM IS NO LONGER NECESSARY FOR TEST DATA.
#include "Arduino.h"

// Native ESP32 library
#include <Preferences.h>

#include "config.h"

class Plants
{
public:
    static void Init();

    static void GetPlant(int id, int *outPercentage, int *outThreshold);

    static int GetMoisturePercentage(int id);
    static int GetThresholdPercentage(int id);

    static void SetThresholdPercentage(int id, int percentage);
    static void SetMoisturePercentage(int id, int percentage);

private:
    Plants();

    static void CreateThresholdPercentageKey(int id, char *outKey);
    static void CreateMoisturePercentageKey(int id, char *outKey);
};