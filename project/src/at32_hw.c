#include "at32_hw.h"

UALEVENT         EscALEvent; 


uint8_t CF11XX_HW_Init(void)
{
    uint32_t intMask = 0;
    
    do 
    {
        intMask = 0x93;
        HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
        intMask = 0;
        HW_EscReadDWord(intMask, ESC_AL_EVENTMASK_OFFSET);
    } while (intMask != 0x93);

    intMask = 0x00;
    HW_EscWriteDWord(intMask, ESC_AL_EVENTMASK_OFFSET);

    DISABLE_GLOBAL_INT;
    
    //ESC_INT / SYNC0_INT / SYNC1_INT
    wk_exint_config();
    wk_tmr7_init();
    wk_nvic_config();
    
    /* enable all interrupts */
    ENABLE_GLOBAL_INT;

    return 0;
}

uint8_t WR_CMD (uint8_t cmd)  
{ 
    uint8_t temp; 

    /* Wait for SPI1 Tx buffer empty */ 
    while (spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET); 
    /* Send SPI1 data */ 
    spi_i2s_data_transmit(SPI2,cmd); 
    /* Wait for SPI1 data reception */ 
    while (spi_i2s_flag_get(SPI2, SPI_I2S_RDBF_FLAG) == RESET); 
    /* Read SPI1 received data */ 
    temp =  spi_i2s_data_receive(SPI2); 
    return temp;
} 

void CF11xx_SPI_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT8 dummy;

    UINT8 *pTmpData = (UINT8 *)pData;

   
    /* loop for all bytes to be written */
    while ( i-- > 0 )
    {
        DISABLE_GLOBAL_INT;
        AddressingEsc( Address, ESC_WR );

        dummy = WR_CMD(*pTmpData);
        pTmpData++;
        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */
        DESELECT_SPI;
        ENABLE_GLOBAL_INT;

        /* next address */
        Address++;
    }
}


void CF11xx_SPI_EscRead( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* loop for all bytes to be read */
    while ( i-- > 0 )
    {

         DISABLE_GLOBAL_INT;

         AddressingEsc( Address, ESC_RD );
	
         /*Each Byte will be read with a new addressing phase so the out data is 0xFF*/
         *pTmpData = WR_CMD(0xFF);
         
         pTmpData++;
         
        /* there has to be at least 15 ns + CLK/2 after the transmission is finished
           before the SPI1_SEL signal shall be 1 */
        DESELECT_SPI;

        ENABLE_GLOBAL_INT;

        /* next address */
        Address++;
    }
} 

void CF11xx_SPI_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len )
{
    UINT16 i = Len;
    VARVOLATILE UINT16 dummy;
    UINT8 *pTmpData = (UINT8 *)pData;

    /* send the address and command to the ESC */
     AddressingEsc( Address, ESC_WR );
     /* loop for all bytes to be written */
    while ( i-- > 0 )
    {

         dummy = WR_CMD(*pTmpData);
         pTmpData++;
    }
    /* there has to be at least 15 ns + CLK/2 after the transmission is finished
       before the SPI1_SEL signal shall be 1 */
    DESELECT_SPI;
}


void CF11xx_SPI_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
     UINT16 i = Len;
     UINT8 SendData = 0;
     UINT8 *pTmpData = (UINT8 *)pData;
     AddressingEsc( Address, ESC_RD );
     while ( i-- > 0 )
     {
         if(i == 0)
         {
             SendData = 0xff;
         }
         *pTmpData  = WR_CMD(SendData);
         pTmpData++;
     }
     DESELECT_SPI;

}

void HW_Init(void)
{
    wk_system_clock_config();

    wk_timebase_init();

    wk_gpio_config();

    /* init spi2 function. */
    wk_spi2_init();
   

    CF11XX_HW_Init();
}

UINT16 HW_GetALEventRegister(void)
{
    GetInterruptRegister();
    return EscALEvent.Word;
}

UINT16 HW_GetALEventRegister_Isr(void)
{
    ISR_GetInterruptRegister();
    return EscALEvent.Word;
}

void HW_EscWrite(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    CF11xx_SPI_EscWrite(pData, Address, Len);
}

void HW_EscRead(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    CF11xx_SPI_EscRead(pData, Address, Len);
}

void HW_EscWriteIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    CF11xx_SPI_EscWriteIsr(pData, Address, Len);
}

void HW_EscReadIsr(MEM_ADDR *pData, UINT16 Address, UINT16 Len)
{
    CF11xx_SPI_EscReadIsr(pData,Address,Len);
}