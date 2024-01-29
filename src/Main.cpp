#include <NetworkService.hpp>
#include <GUI.hpp>
#include <User.hpp>

#include <iostream>
#include <thread>

int main() {
    GUI.init();
    GUI.mainThread();
    GUI.close();
}

int rest_api_test()
{
    AuthRequest req = {
        .username = "tim",
        .email = "email",
        .password = "password",
    };
    NetworkService.authRegister(req, [=](RequestError err, AuthResponse& response) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << response.token << '\n';
    });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    NetworkService.authLogin(req, [=](RequestError err, AuthResponse& response) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << response.token << '\n';
    });
    std::this_thread::sleep_for(std::chrono::seconds(3));
    User user;
    NetworkService.userGetCurrentUserInfo(user, [=](RequestError err, User& user) {
        if (err != REQUEST_ERR_OK)
        {
            std::cerr << err << '\n';
            return;
        }
        std::cout << user.id << '\n';
    });
    while (true)
    {};
    return EXIT_SUCCESS;
}
