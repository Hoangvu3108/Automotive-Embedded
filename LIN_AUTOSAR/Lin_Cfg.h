/**************************************************************************************************/
/** @file Lin_GeneralTypes.h
 *  @brief Các d?nh nghia chung cho LIN driver theo chu?n AUTOSAR
 *  @details File này ch?a các ki?u d? li?u và d?nh nghia chung du?c s? d?ng trong LIN driver trên STM32F103.
 *  @version 1.0.1
 *  @date 2024-11-1
 *  @author Hoang Long Vu
 **************************************************************************************************/
#ifndef LIN_CFG_H
#define LIN_CFG_H

#include "stm32f10x.h"                  // Device header

/**
 * @brief Ð?nh nghia các tr?ng thái c?a kênh LIN.
 */
//#define LIN_CH_SLEEP          0 /**< @brief Tr?ng thái ng? c?a kênh LIN. */
//#define LIN_CH_OPERATIONAL    1 /**< @brief Tr?ng thái ho?t d?ng c?a kênh LIN. */
//#define LIN_CH_SLEEP_PENDING  2 /**< @brief Tr?ng thái dang ch? d? chuy?n vào sleep. */

/**
 * @brief Ð?nh nghia s? lu?ng kênh LIN t?i da.
 * @details Giá tr? này c?n du?c c?u hình d?a trên h? th?ng th?c t?
 * và kh? nang h? tr? c?a vi di?u khi?n.
 */
#define MAX_LIN_CHANNELS 2 /**< Giá tr? này có th? thay d?i tùy thu?c vào s? lu?ng kênh LIN mà h? th?ng h? tr?. */

/**
 * @brief Ð?nh nghia ID nhà cung c?p (Vendor ID).
 */

/**
 * @brief ID nhà cung c?p cho LIN driver.
 */
#define LIN_VENDOR_ID 123 /**< @brief ID nhà cung c?p cho LIN driver. */

/**
 * @brief Ð?nh nghia ID module (Module ID).
 */
#define LIN_MODULE_ID 456 /**< @brief ID module cho LIN driver. */

/**
 * @brief Ð?nh nghia phiên b?n ph?n m?m (Software Version).
 */
#define LIN_SW_MAJOR_VERSION 1 /**< @brief Phiên b?n chính c?a ph?n m?m. */
#define LIN_SW_MINOR_VERSION 0 /**< @brief Phiên b?n ph? c?a ph?n m?m. */
#define LIN_SW_PATCH_VERSION 0 /**< @brief Phiên b?n s?a l?i c?a ph?n m?m. */

/**
 * @enum Lin_StatusType
 * @brief Các tr?ng thái khác nhau c?a kênh LIN.
 */
typedef enum {
    LIN_CH_SLEEP,        /**< @brief Tr?ng thái ng? c?a kênh LIN. */
    LIN_CH_OPERATIONAL,  /**< @brief Tr?ng thái ho?t d?ng c?a kênh LIN. */
    LIN_CH_SLEEP_PENDING /**< @brief Tr?ng thái dang ch? d? chuy?n vào sleep. */
} Lin_StatusType;

/**
 * @struct LinChannelConfigType
 * @brief C?u trúc ch?a thông tin c?u hình cho m?t kênh LIN.
 */
typedef struct {
    uint32_t Lin_Baudrate;                  /**< @brief T?c d? truy?n d? li?u c?a kênh LIN. */
    FunctionalState LinChannelWakeupSupport; /**< @brief H? tr? phát hi?n wake-up (ENABLE/DISABLE). */
    uint16_t Lin_ChannelID;                 /**< @brief ID c?a kênh LIN. */
    GPIO_TypeDef* Lin_Port;                 /**< @brief C?ng GPIO c?a kênh LIN. */
    uint16_t Lin_TxPin;                     /**< @brief Chân Tx c?a kênh LIN. */
    uint16_t Lin_RxPin;                     /**< @brief Chân Rx c?a kênh LIN. */
} LinChannelConfigType;


/**
 * @brief M?ng luu tr? tr?ng thái c?a các kênh LIN.
 */
Lin_StatusType LinChannelState[MAX_LIN_CHANNELS] = {
    LIN_CH_SLEEP, // Kh?i t?o tr?ng thái ban d?u cho m?i kênh
    LIN_CH_SLEEP  // Kh?i t?o cho kênh th? hai n?u c?n
};

/**
 * @brief M?ng luu tr? c?u hình cho các kênh LIN.
 * @details M?i ph?n t? trong m?ng ch?a thông tin c?u hình c?a m?t kênh LIN,
 * bao g?m t?c d? baud, tr?ng thái h? tr? wake-up, và các chân GPIO liên quan.
 */
LinChannelConfigType LinChannelConfig[MAX_LIN_CHANNELS] = {
    {
        .Lin_Baudrate = 19200,                  /**< @brief T?c d? baud cho kênh LIN. */
        .LinChannelWakeupSupport = ENABLE,     /**< @brief H? tr? wake-up. */
        .Lin_ChannelID = 0,                     /**< @brief ID c?a kênh LIN. */
        .Lin_Port = GPIOA,                      /**< @brief C?ng GPIO s? d?ng. */
        .Lin_TxPin = GPIO_Pin_9,                /**< @brief Chân Tx c?a kênh. */
        .Lin_RxPin = GPIO_Pin_10                /**< @brief Chân Rx c?a kênh. */
    }
    // Thêm c?u hình cho các kênh khác n?u c?n
};

#endif /* LIN_CFG_H */
