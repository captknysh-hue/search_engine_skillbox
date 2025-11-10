#include "../include/InvertedIndex.h"
#include <unordered_map>
#include <sstream>
#include <algorithm>

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs) {
    docs = input_docs;
    freq_dictionary.clear();

    std::vector<std::thread> threads;

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        threads.emplace_back([this, doc_id]() {
            std::unordered_map<std::string, size_t> local_freq;
            std::istringstream iss(docs[doc_id]);
            std::string word;

            while (iss >> word) {
                std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                ++local_freq[word];
            }
            std::lock_guard<std::mutex> lock(freq_mutex);
            for (const auto& [w, count] : local_freq) {
                freq_dictionary[w].push_back({doc_id, count});
            }
        });
    }

    for (auto& t : threads)
        if (t.joinable())
            t.join();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    std::lock_guard<std::mutex> lock(freq_mutex);
    if (auto it = freq_dictionary.find(word); it != freq_dictionary.end()) {
        return it->second;
    }
    return {};
}

