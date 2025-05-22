/**
 ****************************************************************************************************
 * @file        norflash_w25q128_dual.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2024-05-21
 * @brief       NOR Flash 双W25Q128驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 * 
 * 实验平台:正点原子 H7R7开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 * 
 ****************************************************************************************************
 */

#ifndef __NORFLASH_W25Q128_H
#define __NORFLASH_W25Q128_H

#include "main.h"

/* NOR Flash设备支持定义 */
//#define NORFLASH_SUPPORT_MX25UM25645G   /* MX25UM25645G */
#define NORFLASH_SUPPORT_W25Q128_DUAL   /* 双W25Q128 */

/* NOR Flash扇区缓冲区大小定义 */
#define NORFLASH_SECTOR_BUFFER_SIZE (0x00002000UL)

/* NOR Flash内存映射基地址定义 */
#define NORFLASH_MEMORY_MAPPED_BASE (XSPI1_BASE)

/* NOR Flash设备类型定义 */
typedef enum : uint8_t {
    NORFlash_Unknow = 0,    /* 未知 */
#ifdef NORFLASH_SUPPORT_MX25UM25645G
    NORFlash_MX25UM25645G,  /* MX25UM25645G */
#endif /* NORFLASH_SUPPORT_MX25UM25645G */
#ifdef NORFLASH_SUPPORT_W25Q128_DUAL
    NORFlash_W25Q128_Dual,  /* 双W25Q128 */
#endif /* NORFLASH_SUPPORT_W25Q128_DUAL */
    NORFlash_Dummy,
} norflash_type_t;

/* NOR Flash设备定义 */
typedef struct {
    /* NOR Flash设备类型 */
    norflash_type_t type;
    
    /* NOR Flash设备参数 */
    struct {
        uint8_t empty_value;    /* 擦后数据值 */
        uint32_t chip_size;     /* 全片大小 */
        uint32_t block_size;    /* 块大小 */
        uint32_t sector_size;   /* 扇区大小 */
        uint32_t page_size;     /* 页大小 */
    } parameter;
    
    /* NOR Flash操作函数集合 */
    struct {
        uint8_t (*init)(XSPI_HandleTypeDef *hxspi);                                                             /* 初始化 */
        uint8_t (*deinit)(XSPI_HandleTypeDef *hxspi);                                                           /* 反初始化 */
        uint8_t (*erase_chip)(XSPI_HandleTypeDef *hxspi);                                                       /* 全片擦除 */
        uint8_t (*erase_block)(XSPI_HandleTypeDef *hxspi, uint32_t address);                                    /* 块擦除 */
        uint8_t (*erase_sector)(XSPI_HandleTypeDef *hxspi, uint32_t address);                                   /* 扇区擦除 */
        uint8_t (*program_page)(XSPI_HandleTypeDef *hxspi, uint32_t address, uint8_t *data, uint32_t length);   /* 页编程 */
        uint8_t (*read)(XSPI_HandleTypeDef *hxspi, uint32_t address, uint8_t *data, uint32_t length);           /* 读 */
        uint8_t (*memory_mapped)(XSPI_HandleTypeDef *hxspi);                                                    /* 内存映射 */
    } ops;
} norflash_t;

/* 导出NOR Flash设备 */
extern const norflash_t norflash_w25q128_dual;

/* 函数声明 */
norflash_type_t norflash_init(void);                                                /* 初始化NOR Flash */
uint8_t norflash_deinit(void);                                                      /* 反初始化NOR Flash */
uint8_t norflash_erase_chip(void);                                                  /* 全片擦除NOR Flash */
uint8_t norflash_erase_block(uint32_t address);                                     /* 块擦除NOR Flash */
uint8_t norflash_erase_sector(uint32_t address);                                    /* 扇区擦除NOR Flash */
uint8_t norflash_program_page(uint32_t address, uint8_t *data, uint32_t length);    /* 页编程NOR Flash */
uint8_t norflash_read(uint32_t address, uint8_t *data, uint32_t length);            /* 读NOR Flash */
uint8_t norflash_memory_mapped(void);                                               /* 开启NOR Flash内存映射 */
uint8_t norflash_get_empty_value(void);                                             /* 获取NOR Flash擦后数据值 */
uint32_t norflash_get_chip_size(void);                                              /* 获取NOR Flash片大小 */
uint32_t norflash_get_block_size(void);                                             /* 获取NOR Flash块大小 */
uint32_t norflash_get_sector_size(void);                                            /* 获取NOR Flash扇区大小 */
uint32_t norflash_get_page_size(void);                                              /* 获取NOR Flash页大小 */
uint8_t norflash_write(uint32_t address, uint8_t *data, uint32_t length);           /* 写NOR Flash */

/* 函数声明 */
uint8_t norflash_ex_init(void);                                                 /* 初始化NOR Flash */
uint8_t norflash_ex_write(uint32_t address, uint8_t *data, uint32_t length);    /* 写NOR Flash */
uint8_t norflash_ex_read(uint32_t address, uint8_t *data, uint32_t length);     /* 读NOR Flash */
uint8_t norflash_ex_erase_sector(uint32_t address);                             /* 扇区擦除NOR Flash */

#endif /* __NORFLASH_W25Q128_DUAL_H */
