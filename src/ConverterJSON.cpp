#include "../include/ConverterJSON.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <filesystem>

ConverterJSON::ConverterJSON() = default;

std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::ifstream file("config/config.json");
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
    std::ifstream file("config/config.json");
    json config;
    file >> config;
    file.close();
    return config["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::ifstream file("config/requests.json");
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
    nlohmann::json jAnswers;

    for (size_t i = 0; i < answers.size(); i++) {
        nlohmann::json request;
        request["request"] = "request" + std::to_string(i + 1);

        if (answers[i].empty()) {
            request["result"] = false;
        } else {
            request["result"] = true;
            nlohmann::json relevance = nlohmann::json::array();

            for(const auto& [docId, rank] : answers[i]) {
                nlohmann::json entry;
                entry["docId"] = docId;
                entry["rank"] = rank;
                relevance.push_back(entry);
            }
            request["relevance"] = relevance;
        }
        jAnswers["answers"].push_back(request);
    }

    std::ofstream out("config/answers.json");
    if (!out.is_open()) {
        std::cerr << "File was not opened for writing!" << std::endl;
        return;
    }
    out << std::setw(4) << jAnswers;
    out.close();

    std::cout << "Search results saved in answers.json file! " << std::endl;
}




