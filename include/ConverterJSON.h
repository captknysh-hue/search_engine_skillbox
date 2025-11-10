#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
#include <map>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

class ConverterJSON {
public:
    ConverterJSON();
    std::vector<std::string>GetTextDocuments();
    int GetResponseLimit();
    std::vector<std::string> GetRequests();
    void PutAnswers(const std::vector<std::vector<std::pair<int, float>>>& answers);

private:
    json configJSON;
    json requestJSON;

    void LoadConfig();
    void LoadRequests();
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H