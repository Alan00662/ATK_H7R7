#ifndef __BSPQSPIBOOT_H__
#define __BSPQSPIBOOT_H__

#include "string.h"
#include "main.h"
#define FLASH_MEM_ADDR       0x90000000


typedef enum
{
  BQB_Cmd_ReadID = 0x9F,
  BQB_Cmd_ReadStatus1 = 0x05,
  BQB_Cmd_WriteEnable = 0x06,
  BQB_Cmd_SectorErase = 0x20,
  BQB_Cmd_ChipErase = 0xC7,
  BQB_Cmd_PageProgram_Quad = 0x32,
  BQB_Cmd_FastRead_Quad = 0xEB,
}BQB_Cmd_E;


void Boot_JumpToApp(void);

#endif /**/
