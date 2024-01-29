#pragma once

#include <Settings.hpp>

class SettingsServiceClass {
  private:
  public:
    void connectToWiFi(const std::string& ssid, const std::string& password);

    void saveSettings(Settings& settings);
    void loadSettings(Settings& settings);
};
