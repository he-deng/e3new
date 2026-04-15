#ifndef _AT32_HW_H
#define _AT32_HW_H

#include "at32f435_437.h"
#include "esc.h"  
#include "ecat_def.h"
#include "at32f435_437_wk_config.h"
#include "wk_exint.h"
#include "wk_spi.h"
#include "wk_tmr.h"
#include "wk_gpio.h"
#include "wk_system.h"

typedef union
{
    unsigned short    Word;
    unsigned char     Byte[2];
} UBYTETOWORD;

typedef union 
{
    UINT8             Byte[2];
    UINT16            Word;
} UALEVENT; 

#define DISABLE_GLOBAL_INT         __disable_irq();
#define ENABLE_GLOBAL_INT           __enable_irq();

#define DISABLE_AL_EVENT_INT        DISABLE_GLOBAL_INT
#define ENABLE_AL_EVENT_INT         ENABLE_GLOBAL_INT

#define ESC_RD                      0x02
#define ESC_WR                      0x04

#define PDI_IRQ                    EXINT0_IRQn

#define ECAT_TIMER_INC_P_MS         200

#define    DISABLE_ESC_INT()        nvic_irq_disable(PDI_IRQ)

#define    ENABLE_ESC_INT()         nvic_irq_enable(PDI_IRQ, 1, 0)

#define HW_GetTimer()       		TMR7->cval
#define HW_ClearTimer()             ((TMR7->cval)=0);

#define HW_EscReadWord(WordValue, Address)       HW_EscRead((MEM_ADDR*)&(WordValue),(UINT32)Address,2)   /**< \brief 16Bit ESC read access*/
#define HW_EscReadDWord(DWordValue, Address)     HW_EscRead((MEM_ADDR*)&(DWordValue),(UINT32)Address,4)  /**< \brief 32Bit ESC read access*/
#define HW_EscReadByte(ByteValue, Address)       HW_EscRead((MEM_ADDR*)&(ByteValue),(UINT32)Address,1)
#define HW_EscReadMbxMem(pData,Address,Len)      HW_EscRead((MEM_ADDR*)(pData),(UINT32)Address,Len)       /**< \brief The mailbox data is stored in the local uC memory therefore the default read function is used.*/
#define HW_EscReadWordIsr(WordValue, Address)    HW_EscReadIsr((MEM_ADDR*)&WordValue,(UINT32)Address,2) /**< \brief Interrupt specific 16Bit ESC read access*/
#define HW_EscReadDWordIsr(DWordValue, Address)  HW_EscReadIsr((MEM_ADDR*)&DWordValue,(UINT32)Address,4) /**< \brief Interrupt specific 32Bit ESC read access*/
#define HW_EscWriteWord(WordValue, Address)      HW_EscWrite((MEM_ADDR*)&WordValue,(UINT32)Address,2) 
#define HW_EscWriteDWord(DWordValue, Address)    HW_EscWrite((MEM_ADDR*)&DWordValue,(UINT32)Address,4) 
#define HW_EscWriteByte(ByteValue, Address)      HW_EscWrite((MEM_ADDR*)&ByteValue,(UINT32)Address,1)   /**< \brief 8Bit ESC write access*/
#define HW_EscWriteMbxMem(pData,Address,Len)     HW_EscWrite((MEM_ADDR*)pData,(UINT32)Address,Len)     /**< \brief The mailbox data is stored in the local uC memory therefore the default write function is used.*/
#define HW_EscWriteWordIsr(WordValue, Address)   HW_EscWriteIsr((MEM_ADDR*)&WordValue,(UINT32)Address,2) /**< \brief Interrupt specific 16Bit ESC write access*/
#define HW_EscWriteDWordIsr(DWordValue, Address) HW_EscWriteIsr((MEM_ADDR*)&DWordValue,(UINT32)Address,4) /**< \brief Interrupt specific 32Bit ESC write access*/


uint8_t CF11XX_HW_Init(void);
void HW_Init(void);
void  AddressingEsc( UINT16 Address, UINT8 Command );
void   HW_Release(void);
uint16_t HW_GetALEventRegister(void);
uint16_t HW_GetALEventRegister_Isr(void);  
void   HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
void   HW_EscRead( MEM_ADDR * pData, UINT16 Address, UINT16 Len );
void   HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );
void   HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

#endif
