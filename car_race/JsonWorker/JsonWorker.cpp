#include "json_worker.h";

std::string JSONWorker::getJsonTokenFromString(const std::string rawJson) {
    Json::Value root; // root value for processing json string to structure
    const auto rawJsonLength = static_cast<int>(rawJson.length());
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &root,
        &err)) {
        std::cout << "error" << std::endl;
    }
    const std::string token = root["token"].asString();
    return token;
}