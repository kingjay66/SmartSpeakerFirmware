#pragma once

class Settings
{
  private:
  public:
    Settings();
    ~Settings();

    Settings(const Settings&) = default;
    Settings(Settings&&) = default;
    Settings& operator=(const Settings&) = default;
    Settings& operator=(Settings&&) = default;
};
