/*
以下例子在SMS40BL中测试通过，舵机出厂速度单位为0.732rpm，舵机机运行速度V=80
如果使用的出厂速度单位是0.0146rpm，则速度改为V=4000，延时公式T=[(P1-P0)/V]*1000+[V/(A*100)]*1000
*/

#include "jointmodel.h"
//extern SMSBL sm;

int RegWritePos_main(SMSBL &sm)
{
//	if(argc<2){
//        std::cout<< "argc error!"<<std::endl;
//        return 0;
//	}
//	std::cout<< "serial:"<<argv[1]<<std::endl;
//    if(!sm.begin(115200, argv[1])){
//        std::cout<< "Failed to init smsbl motor!"<<std::endl;
//        return 0;
//    }
	while(1){
		sm.RegWritePosEx(1, 4095, 80, 100);//舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=4095位置
		sm.RegWritePosEx(2, 4095, 80, 100);//舵机(ID2)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=4095位置
		sm.RegWriteAction();
		std::cout<< "pos ="<<4095<<std::endl;
		usleep(1495*1000);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
  
		sm.RegWritePosEx(1, 0, 80, 100);//舵机(ID1)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P0=0位置
		sm.RegWritePosEx(2, 0, 80, 100);//舵机(ID2)以最高速度V=80(50*80步/秒)，加速度A=100(100*100步/秒^2)，运行至P1=0位置
		sm.RegWriteAction();
		std::cout<< "pos ="<<0<<std::endl;
		usleep(1495*1000);//[(P1-P0)/(50*V)]*1000+[(50*V)/(A*100)]*1000
	}
//	sm.end();
	return 1;
}

