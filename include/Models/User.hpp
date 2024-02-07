#pragma once

#include <string>

class User {
  private:
  public:
    User();
    ~User() = default;

    std::string id;

    std::string userType;

    std::string username;
    std::string email;
    std::string name;

    User(const User&) = default;
    User(User&&) = default;
    User& operator=(const User&) = default;
    User& operator=(User&&) = default;
};
