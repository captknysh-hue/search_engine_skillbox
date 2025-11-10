#include "../include/SearchServer.h"
#include <sstream>
#include <algorithm>
#include <unordered_map>

std::vector<std::vector<RelativeIndex>> SearchServer::search(
    const std::vector<std::string>& queries_input) {

    std::vector<std::vector<RelativeIndex>> result;
    for (const auto& query : queries_input) {
        std::unordered_map<size_t, float> abs_relevance;
        std::istringstream iss(query);
        std::string word;

        while (iss >> word) {
            auto entries = index.GetWordCount(word);
            for (auto& e : entries) {
                abs_relevance[e.doc_id] += e.count;
            }
        }

        if (abs_relevance.empty()) {
            result.push_back({});
            continue;
        }

        float max_relevance = 0.0f;
        for (const auto& [_, value] : abs_relevance)
            max_relevance = std::max(max_relevance, value);

        std::vector<RelativeIndex> relVec;
        for (const auto& [id, value] : abs_relevance) {
            relVec.push_back({id, value / max_relevance});
        }

        std::sort(relVec.begin(), relVec.end(),
            [](const RelativeIndex& a, const RelativeIndex& b) {
                return a.rank > b.rank;
            });

        if (relVec.size() > 5)
            relVec.resize(5);
        result.push_back(relVec);
    }
    return result;
}

