#ifndef FILTER_H__
#define FILTER_H__

#include "main.h"

#define moveAverage_N 16
typedef struct MoveAverageFilter
{
    float value_buf[moveAverage_N];
    float sum;
    uint8_t curNum;
} MoveAverageFilter;

float moveAverageFilter_Update(MoveAverageFilter *filter, float newValue);

#endif
