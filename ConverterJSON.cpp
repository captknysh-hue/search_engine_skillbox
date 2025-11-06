#include "ConverterJSON.h"

ConverterJSON::ConverterJSON() {
     LoadConfig();
     LoadRequests();
}

void ConverterJSON::LoadConfig() {
     std::ifstream configFile("config.json");
     if (!configFile.is_open()) {
          throw std::runtime_error("config file is missing");
     }
     configFile >> configJSON;
     configFile.close();

     if (configJSON.empty() || !configJSON.contains("config")) {
          throw std::runtime_error("config file is empty");
     }

     if (!configJSON["config"].contains("version") ||!configJSON["config"].contains("name")) {
          throw std::runtime_error("config.json has incorrect structure");
     }
     std::cout << "Starting " << configJSON["config"]["version"] << std::endl;
}

std::vector<std::string> ConverterJSON::GetTextDocuments() {
     std::vector<std::string> documents;

     if (!configJSON.contains("files")) {
          std::cerr << "config.json missing 'files' section\n";
          return documents;
     }

     for (auto &path : configJSON["files"]) {
          std::ifstream file(path.get<std::string>());
          if (!file.is_open()) {
               std::cerr << "File not found: " << path.get<std::string>() << std::endl;
               continue;
          }
          std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
          file.close();
          documents.push_back(content);
     }
     return documents;
}

int ConverterJSON::GetResponsesLimit() {
     if (configJSON["config"].contains("max_responses"))
          return configJSON["config"]["max_responses"].get<int>();
     else
          return 5;
}

void ConverterJSON::LoadRequests() {
     std::ifstream file("requests.json");
     if (!file.is_open()) {
          throw std::runtime_error("requests.json file is missing");
     }
     file >> requestJSON;
     file.close();

     if (!requestJSON.contains("requests")) {
          throw std::runtime_error("request.json file is empty");
     }
}

std::vector<std::string> ConverterJSON::GetRequests() {
     std::vector<std::string> result;

     for (auto &req : requestJSON["requests"]) {
          result.push_back(req.get<std::string>());
     }
     return result;
}

void ConverterJSON::PutAnswers(const std::vector<std::vector<std::pair<int, float> > > &answers) {
     json answerJSON;
     json answersObj;

     for (size_t i = 0; i < answers.size(); i++) {
          std::string requestId = "request" + std::string(i + 1 < 10 ? "00" :
                   (i + 1 < 100 ? "0" : "")) + std::to_string(i + 1);

          if (answers[i].empty()) {
               answersObj[requestId] = { {"result", "false"} };
               continue;
          }

          json relevances;
          if (answers[i].size() > 1) {
               relevances["result"] = true;
               json docs;
               for (auto &[docId, rank] : answers[i]) {
                    docs.push_back({ {"docId", docId}, {"rank", rank} });
               }
               relevances["relevance"] = docs;
               answersObj[requestId] = relevances;
          } else {
               answersObj[requestId] = {
                    {"result", true},
                    {"docId", answers[i][0].first},
                    {"rank", answers[i][0].second}
               };
          }
     }

     answerJSON["answers"] = answersObj;

     std::ofstream out("answers.json", std::ios::trunc);
     if (!out.is_open()) {
          throw std::runtime_error("cannot write answers.json");
     }
     out << std::setw(4) << answerJSON;
     out.close();
}




