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

//void JSONWorker::sendPlayerRecordedData(int currentLap, int currentFrame, float currentVelocity, float currentRotation) {
//    static Json::Value root;
//
//    std::string currentLapString = std::to_string(currentLap);
//
//    if(currentFrame % 10 == 0) {
//        root["Records"][0][currentLapString][currentFrame/10]["Frame"] = currentFrame;
//        root["Records"][0][currentLapString][currentFrame/10]["currentVelocity"] = currentVelocity;
//        root["Records"][0][currentLapString][currentFrame/10]["currentRotation"] = currentRotation;
//    } else if (currentFrame == 0) {
//        root["Records"][0][currentLapString][0]["Frame"] = currentFrame;
//        root["Records"][0][currentLapString][0]["currentVelocity"] = currentVelocity;
//        root["Records"][0][currentLapString][0]["currentRotation"] = currentRotation;
//    }
//
// 
//
//    std::cout << root;
//}