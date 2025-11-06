#include <gtest/gtest.h>
#include "../ConverterJSON.h"

TEST(sampleTestCase, BasicEquality) {
    EXPECT_EQ(1, 1);
}

TEST(ConverterJSON, LoadConfigFile) {
    ConverterJSON conv;
    EXPECT_NO_THROW({
        auto docs = conv.GetTextDocuments();
    });
}

TEST(ConverterJSON, ResponsesLimitDefault) {
    ConverterJSON conv;
    int limit = conv.GetResponsesLimit();
    EXPECT_GT(limit, 0);
}

TEST(SearchTest, Basic) {
    ASSERT_EQ(2 +2, 4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}