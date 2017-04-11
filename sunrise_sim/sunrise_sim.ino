/*
 * Sunrise by Gary Grossi
 * 
 */

#include <avr/pgmspace.h>

#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO

/* Hex color values for each set of LEDs */
PROGMEM const unsigned long sunrise_1[10]={
  0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a,0x0a0a0a
};

PROGMEM const unsigned long sunrise_2[10]={
  0x141414,0x141414,0x141414,0x141414,0x141414,0x141414,0x141414,0x141414,0x141414,0x141414
};

PROGMEM const unsigned long sunrise_3[10]={
  0x282828,0x282828,0x282828,0x282828,0x282828,0x282828,0x282828,0x282828,0x282828,0x282828
};

PROGMEM const unsigned long sunrise_4[10]={
  0x505050,0x505050,0x505050,0x505050,0x505050,0x505050,0x505050,0x505050,0x505050,0x505050
};

PROGMEM const unsigned long sunrise_5[10]={
  0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0,0xa0a0a0
};

PROGMEM const unsigned long sunlight_bright[10]={
  0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff
};

/* Init */
void setup() {                
  STRIP_PINOUT;        // set output pin
  reset_strip();
}



/* Main Program */
void loop() 
{
  send_pattern(sunrise_1, 70);
  delay(1000);
  send_pattern(sunrise_2, 70);  
  delay(1000);
  send_pattern(sunrise_3, 0);
  delay(1000);
  send_pattern(sunrise_4, 70);  
  delay(1000);
  while(1){
    send_pattern(sunlight_bright, 70);  
  }
}


/*******************************************************************************
 * Function Name  : send_1M_pattern
 * Description    : Transmit pattern to whole 1 meter strip
 *                  
 * Input          : pointer to ROM pattern; pattern length; frame rate
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate)
{
  int i=0;
  int j=0;
  uint32_t temp_data;

  for (i=0;i<pattern_no;i++)
  {
    noInterrupts();
    for (j=0;j<10;j++)
    {
      temp_data=pgm_read_dword_near(&data[i][j]);
      send_strip(temp_data);
    }
    interrupts();

    delay(frame_rate);
  }
}

void send_pattern(const unsigned long data[10], int frame_rate){
  int i=0;
  uint32_t temp_data;

  noInterrupts();
  for (i=0;i<10;i++) {
    temp_data=pgm_read_dword_near(&data[i]);
    send_strip(temp_data);
  }
  interrupts();

  delay(frame_rate);
}


/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
  int i;
  unsigned long j=0x800000;
  
 
  for (i=0;i<24;i++)
  {
    if (data & j)
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      
/*----------------------------*/
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");  
      __asm__("nop\n\t");  
      __asm__("nop\n\t");        
/*----------------------------*/      
      DATA_0;
    }
    else
    {
      DATA_1;
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");    
      DATA_0;
/*----------------------------*/      
       __asm__("nop\n\t");
      __asm__("nop\n\t");
      __asm__("nop\n\t");      
/*----------------------------*/         
    }

    j>>=1;
  }


  
}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
  DATA_0;
  delayMicroseconds(20);
}
