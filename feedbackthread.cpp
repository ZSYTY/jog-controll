#include "feedbackthread.h"

FeedBackThread::FeedBackThread(SMSBL *_sm)
{
    sm = _sm;
}

FeedBackThread::~FeedBackThread()
{

}

void FeedBackThread::run()
{
    while(1){
        int Pos;
        int Speed;
        int Load;
        int Voltage;
        int Temper;
        int Move;
        int Current;
        for (int i = 0; i < IDN; i++) {
            if(sm->FeedBack(i)!=-1){
                Pos = sm->ReadPos(-1);
                Speed = sm->ReadSpeed(-1);
                Load = sm->ReadLoad(-1);
                Voltage = sm->ReadVoltage(-1);
                Temper = sm->ReadTemper(-1);
                Move = sm->ReadMove(-1);
                Current = sm->ReadCurrent(-1);
                std::cout<< "pos ="<<Pos<<std::endl;
                std::cout<< "Speed ="<<Speed<<std::endl;
                std::cout<< "Load ="<<Load<<std::endl;
                std::cout<< "Voltage ="<<Voltage<<std::endl;
                std::cout<< "Temper ="<<Temper<<std::endl;
                std::cout<< "Move ="<<Move<<std::endl;
                std::cout<< "Current ="<<Current<<std::endl;
                emit positionReceived(i, Pos);
                usleep(10*1000);
            }else{
                std::cout<< "read err ="<<i<<std::endl;
                usleep(10*1000);
            }
        }
    }
}
