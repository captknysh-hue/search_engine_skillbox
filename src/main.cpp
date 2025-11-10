#include "../include/ConverterJSON.h"
#include "../include/InvertedIndex.h"
#include "../include/SearchServer.h"
#include <iostream>

int main() {
    ConverterJSON converter;
    auto docs = converter.GetTextDocuments();

    InvertedIndex index;
    index.UpdateDocumentBase(docs);

    SearchServer server(index);
    auto requests = converter.GetRequests();

    auto results = server.search(requests);

    std::vector<std::vector<std::pair<int, float>>> formatted;
    for (const auto& res : results) {
        std::vector<std::pair<int, float>> oneReq;
        for (const auto& r : res) {
            oneReq.push_back({(int)r.doc_id, r.rank});
        }
        formatted.push_back(oneReq);
    }

    converter.PutAnswers(formatted);

    std::cout << "Search complete. Results written to answers.json\n";
}