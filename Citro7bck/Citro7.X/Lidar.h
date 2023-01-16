
#ifndef __LIDAR_H
#define __LIDAR_H

#ifdef ENABLE_LIDAR

void Lidar_Loop(void);

u8 Moteur_Lidar_Func (void);

u8 Lidar_Start_Func(void);
u8 Lidar_Stop_Func(void);
u8 Lidar_Reboot_Func(void);


#endif
#endif
