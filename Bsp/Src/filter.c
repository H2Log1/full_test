#include "filter.h"
#include "arm_math.h"

float moveAverageFilter_Update(MoveAverageFilter *filter, float newValue)
{
    if (filter->curNum < moveAverage_N)
    {

        filter->value_buf[filter->curNum] = newValue;
        filter->sum += newValue;
        filter->curNum++;
        return filter->sum / filter->curNum;
    }

    else
    {
        filter->sum -= filter->value_buf[0];
        for (int i = 0; i < moveAverage_N - 1; i++)
        {
            filter->value_buf[i] =
                filter->value_buf[i + 1];
        }
        filter->value_buf[moveAverage_N - 1] = newValue;
        filter->sum += newValue;
        return filter->sum / moveAverage_N;
    }
}
