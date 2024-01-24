#pragma once

#include <Settings.hpp>
#include <Speaker.hpp>
#include <User.hpp>
#include <functional>
#include <string>

#ifdef PRODUCTION
    #define BACKEND_SERVER_ADDR "https://yarmanprojects.com/speaker/api/"
#else  // PRODUCTION
    #ifndef TESTING
        #define TESTING
    #endif  // TESTING
    #define BACKEND_SERVER_ADDR "http://127.0.0.1:8080/api/"
#endif  // PRODUCTION

struct RequestError
{
    const std::string error;
};

struct AuthRequest
{
    const char* username;
    const char* email;
    const char* password;
};

struct UserUpdateRequest
{
    const char* name;
    const char* username;
    const char* email;
};

struct AuthResponse
{
    const char* token;
};

class NetworkServiceClass
{
  private:
    std::string token;

  public:
    void authRegister(
        AuthRequest req,
        std::function<void(RequestError* err, AuthResponse& response)> callback);
    void authLogin(
        AuthRequest req,
        std::function<void(RequestError* err, AuthResponse& response)> callback);

    void userGetCurrentUserInfo(
        User& user,
        std::function<void(RequestError* err, User& user)> callback);
    void userUpdateCurrentUserInfo(
        User& user,
        std::function<void(RequestError* err, User& user)> callback);

    void createNewSpeaker(
        Speaker& speaker,
        std::function<void(RequestError* err, Speaker& speaker)> callback);
    void updateSpeaker(
        Speaker& speaker,
        std::function<void(RequestError* err, Speaker& speaker)> &callback);
    void deleteSpeaker(Speaker& speaker,
                       std::function<void(RequestError* err)> callback);
};

extern NetworkServiceClass NetworkService;

