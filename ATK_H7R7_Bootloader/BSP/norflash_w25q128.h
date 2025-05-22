/**
 ****************************************************************************************************
 * @file        norflash_w25q128_dual.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2024-05-21
 * @brief       NOR Flash ˫W25Q128��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 * 
 * ʵ��ƽ̨:����ԭ�� H7R7������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __NORFLASH_W25Q128_H
#define __NORFLASH_W25Q128_H

#include "main.h"

/* NOR Flash�豸֧�ֶ��� */
//#define NORFLASH_SUPPORT_MX25UM25645G   /* MX25UM25645G */
#define NORFLASH_SUPPORT_W25Q128_DUAL   /* ˫W25Q128 */

/* NOR Flash������������С���� */
#define NORFLASH_SECTOR_BUFFER_SIZE (0x00002000UL)

/* NOR Flash�ڴ�ӳ�����ַ���� */
#define NORFLASH_MEMORY_MAPPED_BASE (XSPI1_BASE)

/* NOR Flash�豸���Ͷ��� */
typedef enum : uint8_t {
    NORFlash_Unknow = 0,    /* δ֪ */
#ifdef NORFLASH_SUPPORT_MX25UM25645G
    NORFlash_MX25UM25645G,  /* MX25UM25645G */
#endif /* NORFLASH_SUPPORT_MX25UM25645G */
#ifdef NORFLASH_SUPPORT_W25Q128_DUAL
    NORFlash_W25Q128_Dual,  /* ˫W25Q128 */
#endif /* NORFLASH_SUPPORT_W25Q128_DUAL */
    NORFlash_Dummy,
} norflash_type_t;

/* NOR Flash�豸���� */
typedef struct {
    /* NOR Flash�豸���� */
    norflash_type_t type;
    
    /* NOR Flash�豸���� */
    struct {
        uint8_t empty_value;    /* ��������ֵ */
        uint32_t chip_size;     /* ȫƬ��С */
        uint32_t block_size;    /* ���С */
        uint32_t sector_size;   /* ������С */
        uint32_t page_size;     /* ҳ��С */
    } parameter;
    
    /* NOR Flash������������ */
    struct {
        uint8_t (*init)(XSPI_HandleTypeDef *hxspi);                                                             /* ��ʼ�� */
        uint8_t (*deinit)(XSPI_HandleTypeDef *hxspi);                                                           /* ����ʼ�� */
        uint8_t (*erase_chip)(XSPI_HandleTypeDef *hxspi);                                                       /* ȫƬ���� */
        uint8_t (*erase_block)(XSPI_HandleTypeDef *hxspi, uint32_t address);                                    /* ����� */
        uint8_t (*erase_sector)(XSPI_HandleTypeDef *hxspi, uint32_t address);                                   /* �������� */
        uint8_t (*program_page)(XSPI_HandleTypeDef *hxspi, uint32_t address, uint8_t *data, uint32_t length);   /* ҳ��� */
        uint8_t (*read)(XSPI_HandleTypeDef *hxspi, uint32_t address, uint8_t *data, uint32_t length);           /* �� */
        uint8_t (*memory_mapped)(XSPI_HandleTypeDef *hxspi);                                                    /* �ڴ�ӳ�� */
    } ops;
} norflash_t;

/* ����NOR Flash�豸 */
extern const norflash_t norflash_w25q128_dual;

/* �������� */
norflash_type_t norflash_init(void);                                                /* ��ʼ��NOR Flash */
uint8_t norflash_deinit(void);                                                      /* ����ʼ��NOR Flash */
uint8_t norflash_erase_chip(void);                                                  /* ȫƬ����NOR Flash */
uint8_t norflash_erase_block(uint32_t address);                                     /* �����NOR Flash */
uint8_t norflash_erase_sector(uint32_t address);                                    /* ��������NOR Flash */
uint8_t norflash_program_page(uint32_t address, uint8_t *data, uint32_t length);    /* ҳ���NOR Flash */
uint8_t norflash_read(uint32_t address, uint8_t *data, uint32_t length);            /* ��NOR Flash */
uint8_t norflash_memory_mapped(void);                                               /* ����NOR Flash�ڴ�ӳ�� */
uint8_t norflash_get_empty_value(void);                                             /* ��ȡNOR Flash��������ֵ */
uint32_t norflash_get_chip_size(void);                                              /* ��ȡNOR FlashƬ��С */
uint32_t norflash_get_block_size(void);                                             /* ��ȡNOR Flash���С */
uint32_t norflash_get_sector_size(void);                                            /* ��ȡNOR Flash������С */
uint32_t norflash_get_page_size(void);                                              /* ��ȡNOR Flashҳ��С */
uint8_t norflash_write(uint32_t address, uint8_t *data, uint32_t length);           /* дNOR Flash */

/* �������� */
uint8_t norflash_ex_init(void);                                                 /* ��ʼ��NOR Flash */
uint8_t norflash_ex_write(uint32_t address, uint8_t *data, uint32_t length);    /* дNOR Flash */
uint8_t norflash_ex_read(uint32_t address, uint8_t *data, uint32_t length);     /* ��NOR Flash */
uint8_t norflash_ex_erase_sector(uint32_t address);                             /* ��������NOR Flash */

#endif /* __NORFLASH_W25Q128_DUAL_H */
