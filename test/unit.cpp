#include "../main/business.h"
#include "gtest/gtest.h"

TEST(Time, computeRemainingSleepTime)
{
    Timedelta t = computeRemainingSleepTime(Moment(9,0,0));

    EXPECT_EQ(t.hours, 24);
    EXPECT_EQ(t.minutes, 0);
    EXPECT_EQ(t.seconds, 0);


    t = computeRemainingSleepTime(Moment(1,0,0));

    EXPECT_EQ(t.hours, 8);
    EXPECT_EQ(t.minutes, 0);
    EXPECT_EQ(t.seconds, 0);

    t = computeRemainingSleepTime(Moment(1,0,1));

    EXPECT_EQ(t.hours, 7);
    EXPECT_EQ(t.minutes, 59);
    EXPECT_EQ(t.seconds, 0);

    t = computeRemainingSleepTime(Moment(1,1,0));

    EXPECT_EQ(t.hours, 7);
    EXPECT_EQ(t.minutes, 59);
    EXPECT_EQ(t.seconds, 0);

    t = computeRemainingSleepTime(Moment(1,1,1));

    EXPECT_EQ(t.hours, 7);
    EXPECT_EQ(t.minutes, 58);
    EXPECT_EQ(t.seconds, 0);
}

TEST(Time, formatTimedeltaForDisplay)
{
    EXPECT_EQ(formatTimedeltaForDisplay(Timedelta(8,0,0)), 800);
    EXPECT_EQ(formatTimedeltaForDisplay(Timedelta(9,0,0)), 900);
}
