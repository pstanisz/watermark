// Copyright (c) 2022, Piotr Staniszewski

#include <gmock/gmock.h>

#include <image.h>
#include <exception.h>

#include <cv_mock.h>

namespace watermark
{
    namespace mock
    {
        Imread_mock *g_imread_mock;
    }
}

namespace test
{
    using ::testing::_;
    using ::testing::Return;

    class Image_test : public ::testing::Test
    {
    protected:
        virtual void SetUp() override
        {
            watermark::mock::g_imread_mock = new watermark::mock::Imread_mock();
        }

        virtual void TearDown() override
        {
            delete watermark::mock::g_imread_mock;
        }
    };

    TEST_F(Image_test, test_empty)
    {
        using namespace watermark;

        cv::Mat empty_mat{
            true,
            cv::Size{0, 0}};

        EXPECT_CALL(*watermark::mock::g_imread_mock, imread(_, _))
            .Times(1)
            .WillOnce(Return(empty_mat));

        ASSERT_THROW({ Image img{""}; }, Image_exception);
    }

    TEST_F(Image_test, test_non_empty)
    {
        using namespace watermark;

        cv::Mat non_empty_mat{
            false,
            cv::Size{10, 10}};

        EXPECT_CALL(*watermark::mock::g_imread_mock, imread(_, _))
            .Times(1)
            .WillOnce(Return(non_empty_mat));

        ASSERT_NO_THROW({ Image img{""}; });
    }

    int main(int argc, char **argv)
    {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}
