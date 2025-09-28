#include "iq32_board.h"
int Number=0;
void Show_MUX_All(void)
{ 
  ssd1306_Fill(Black);  
 

    LineSensor_ReadCalibrated();
    if (Read_SW2()) { 
        Number+=1;
        if(Number>15)Number=15;
    }
    if (Read_SW1()) { 
        Number-=1;
        if(Number==0)Number=0;
    }
     
  
    OLED_ShowSInt("Sensor ->", Number, 0 , 2);
    OLED_ShowInt(lineSensor.sensorValues[Number],70,2);

    HAL_Delay(20);
    ssd1306_UpdateScreen();
}

int main(void)
{
    IQ32_Init();
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    uint16_t minValues[16] = {
        300, 300, 300, 300, 300, 300, 300, 300,
        300, 300, 300, 300, 300, 300, 300, 300
    };
    
    uint16_t maxValues[16] = {
        3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
        3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000
    };
    
    LineSensor_SetMinMax(minValues, maxValues);
    

    // ตั้งค่า threshold สำหรับการตรวจจับเส้น
    lineSensor.threshold = 250;
    Wait_SW1(); // รอ SW1 กดครั้งแรก

    while (1) {
       // Show_MUX_All();

      LineSensor_ReadCalibrated();

        OLED_ShowMuxGraph(lineSensor.sensorValues,600,LineSensor_ReadPosition());
        HAL_Delay(5);
    }
}
