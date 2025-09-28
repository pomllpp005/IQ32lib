#ifndef __IQ32_READLINE_H
#define __IQ32_READLINE_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_SENSORS 16
#define ADC_BITS 12 // ความละเอียด ADC 12 บิต

#define DEFAULT_CALIB_TIME 3000
#define CONSTRAIN(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))

typedef enum {
    IQ32_OK = 0,
    IQ32_ERROR,
    IQ32_INVALID_PARAM
} IQ32_Result_t;

typedef struct {
    uint16_t rawValues[MAX_SENSORS];
    uint16_t sensorValues[MAX_SENSORS];
    uint16_t calibratedMin[MAX_SENSORS];
    uint16_t calibratedMax[MAX_SENSORS];
    uint16_t threshold;
    uint16_t position;
    bool isOnLine;
    bool isCalibrated;
} LineSensor_t;

extern LineSensor_t lineSensor;

// Function prototypes
IQ32_Result_t LineSensor_SetMinMax(uint16_t minValues[MAX_SENSORS], uint16_t maxValues[MAX_SENSORS]);
IQ32_Result_t LineSensor_ReadRaw(void);
IQ32_Result_t LineSensor_Calibrate(uint32_t calibrationTime);
void LineSensor_ReadCalibrated(void);
uint16_t LineSensor_ReadPosition(void);
bool LineSensor_IsOnLine(void);

#endif
