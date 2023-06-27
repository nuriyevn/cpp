#include "LibraryCode.hpp"
#include <gtest/gtest.h>
#include <vector>



TEST(TestSuiteSample, TestSample)
{
    int sum = add(3, 4);
    ASSERT_EQ(7, sum);
}

TEST(TestCountPositives, BasicTest)
{
    // Arrange
    std::vector<int> inputVector{1, -2, 3, -4, 5, -6, -7, 8, 9, 10};

    // Act
    int count = countPositives(inputVector);

    // Assert
    ASSERT_EQ(6, count);
}

TEST(TestCountPositives, EmptyVectorTest)
{
    // Arrange
    std::vector<int> inputVector;

    // Act
    int count = countPositives(inputVector);

    // Assert
    ASSERT_EQ(0, count);
}

TEST(TestCountPositives, AllNegativesTest)
{
    // Arrange
    std::vector<int> inputVector{-6, -3, -200, -1, -76};

    // Act
    int count = countPositives(inputVector);

    // Assert, non-fatal assertion, Failed assertion
    EXPECT_EQ(20, count);
    std::cout << "After AllNegativesTest" << std::endl; // This line will be still printed because we use only EXPECT_EQ (non-fatal) counterpart of the assertion 
}

// This test case is not testing one thing which violates TDD principle, that one unit test should check one thing.
TEST(ToUpperTest, BasicTest)
{
    // Arrange
    char inputString[] = "Hello World!";
    std::string strInputString("HELLO WORLD!");

    // Act
    toUpper(inputString);
    std::cout << "After toUpper: " << inputString << '\n';

    // Wrong way of checking string equality, 
    (inputString == "HELLO WORLD!") ? 
        std::cout << "Equal strings\n" : std::cout << "Unequal strings\n";
    // Correct way of chekcing string equality:
    (0 == strcmp(inputString, "HELLO WORLD!")) ?
        std::cout << "Equal strings\n" : std::cout << "Unequal strings\n";
    
    // ASSERT two C strings
    // Wrong Way
    // ASSERT_EQ("HELLO WORLD!", inputString); // We compare addresses, which are always difference for different variable allocations
    // Correct Way
    ASSERT_STREQ("HELLO WORLD!", inputString);// true
    ASSERT_STRCASEEQ("Hello World!", inputString); // true : case insensitive equality check
    ASSERT_STRCASENE("Salut tout le Monde!", inputString); // true: case insensitive inequality check

    // Assert two strings
    ASSERT_EQ(std::string(inputString), strInputString); // true
    // or we can treat two strings as c-strings, using ASSERT_STREQ
    ASSERT_STREQ("HELLO WORLD!", std::string(inputString).c_str()); // true

    std::cout << "End of toUpper basicTest\n";
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}