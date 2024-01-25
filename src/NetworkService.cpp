#include <NetworkService.hpp>

#include <curl/curl.h>
#include <iostream>
#include <json.hpp>
#include <string>
#include <thread>

using json = nlohmann::json;

NetworkServiceClass NetworkService;

void from_json_to_user(const json& json, User& user)
{
    json.at("id").get_to(user.id);
    json.at("name").get_to(user.name);
    json.at("email").get_to(user.email);
    json.at("username").get_to(user.username);
    json.at("userType").get_to(user.userType);
}

void from_json_to_speaker(const json& json, Speaker& speaker)
{
    json.at("id").get_to(speaker.id);
    json.at("name").get_to(speaker.name);
}

static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
void getRequest(
    const std::string& token,
    const std::string& url,
    std::function<void(RequestError& err, json jsonResponse)> callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err{.error = "CURL_EASY_INIT_FAILED"};
            callback(err, json());
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        if (token.c_str() != nullptr && token != "")
        {
            std::string authHeader = "Authorization: Bearer " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        RequestError err;
        if (res != CURLE_OK)
        {
            RequestError err{.error = std::string("CURL_EASY_PERFORM_FAILED: ") +
                                      curl_easy_strerror(res)};
            callback(err, json::parse(readBuffer));
            curl_easy_cleanup(curl);
        }
        callback(err, json::parse(readBuffer));

        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void putRequest(
    const std::string& token,
    const std::string& url,
    const json& jsonObj,
    std::function<void(RequestError& err, json jsonResponse)> callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err{.error = "CURL_EASY_INIT_FAILED"};
            callback(err, json());
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string jsonData = jsonObj.dump();
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        if (token.c_str() != nullptr && token != "")
        {
            std::string authHeader = "Authorization: Bearer " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        CURLcode res = curl_easy_perform(curl);
        RequestError err;
        if (res != CURLE_OK)
        {
            RequestError err{.error = std::string("CURL_EASY_PERFORM_FAILED: ") +
                                      curl_easy_strerror(res)};
            callback(err, json::parse(readBuffer));
            curl_easy_cleanup(curl);
        }
        callback(err, json::parse(readBuffer));

        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void postRequest(
    const std::string& token,
    const std::string& url,
    const json& jsonObj,
    std::function<void(RequestError& err, json jsonResponse)> callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err{.error = "CURL_EASY_INIT_FAILED"};
            callback(err, json());
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        std::string jsonData = jsonObj.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        if (token.c_str() != nullptr && token != "")
        {
            std::string authHeader = "Authorization: Bearer " + token;
            headers = curl_slist_append(headers, authHeader.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        std::string* readBuffer = new std::string("");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, readBuffer);

        CURLcode res = curl_easy_perform(curl);
        RequestError err;
        if (res != CURLE_OK)
        {
            err.error = std::string("CURL_EASY_PERFORM_FAILED: ") +
                        curl_easy_strerror(res);
        }
        callback(err, json::parse(*readBuffer));
        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void NetworkServiceClass::authRegister(
    AuthRequest req,
    std::function<void(RequestError& err, AuthResponse& response)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "auth/register";
    json authJson = json{{"username", req.username},
                         {"password", req.password},
                         {"email", req.email}};
    postRequest(this->token, url, authJson, [&](RequestError& err, json jsonResponse) {
        AuthResponse response;
        if (err.error != "")
        {
            callback(err, response);
            return;
        }
        std::string tokenStr = jsonResponse.at("token");
        this->token = tokenStr;
        response.token = tokenStr.c_str();
        callback(err, response);
    });
}

void NetworkServiceClass::authLogin(
    AuthRequest req,
    std::function<void(RequestError& err, AuthResponse& response)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "auth/authenticate";
    json authJson = json{{"username", req.username},
                         {"password", req.password}};
    postRequest(this->token, url, authJson, [this, &callback](RequestError& err, json jsonResponse) {
        AuthResponse response{};
        if (err.error != "")
        {
            callback(err, response);
            return;
        }
        std::string tokenStr = jsonResponse.at("token");
        this->token = tokenStr;
        response.token = tokenStr.c_str();
        callback(err, response);
    });
}

void NetworkServiceClass::userGetCurrentUserInfo(
    User& user,
    std::function<void(RequestError& err, User& user)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "users";
    getRequest(this->token, url, [this, &callback, &user](RequestError& err, const json& jsonResponse) {
        if (err.error != "")
        {
            callback(err, user);
            return;
        }
        from_json_to_user(jsonResponse, user);
        callback(err, user);
    });
}

void NetworkServiceClass::userUpdateCurrentUserInfo(
    User& user,
    std::function<void(RequestError& err, User& user)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "users";
    json jsonObj = json{{"username", user.username},
                        {"email", user.email},
                        {"name", user.name}};
    putRequest(this->token, url, jsonObj, [this, &callback, &user](RequestError& err, const json& jsonResponse) {
        if (err.error != "")
        {
            callback(err, user);
            return;
        }
        from_json_to_user(jsonResponse, user);
        callback(err, user);
    });
}

void NetworkServiceClass::createNewSpeaker(
    Speaker& speaker,
    std::function<void(RequestError& err, Speaker& speaker)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers";
    json jsonObj = json{{"name", speaker.name}, {"id", speaker.id}};
    postRequest(this->token, url, jsonObj, [this, &callback, &speaker](RequestError& err, const json& jsonResponse) {
        if (err.error != "")
        {
            callback(err, speaker);
        }
        from_json_to_speaker(jsonResponse, speaker);
        callback(err, speaker);
    });
}

void NetworkServiceClass::updateSpeaker(
    Speaker& speaker,
    std::function<void(RequestError& err, Speaker& speaker)>& callback)
{
    if (speaker.id == "NOID")
    {
        RequestError err{.error = "SPEAKER_UPD_NOID"};
        callback(err, speaker);
        return;
    }
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers/" + speaker.id;
    json jsonObj = json{{"name", speaker.name}, {"id", speaker.id}};
    putRequest(this->token, url, jsonObj, [this, &callback](RequestError& err, const json& jsonResponse) {
        Speaker speaker;
        if (err.error != "")
        {
            callback(err, speaker);
            return;
        }
        from_json_to_speaker(jsonResponse, speaker);
        callback(err, speaker);
    });
}

void NetworkServiceClass::deleteSpeaker(
    Speaker& speaker,
    std::function<void(RequestError& err)> callback)
{
    if (speaker.id == "NOID")
    {
        RequestError err{.error = "SPEAKER_DEL_NOID"};
        callback(err);
        return;
    }
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers";
}
