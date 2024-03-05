/* 
 * File:   bsp_ADCollect.h
 * Author: lix
 *
 * Created on 2023��2��28��, ����7:01
 */

#ifndef BSP_ADCOLLECT_H
#define	BSP_ADCOLLECT_H

#ifdef	__cplusplus
extern "C" {
#endif



void ADColect_Init(void);
void TemperatureCollect(void);
void ADCollectProcess(void);
float GetInputVoltage(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BSP_ADCOLLECT_H */

