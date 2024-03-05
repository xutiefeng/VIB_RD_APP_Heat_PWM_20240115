/* 
 * File:   bsp_Led.h
 * Author: lix
 *
 * Created on 2022?11?15?, ??8:23
 */

#ifndef BSP_LED_H
#define	BSP_LED_H

#include "globe.h"

#ifdef	__cplusplus
extern "C" {
#endif

	
void LED_Process(void);
void LED_ForceOutput(u8 v);
void FactoryErrowDisplay(u8 v);
#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

