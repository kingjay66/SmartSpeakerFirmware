#pragma once

#include <string>
enum UserType {
  USER = 0,
  ADMIN = 1,
};

class User {
private:
public:
  User();
  ~User();

  std::string id;

  UserType userType;

  std::string username;
  std::string email;
  std::string name;

  User(const User &) = default;
  User(User &&) = default;
  User &operator=(const User &) = default;
  User &operator=(User &&) = default;
};

