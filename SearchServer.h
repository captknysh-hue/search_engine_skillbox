#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include <string>
#include <vector>
#include <cmath>
#include "InvertedIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && fabs(rank - other.rank) < 1e-6);
    }
};

class SearchServer {
public:
    explicit SearchServer(InvertedIndex& idx) : index(idx) { }

    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& index;
};

#endif //SEARCH_ENGINE_SEARCHSERVER_H