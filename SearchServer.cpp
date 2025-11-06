#include "SearchServer.h"
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <cmath>

SearchServer::SearchServer(InvertedIndex &idx) : index(idx) {}

std::vector<std::vector<RelativeIndex> > SearchServer::search(
    const std::vector<std::string> &queries_input) {

    std::vector<std::vector<RelativeIndex>> result;
    for (const auto& query : queries_input) {
        std::map<size_t, size_t> doc_absolute_relevance;
        std::istringstream iss(query);
        std::set<std::string> unique_words;
        std::string word;

        while (iss >> word) {
            unique_words.insert(word);
        }

        for (const auto& w : unique_words) {
            for (const auto& entry : index.GetWordCount(w)) {
                doc_absolute_relevance[entry.doc_id] += entry.count;
            }
        }

        if (doc_absolute_relevance.empty()) {
            result.push_back({});
            continue;
        }

        size_t max_abs_relevance = 0;
        for (auto& [doc_id, abs_rel] : doc_absolute_relevance)
            if (abs_rel > max_abs_relevance) max_abs_relevance = abs_rel;

        std::vector<RelativeIndex> rel_result;
        for (auto& [doc_id, abs_rel] : doc_absolute_relevance) {
            RelativeIndex rel{};
            rel.doc_id = doc_id;
            rel.rank = static_cast<float>(abs_rel) / max_abs_relevance;
            rel_result.push_back(rel);
        }

        std::sort(rel_result.begin(), rel_result.end(),
            [](const RelativeIndex& a, const RelativeIndex& b) {
                if (fabs(a.rank - b.rank) > 1e-6)
                    return a.rank > b.rank;
                return a.doc_id < b.doc_id;
            });

        if (rel_result.size() > 5)
            rel_result.resize(5);
        result.push_back(rel_result);
    }
    return result;
}

