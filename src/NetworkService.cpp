#include <NetworkService.hpp>

#include <curl/curl.h>
#include <json.hpp>
#include <string>
#include <thread>

using json = nlohmann::json;

void from_json_to_user(const json& json, User& user)
{
    json.at("id").get_to(user.id);
    if (json.contains("name"))
    {
        json.at("name").get_to(user.name);
    }
    json.at("email").get_to(user.email);
    json.at("username").get_to(user.username);
    json.at("userType").get_to(user.userType);
}

void from_json_to_speaker(const json& json, Speaker& speaker)
{
    json.at("id").get_to(speaker.id);
    if (json.contains("name"))
    {
        json.at("name").get_to(speaker.name);
    }
}

static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    (static_cast<std::string*>(userp))->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}
void getRequest(
    const std::string& token,
    const std::string& url,
    const std::function<void(RequestError err, json jsonResponse)>& callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err = REQUEST_ERR_CURL_INIT;
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
        RequestError err = 0;
        if (res != CURLE_OK)
        {
            err = REQUEST_ERR_CURL_PERFORM;
            callback(err, nullptr);
            return;
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &err);
        if (err != REQUEST_ERR_OK)
        {
            callback(err, nullptr);
            return;
        }
        if (readBuffer == "")
        {
            err = REQUEST_ERR_NO_JSON;
            callback(err, nullptr);
            return;
        }
        json parsed = json::parse(readBuffer);
        callback(err, parsed);

        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void putRequest(
    const std::string& token,
    const std::string& url,
    const json& jsonObj,
    const std::function<void(RequestError err, json jsonResponse)>& callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err = REQUEST_ERR_CURL_INIT;
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
        RequestError err = 0;
        if (res != CURLE_OK)
        {
            err = REQUEST_ERR_CURL_PERFORM;
            callback(err, nullptr);
            return;
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &err);
        if (err != REQUEST_ERR_OK)
        {
            callback(err, nullptr);
            return;
        }
        if (readBuffer == "")
        {
            err = REQUEST_ERR_NO_JSON;
            callback(err, nullptr);
            return;
        }
        json parsed = json::parse(readBuffer);
        callback(err, parsed);

        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void postRequest(
    const std::string& token,
    const std::string& url,
    const json& jsonObj,
    const std::function<void(RequestError err, json jsonResponse)>& callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err = REQUEST_ERR_CURL_INIT;
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
        std::string readBuffer;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        RequestError err = 0;
        if (res != CURLE_OK)
        {
            err = REQUEST_ERR_CURL_PERFORM;
            callback(err, nullptr);
            return;
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &err);
        if (err != REQUEST_ERR_OK)
        {
            callback(err, nullptr);
            return;
        }
        if (readBuffer == "")
        {
            err = REQUEST_ERR_NO_JSON;
            callback(err, nullptr);
            return;
        }
        json parsed = json::parse(readBuffer);
        callback(err, parsed);
        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void deleteRequest(
    const std::string& token,
    const std::string& url,
    const std::function<void(RequestError err, json jsonResponse)>& callback)
{
    std::thread reqThread([=]() {
        CURL* curl = curl_easy_init();
        if (curl == nullptr)
        {
            RequestError err = REQUEST_ERR_CURL_INIT;
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
        RequestError err = 0;
        if (res != CURLE_OK)
        {
            err = REQUEST_ERR_CURL_PERFORM;
            callback(err, nullptr);
            return;
        }
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &err);
        if (err != REQUEST_ERR_OK)
        {
            callback(err, nullptr);
            return;
        }
        if (readBuffer == "")
        {
            err = REQUEST_ERR_NO_JSON;
            callback(err, nullptr);
            return;
        }
        json parsed = json::parse(readBuffer);
        callback(err, parsed);
        curl_easy_cleanup(curl);
    });

    reqThread.detach();
}

void NetworkServiceClass::authRegister(
    AuthRequest req,
    std::function<void(RequestError err, AuthResponse& response)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "auth/register";
    json authJson = json{{"username", req.username},
                         {"password", req.password},
                         {"email", req.email}};
    try
    {
        postRequest(this->token, url, authJson, [&](RequestError err, json jsonResponse) {
            AuthResponse response{};
            if (err != REQUEST_ERR_OK)
            {
                callback(err, response);
                return;
            }
            std::string tokenStr = jsonResponse.at("token");
            this->token = tokenStr;
            response.token = tokenStr;
            callback(err, response);
        });
    }
    catch (const json::parse_error& ex)
    {
        RequestError err = REQUEST_ERR_JSON_PARSE;
        AuthResponse response{};
        callback(err, response);
    }
}

void NetworkServiceClass::authLogin(
    AuthRequest req,
    std::function<void(RequestError err, AuthResponse& response)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "auth/authenticate";
    json authJson = json{{"username", req.username},
                         {"password", req.password}};
    try
    {
        postRequest(this->token, url, authJson, [this, &callback](RequestError err, json jsonResponse) {
            AuthResponse response{};
            if (err != REQUEST_ERR_OK)
            {
                callback(err, response);
                return;
            }
            std::string tokenStr = jsonResponse.at("token");
            this->token = tokenStr;
            response.token = tokenStr;
            callback(err, response);
        });
    }
    catch (const json::parse_error& ex)
    {
        RequestError err = REQUEST_ERR_JSON_PARSE;
        AuthResponse response{};
        callback(err, response);
    }
}

void NetworkServiceClass::userGetCurrentUserInfo(
    User& user,
    std::function<void(RequestError err, User& user)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "users";
    try
    {
        getRequest(this->token, url, [this, &callback, &user](RequestError err, const json& jsonResponse) {
            if (err != REQUEST_ERR_OK)
            {
                callback(err, user);
                return;
            }
            from_json_to_user(jsonResponse, user);
            callback(err, user);
        });
    }
    catch (const json::parse_error& ex)
    {
        RequestError err = REQUEST_ERR_JSON_PARSE;
        callback(err, user);
    }
}

void NetworkServiceClass::userUpdateCurrentUserInfo(
    User& user,
    std::function<void(RequestError err, User& user)> callback)
{
    const std::string url = std::string(BACKEND_SERVER_ADDR) + "users";
    json jsonObj = json{{"username", user.username},
                        {"email", user.email},
                        {"name", user.name}};
    try
    {
        putRequest(this->token, url, jsonObj, [this, &callback, &user](RequestError err, const json& jsonResponse) {
            if (err != REQUEST_ERR_OK)
            {
                callback(err, user);
                return;
            }
            from_json_to_user(jsonResponse, user);
            callback(err, user);
        });
    }
    catch (const json::parse_error& ex)
    {
        RequestError err = REQUEST_ERR_JSON_PARSE;
        callback(err, user);
    }
}

void NetworkServiceClass::createNewSpeaker(
    Speaker& speaker,
    std::function<void(RequestError err, Speaker& speaker)> callback)
{
    try
    {
        const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers";
        json jsonObj = json{{"name", speaker.name}, {"id", speaker.id}};
        postRequest(this->token, url, jsonObj, [this, &callback, &speaker](RequestError err, const json& jsonResponse) {
            if (err != REQUEST_ERR_OK)
            {
                callback(err, speaker);
            }
            from_json_to_speaker(jsonResponse, speaker);
            callback(err, speaker);
        });
    }
    catch (const json::parse_error& ex)
    {
        RequestError err = REQUEST_ERR_JSON_PARSE;
        callback(err, speaker);
    }
}

void NetworkServiceClass::updateSpeaker(
    Speaker& speaker,
    std::function<void(RequestError err, Speaker& speaker)>& callback)
{
    if (speaker.id == "NOID")
    {
        callback(REQUEST_ERR_OBJ_NOID, speaker);
        return;
    }
    try
    {
        const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers/" + speaker.id;
        json jsonObj = json{{"name", speaker.name}, {"id", speaker.id}};
        putRequest(this->token, url, jsonObj, [this, &callback](RequestError err, const json& jsonResponse) {
            Speaker speaker;
            if (err != REQUEST_ERR_OK)
            {
                callback(err, speaker);
                return;
            }
            from_json_to_speaker(jsonResponse, speaker);
            callback(err, speaker);
        });
    }
    catch (const json::parse_error& ex)
    {
        callback(REQUEST_ERR_JSON_PARSE, speaker);
    }
}

void NetworkServiceClass::deleteSpeaker(
    Speaker& speaker,
    std::function<void(RequestError err)>& callback)
{
    try
    {
        if (speaker.id == "NOID")
        {
            callback(REQUEST_ERR_OBJ_NOID);
            return;
        }
        const std::string url = std::string(BACKEND_SERVER_ADDR) + "speakers/" + speaker.id;
        deleteRequest(this->token, url, [&callback](RequestError err, const json&  /*jsonResponse*/) {
            callback(err);
        });
    }
    catch (const json::parse_error& ex)
    {
        callback(REQUEST_ERR_JSON_PARSE);
    }
}

std::string NetworkServiceClass::loadToken()
{
    this->token = "";
    return "";
}

void NetworkServiceClass::saveToken()
{
    this->token = "";
}
