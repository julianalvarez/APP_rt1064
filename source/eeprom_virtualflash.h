/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EEPROM_VIRTUAL_FLASH_H
#define __EEPROM_VIRTUAL_FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "types.h"
#include <cr_section_macros.h>

/* Defines -------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
__RAMFUNC(RAM2) void            Init_VIRTUAL_EEPROM (void);
__RAMFUNC(RAM2) void            Read_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size);
__RAMFUNC(RAM2) void            Write_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size);
__RAMFUNC(RAM2) void            Erase_VIRTUAL_EEPROM (uint32_t Address, uint32_t Size);
__RAMFUNC(RAM2) void            Close_VIRTUAL_EEPROM (void);

#endif /* __EEPROM_VIRTUAL_FLASH_H */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
