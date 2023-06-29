#include <iostream>
#include <gtest/gtest.h>
#include <vector>

#include "LibraryCode.hpp"

TEST(SquareRootTest, NegativeArgumentTest)
{
    double inputValue = -9;
    //ASSERT_ANY_THROW(mySqrt(inputValue));
    ASSERT_THROW(mySqrt(inputValue), std::logic_error);
}

TEST(SquareRootTest, PositiveArgumentTest)
{
    double inputValue = 9;
    //ASSERT_ANY_THROW(mySqrt(inputValue));
    ASSERT_NO_THROW(mySqrt(inputValue));
}

TEST(NumberOfDaysLived, Lived90Years)
{
    int years = 90;
    int days = 0;

    EXPECT_NO_THROW(days = numberOfDaysLived(years));
    ASSERT_GE(32850, days);
}

TEST(NumberOfDaysLived, NegativeNumberOfYears)
{
    int years = -5;
    ASSERT_THROW(numberOfDaysLived(years), std::runtime_error);
}

TEST(NumberOfDaysLived, UnrealNumberOfYears)
{
    int years = 150;
    int days = 0;

    ASSERT_THROW(numberOfDaysLived(years), std::logic_error);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}