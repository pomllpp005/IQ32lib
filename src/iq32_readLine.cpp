#include "iq32_readLine.h"
#include "iq32_Mux.h"  // สำหรับ MUX_SelectChannel และ MUX_Read
#include "Arduino.h"   // สำหรับ map() และ HAL_Delay()

LineSensor_t lineSensor;

IQ32_Result_t LineSensor_SetMinMax(uint16_t minValues[MAX_SENSORS],
                                   uint16_t maxValues[MAX_SENSORS]) {
    for(int i=0;i<MAX_SENSORS;i++){
        lineSensor.calibratedMin[i] = minValues[i];
        lineSensor.calibratedMax[i] = maxValues[i];
    }
    lineSensor.isCalibrated = true;
    return IQ32_OK;
}

IQ32_Result_t LineSensor_ReadRaw(void)
{
    for(int i = 0; i < MAX_SENSORS; i++) {
        MUX_SelectChannel(i);               // เลือกช่อง MUX
        lineSensor.rawValues[i] = MUX_Read(); // อ่านค่า ADC
    }
    return IQ32_OK;
}

IQ32_Result_t LineSensor_Calibrate(uint32_t calibrationTime)
{
    if(calibrationTime == 0) calibrationTime = DEFAULT_CALIB_TIME;

    uint32_t startTime = millis();

    // ค่าเริ่มต้น min/max
    for(int i = 0; i < MAX_SENSORS; i++) {
        lineSensor.calibratedMin[i] = (1 << ADC_BITS) - 1; // 4095
        lineSensor.calibratedMax[i] = 0;
    }

    while((millis() - startTime) < calibrationTime) {
        LineSensor_ReadRaw();

        for(int i = 0; i < MAX_SENSORS; i++) {
            if(lineSensor.rawValues[i] < lineSensor.calibratedMin[i])
                lineSensor.calibratedMin[i] = lineSensor.rawValues[i];
            if(lineSensor.rawValues[i] > lineSensor.calibratedMax[i])
                lineSensor.calibratedMax[i] = lineSensor.rawValues[i];
        }
        delay(10);
    }

    lineSensor.isCalibrated = true;
    return IQ32_OK;
}

void LineSensor_ReadCalibrated(void)
{
    LineSensor_ReadRaw();  // อ่านค่า raw

    for (int i = 0; i < MAX_SENSORS; i++) {
        int value = map(lineSensor.rawValues[i],lineSensor.calibratedMin[i],lineSensor.calibratedMax[i],0, 1000);
        value = CONSTRAIN(value, 0, 1000);
        lineSensor.sensorValues[i] = value;
    }
}

uint16_t LineSensor_ReadPosition(void)
{
    LineSensor_ReadCalibrated();  // อ่านค่า calibrate

    uint32_t sum = 0;
    uint32_t weightedSum = 0;

    for (int i = 0; i < MAX_SENSORS; i++) {
        if (lineSensor.sensorValues[i] >= lineSensor.threshold) {
            sum += lineSensor.sensorValues[i];
            weightedSum += (uint32_t)lineSensor.sensorValues[i] * (i * 1000);
        }
    }

    if (sum > 0) {
        lineSensor.position = weightedSum / sum;
        lineSensor.isOnLine = true;
    } else {
        lineSensor.position = 0;
        lineSensor.isOnLine = false;
    }

    return lineSensor.position;
}

bool LineSensor_IsOnLine(void)
{
    return lineSensor.isOnLine;
}
