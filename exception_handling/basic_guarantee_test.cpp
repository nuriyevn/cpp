#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DateTestFixture : public testing::Test
{
    public:
        void SetUp() override;
    private:
        Date date;
}

void DataTestFixture::SetUp()
{
    cout << "SetUp called\n" << endl;
    cout << date;
}

TEST_F(DateTestFixture , ValidDateTest)
{
    Date
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}