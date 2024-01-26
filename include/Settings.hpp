#pragma once

#include <string>
class Settings
{
  private:
    std::string wifi_ssid;
    std::string wifi_pass;
  public:
    Settings();
    ~Settings();

    Settings(const Settings&) = default;
    Settings(Settings&&) = default;
    Settings& operator=(const Settings&) = default;
    Settings& operator=(Settings&&) = default;
};
