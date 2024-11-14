/**************************************************************************************************/
/** @file Lin_GeneralTypes.h
 *  @brief Các d?nh nghia chung cho LIN driver theo chu?n AUTOSAR
 *  @details File này ch?a các ki?u d? li?u và d?nh nghia chung du?c s? d?ng trong LIN driver trên STM32F103.
 *  @version 1.0.1
 *  @date 2024-11-1
 *  @author Hoang Long Vu
 **************************************************************************************************/
#ifndef LIN_GENERAL_TYPES_H
#define LIN_GENERAL_TYPES_H

#include "Std_Types.h"

/**************************************************************************************************/
/** @typedef Lin_FramePidType
 *  @brief Ki?u d? li?u cho ID b?o v? h?p l? c?a LIN frame.
 */
typedef uint8_t Lin_FramePidType; /**< @brief Ph?m vi: 0...0xEF */

/** @typedef Lin_FrameCsModelType
 *  @brief Enum ch? d?nh mô hình checksum du?c s? d?ng cho frame LIN.
 */
typedef enum {
    LIN_ENHANCED_CS, /**< @brief Mô hình checksum nâng cao */
    LIN_CLASSIC_CS   /**< @brief Mô hình checksum c? di?n */
} Lin_FrameCsModelType;

/** @typedef Lin_FrameResponseType
 *  @brief Enum ch? d?nh lo?i ph?n h?i c?a frame LIN.
 */
typedef enum {
    LIN_FRAMERESPONSE_TX,    /**< @brief Ph?n h?i du?c t?o t? node này */
    LIN_FRAMERESPONSE_RX,    /**< @brief Ph?n h?i du?c t?o t? node khác và liên quan d?n node này */
    LIN_FRAMERESPONSE_IGNORE /**< @brief Ph?n h?i du?c t?o t? node khác và không liên quan d?n node này */
} Lin_FrameResponseType;

/**************************************************************************************************/
/** @typedef Lin_FrameDlType
 *  @brief Ki?u ch? d?nh d? dài d? li?u c?a frame LIN.
 */
typedef uint8_t Lin_FrameDlType; /**< @brief Ph?m vi: 1...8 */

/**************************************************************************************************/
/** @typedef Lin_StatusType
 *  @brief Enum d?i di?n cho tr?ng thái c?a kênh ho?c frame LIN.
 **************************************************************************************************/
typedef enum {
    LIN_NOT_OK,   /**< @brief L?i phát sinh trong quá trình ho?t d?ng */
    LIN_TX_OK,    /**< @brief Truy?n thành công */
    LIN_RX_OK,    /**< @brief Nh?n ph?n h?i chính xác */
    LIN_TX_BUSY,   /**< @brief Ðang truy?n */
		LIN_TX_HEADER_ERROR,     /**< @brief L?i trong quá trình truy?n header */
    LIN_TX_ERROR,            /**< @brief L?i trong quá trình truy?n ph?n h?i */
    LIN_RX_BUSY,             /**< @brief Ðang nh?n d? li?u */
    LIN_RX_ERROR,            /**< @brief L?i trong quá trình nh?n d? li?u */
    LIN_RX_NO_RESPONSE,      /**< @brief Không nh?n du?c ph?n h?i */
    LIN_OPERATIONAL,         /**< @brief Tr?ng thái ho?t d?ng bình thu?ng */
    LIN_CH_SLEEP             /**< @brief Tr?ng thái sleep c?a kênh */
} Lin_StatusType;

/**
 * @typedef Lin_SlaveErrorType
 * @brief Enum d?i di?n cho các l?i phát sinh trong quá trình nh?n h?i c?a node LIN.
 */
typedef enum {
    LIN_ERR_HEADER,          /**< @brief L?i trong header */
    LIN_ERR_RESP_STOPBIT,    /**< @brief L?i framing trong ph?n h?i */
    LIN_ERR_RESP_CHKSUM,     /**< @brief L?i checksum */
    LIN_ERR_RESP_DATABIT,    /**< @brief L?i gi?m sát bit d? li?u trong ph?n h?i */
    LIN_ERR_NO_RESP,         /**< @brief Không có ph?n h?i */
    LIN_ERR_INC_RESP         /**< @brief Ph?n h?i không hoàn ch?nh */
} Lin_SlaveErrorType;

#endif /* LIN_GENERAL_TYPES_H*/