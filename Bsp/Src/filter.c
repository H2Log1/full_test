#include "filter.h"
#include "arm_math.h"

// 平滑均值滤波
#define moveAverage_N 16
float value_buf[moveAverage_N];
float sum = 0;
uint8_t curNum = 0;

float moveAverageFilter_Distance(uint32_t newValue)
{
    if (curNum < moveAverage_N)
    {
        value_buf[curNum] = (float)newValue;
        sum += newValue;
        curNum++;
        return sum / curNum;
    }
    else
    {
        sum -= sum / moveAverage_N; // 减去上一次的平均值
        sum += newValue;
        return sum / moveAverage_N;
    }
}
