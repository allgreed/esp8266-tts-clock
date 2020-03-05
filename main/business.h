#include "conf.h"

// cpt. obvious
const int MINUTES_IN_HOUR = 60;
const int HOURS_IN_DAY = 24;


struct Moment
{
    Moment(int hours, int minutes, int seconds)
    {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    int hours;
    int minutes;
    int seconds;
};


struct Timedelta 
{
    Timedelta(int hours, int minutes, int seconds)
    {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    int hours;
    int minutes;
    int seconds;
};


Timedelta computeRemainingSleepTime(Moment moment)
{
    int dayToHoursReminder = moment.hours >= WAKE_UP_HOUR
        ? HOURS_IN_DAY
        : 0
    ;

    int secondsToMinutesBorrow = moment.seconds == 0
        ? 0 
        : 1
    ;
 
    int minutesDiff = (MINUTES_IN_HOUR - moment.minutes - secondsToMinutesBorrow) % MINUTES_IN_HOUR;

    int minutesToHoursBorrow = minutesDiff == 0
        ? 0 
        : 1
    ;

    int hoursDiff = WAKE_UP_HOUR - moment.hours + dayToHoursReminder - minutesToHoursBorrow;

    return Timedelta(hoursDiff, minutesDiff, 0);
}


// display takes a single 4 digit number, need to shift hours by 2 digits
int formatTimedeltaForDisplay(Timedelta t)
{
    return t.hours * 100 + t.minutes;
}
