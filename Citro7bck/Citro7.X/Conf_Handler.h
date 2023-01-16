
#ifndef __CONF_HANDLER_H__
#define __CONF_HANDLER_H__


#define CONF_CARD_COM
//#define CONF_CARD_MOT
//#define CONF_CARD_STEP

#ifdef CONF_CARD_COM
#define ENABLE_COM_UART
#define I2C_MASTER
#define ENABLE_LIDAR
#define ENABLE_UART_LIDAR
//#define CAM_HANDLER
#define MOTOR_MASTER
#define SERVO_MASTER

#define FLASH_HANDLER

#endif


#ifdef CONF_CARD_MOT
#define MOTOR_HANDLER
#define SERVO_HANDLER
#define I2C_SLAVE
//#define I2C_SLAVE_ADRR 0x30
#define I2C_SLAVE_ADRR 0x31
#endif




#endif