#pragma once

#include <string>

class Speaker {
  private:
  public:
    std::string id;
    std::string name;

    Speaker();
    Speaker(std::string id, std::string name);
    ~Speaker() = default;

    Speaker(const Speaker&) = default;
    Speaker(Speaker&&) = default;
    Speaker& operator=(const Speaker&) = default;
    Speaker& operator=(Speaker&&) = default;
};
