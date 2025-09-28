#include "iq32_board.h"
int main(void)
{
    IQ32_Init();

    
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();

     Wait_SW1(); // รอ SW1 กดครั้งแรก

ssd1306_UpdateScreen();
    while (1) {
        uint16_t sensorValues[16]={};
        ssd1306_Fill(Black);
       


        for (uint8_t ch = 0; ch < 16; ch++) {
             MUX_SelectChannel(ch);
            sensorValues[ch] = MUX_Read();
        }
        // อ่านค่าช่อง MUX 0–16
        int Num=0;
        for (uint8_t ln = 0; ln < 4; ln++) {

            for (uint8_t ch = 0; ch < 4; ch++) {
              OLED_ShowInt(sensorValues[Num], ch*5 , ln);
              Num+=1;
           }
              // OLED_ShowIntRotated(1, 0 , 0,270);
        }

        HAL_Delay(5);
        //  ssd1306_RotateBuffer(270);
         ssd1306_UpdateScreen();
       
        
    }
}
