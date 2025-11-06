#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    docs = input_docs;
    freq_dictionary.clear();

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++) {
        std::istringstream iss(docs[doc_id]);
        std::map<std::string, size_t> word_count;
        std::string word;

        while (iss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            ++word_count[word];
        }

        for (auto& [word, count] : word_count) {
            freq_dictionary[word].push_back({doc_id, count});
        }
    }
}
std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) const {
    std::string lower = word;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    auto it = freq_dictionary.find(lower);
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    return {};
}

