#include <iostream>
#include <gtest/gtest.h>

TEST(DummyCpp, testcase) {
    std::cout << "hello from dummymqtt_test";
    ASSERT_FALSE(false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
