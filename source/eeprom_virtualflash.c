/* Include ********************************************************************/
#include "eeprom_virtualflash.h"
#include "eeprom_virtual.h"

/* Defines ********************************************************************/
#define VIRTUAL_EEPROM_NUMBER_OF_VARIABLES          512

/* Typedefs *******************************************************************/
/* Globals ********************************************************************/

/* Statics ********************************************************************/

/* Prototypes *****************************************************************/

/* Functions ******************************************************************/

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
void Init_VIRTUAL_EEPROM (void)
{
    EE_Init(VIRTUAL_EEPROM_NUMBER_OF_VARIABLES);
    return;     
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
void Read_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    uint16_t Data16;
    uint32_t  i;
    
    Data16 = 0xFFFF;
    
    /* Check if fit */
    for (i = 0; i < Size; i++){
        EE_ReadVariable((uint16_t)Address + i, &Data16);
        *pData = (uint8_t) Data16;
        pData++;
    }
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          Size <= 256 Bytes.
*******************************************************************************/
void Write_VIRTUAL_EEPROM (uint32_t Address, uint8_t* pData, uint32_t Size)
{
    uint16_t Data16;
    uint32_t i;

    /* Check if fit */
    for (i = 0; i < Size; i++){
        Data16 = (uint16_t) *pData;
        EE_WriteVariable((uint16_t)Address + i, Data16);
        pData++;
    }
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          Size multiple of SFLASH_SECTOR_SIZE
*******************************************************************************/
void Erase_VIRTUAL_EEPROM (uint32_t Address, uint32_t Size)
{
    return;
}

/*******************************************************************************
*    Function Name:  .
*    Parameters:     .
*    Return Value:   .
*
*    Description:    .
*
*    Notes:          .
*******************************************************************************/
void Close_VIRTUAL_EEPROM (void)
{
    return;
}

/* End of $Workfile: EEPROM_S25FL128S.c$ */

