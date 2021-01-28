#include "writeposthread.h"

WritePosThread::WritePosThread(SMSBL *_sm, QVector<int> *_currentPosition)
{
    sm = _sm;
    currentPosition = _currentPosition;
    targetPosition.resize(IDN);
    for (int i = 0; i < IDN; i++) {
        jogging[i] = false;
    }
}

void WritePosThread::run() {
    usleep(1000*1000);
    bool locked[IDN] = {0};
    while(1) {
        for (int i = 0; i < IDN; i++) {
            if (!jogging[i]) {
                if (! locked[i]) {
                    sm->WritePosEx(i, (*currentPosition)[i], 80, 100);
                    locked[i] = true;
                }
            } else {
                sm->WritePosEx(i, targetPosition[i], 80, 100);
                locked[i] = false;
            }
        }
//        sm->RegWriteAction();
        usleep(40*1000);
    }
}

void WritePosThread::setTargetPosition(int id, int pos) {
    if (id >= 0 && id < IDN) {
        targetPosition[id] = pos;
    }
}

int WritePosThread::getTargetPosition(int id) {
    if (id >= 0 && id < IDN) {
        return targetPosition[id];
    }
}

void WritePosThread::setJogging(int id, bool _jogging) {
    jogging[id] = _jogging;
}

bool WritePosThread::getJogging(int id) {
    return jogging[id];
}
