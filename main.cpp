#include "ConverterJSON.h"

int main() {
    try {
        ConverterJSON converter;

        auto docs = converter.GetTextDocuments();
        auto queries = converter.GetRequests();
        int limit = converter.GetResponsesLimit();

        std::cout << "Loaded " << docs.size() << " documents\n";
        std::cout << "Loaded " << queries.size() << " queries\n";
        std::cout << "Response limit: " << limit << std::endl;

        std::vector<std::vector<std::pair<int, float>>> dummyAnswers = {
            { {0, 0.9f}, {1, 0.7f} },
            { },
            { {2, 0.8f} }
        };
        converter.PutAnswers(dummyAnswers);
    } catch (std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}