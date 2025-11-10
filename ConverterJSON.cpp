#include "ConverterJSON.h"
#include <fstream>
#include <iostream>

ConverterJSON::ConverterJSON() = default;

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream file("confirg.json");
    json config;
    file >> config;
    file.close();

    std::vector<std::string> docs;
    for (const auto& path : config["files"]) {
        std::ifstream f(path);
        if (f) {
            std::string text((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            docs.push_back(text);
        } else {
            std::cerr << "File not found: " << path << std::endl;
        }
    }
    return docs;
}

int ConverterJSON::GetResponseLimit() {
    std::ifstream file("config.json");
    json config;
    file >> config;
    file.close();
    return config["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file("requests.json");
    json requests;
    file >> requests;
    file.close();

    std::vector<std::string> reqs;
    for (const auto& r : requests["requests"]) {
        reqs.push_back(r);
    }
    return reqs;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers) {
    json result;
    result["answers"] = json::object();

    for (size_t i = 0; i < answers.size(); i++) {
        json requestResult;
        std::string key = "request" + std::to_string(i + 1);

        if (answers[i].empty()) {
            requestResult["result"] = false;
        } else {
            requestResult["result"] = true;
            requestResult["relevance"] = json::array();

            for(const auto& [docId, rank] : answers[i]) {
                json entry;
                entry["docId"] = docId;
                entry["rank"] = rank;
                requestResult["relevance"].push_back(entry);
            }
        }
        result["answers"][key] = requestResult;
    }

    std::ofstream out("answers.json");
    out << std::setw(4) << result;
    out.close();
}




