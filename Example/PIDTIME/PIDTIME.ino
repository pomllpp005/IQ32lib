#include "iq32_board.h"

#define NUM_SENSORS 16
#define SENSOR_CENTER ((NUM_SENSORS-1)*1000/2)

int main(void) {
    // ---------------------------
    // 1. เริ่มต้นบอร์ด
    // ---------------------------
    IQ32_Init();

    // ---------------------------
    // 2. กำหนดค่า sensor max/min
    // ---------------------------
    // วิธีที่ 1: Auto Calibration
    // LineSensor_Calibrate(10000);    // Calibrate 10 วินาที

    // วิธีที่ 2: ตั้งค่า min/max แบบกำหนดเอง
    
    uint16_t minValues[NUM_SENSORS] = {
        300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300
    };
    
    uint16_t maxValues[NUM_SENSORS] = {
        3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500,
        3500, 3500, 3500, 3500, 3500, 3500, 3500, 3500
    };
    
    LineSensor_SetMinMax(minValues, maxValues);
    

    // ตั้งค่า threshold สำหรับการตรวจจับเส้น
    lineSensor.threshold = 500;

    // ---------------------------
    // 3. ตั้งค่า PID และพัดลม
    // ---------------------------
    int16_t baseSpeed = 120;        // ความเร็วพื้นฐาน
    int16_t maxSpeed  = 220;        // ความเร็วสูงสุด
    int16_t Turn  = 800;  
    float kp = 0.06f;               // ค่า P
    float kd = 0.6f;                // ค่า D
    uint32_t runTimeMs = 15000;     // วิ่งตามเส้น 15 วินาที
    Wait_SW1();
    // ---------------------------
    // 4. รัน PID time
    // ---------------------------
 
    iq32_PIDtime(baseSpeed, maxSpeed,Turn, kp, kd, runTimeMs);

    // ---------------------------
    // 5. หลังจบ PID ปิดมอเตอร์และพัดลม
    // ---------------------------
    Motor1(0);
    Motor2(0);
    Fan_SetSpeed(0);

    while(1) {
        // รอ user หรือทำอย่างอื่น
    }

    return 0;
}