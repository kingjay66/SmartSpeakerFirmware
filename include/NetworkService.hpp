#pragma once

#include <Settings.hpp>
#include <Speaker.hpp>
#include <User.hpp>
#include <functional>
#include <string>

#ifdef PRODUCTION
    #ifndef BACKEND_SERVER_ADDR
        #define BACKEND_SERVER_ADDR "https://yarmanprojects.com/speaker/api/"
    #endif  // BACKEND_SERVER_ADDR
#else       // PRODUCTION
    #ifndef TESTING
        #define TESTING
    #endif  // TESTING
    #ifndef BACKEND_SERVER_ADDR
        #define BACKEND_SERVER_ADDR "http://127.0.0.1:8080/"
    #endif  // BACKEND_SERVER_ADDR
#endif      // PRODUCTION

#define REQUEST_ERR_OK 200

#define REQUEST_ERR_CURL_INIT -1
#define REQUEST_ERR_CURL_PERFORM -2
#define REQUEST_ERR_NO_JSON -3
#define REQUEST_ERR_OBJ_NOID -4
#define REQUEST_ERR_JSON_PARSE -5

using RequestError = long;

struct AuthRequest
{
    const std::string username;
    const std::string email;
    const std::string password;
};

struct UserUpdateRequest
{
    const std::string name;
    const std::string username;
    const std::string email;
};

struct AuthResponse
{
    std::string token;
};

class NetworkServiceClass
{
  private:
    std::string token;

    std::string loadToken();
    void saveToken();

  public:
    NetworkServiceClass() = default;
    NetworkServiceClass(const NetworkServiceClass&) = default;
    NetworkServiceClass(NetworkServiceClass&&) = default;
    NetworkServiceClass& operator=(const NetworkServiceClass&) = default;
    NetworkServiceClass& operator=(NetworkServiceClass&&) = delete;
    ~NetworkServiceClass();

    void authRegister(
        AuthRequest req,
        std::function<void(RequestError err, AuthResponse& response)> callback);
    void authLogin(
        AuthRequest req,
        std::function<void(RequestError err, AuthResponse& response)> callback);

    void userGetCurrentUserInfo(
        User& user,
        std::function<void(RequestError err, User& user)> callback);
    void userUpdateCurrentUserInfo(
        User& user,
        std::function<void(RequestError err, User& user)> callback);

    void createNewSpeaker(
        Speaker& speaker,
        std::function<void(RequestError err, Speaker& speaker)> callback);
    void updateSpeaker(
        Speaker& speaker,
        std::function<void(RequestError err, Speaker& speaker)>& callback);
    void deleteSpeaker(Speaker& speaker,
                       std::function<void(RequestError err)>& callback);
};

extern NetworkServiceClass NetworkService;

