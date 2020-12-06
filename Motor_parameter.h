/*
 * motor_parameter.h
 * 舵机基本的限制和转换参数
 * 日期: 2020.8.13
 * 作者: 
 */

#ifndef _CRN_H
#define _CRN_H

#include "SCServo/INST.h"


//位置转换系数：弧度-输入
#define	SMSPOSTRANS 651.8986469
//速度转换系数：弧度/秒-输入
#define	SMSVELTRANS 652.2743569
//加速度转换系数：弧度/秒^2-输入
#define	SMSACCTRANS 6.519032827

const double pi = 3.1415936;
const u8 IDN = 6;
const s8 Dirction[IDN] = {-1, 1, -1, 1, -1, 1};
const s16 BiasPos[IDN] = {0, 5744, 2850, 0, 3359,2048};
const u16 thresholdvel[IDN] = {500, 500, 500, 500, 500, 500};
const s16 ThresholdPosUp[IDN] = {2651, 6244, 3850, 2000, 3420, 4096};
const s16 ThresholdPosDown[IDN] = {-1445, 5244, 1800, -2000, 1250, 0};

#endif
