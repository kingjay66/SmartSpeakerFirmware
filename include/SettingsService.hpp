#pragma once

#include <Settings.hpp>

class SettingsServiceClass
{
  private:
  public:
    void connectToWiFi(const char* ssid, const char* password);

    void saveSettings(Settings& settings);
    void loadSettings(Settings& settings);
};
