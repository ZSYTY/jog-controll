#ifndef WRITEPOSTHREAD_H
#define WRITEPOSTHREAD_H

#include <QObject>
#include <QThread>
#include "SCServo/SCServo.h"
#include "Motor_parameter.h"

class WritePosThread : public QThread
{
public:
    WritePosThread(SMSBL *_sm, QVector<int> *_currentPosition);
    void setTargetPosition(int id, int pos);
    int getTargetPosition(int id);
    void setJogging(int id, bool _jogging);
    bool getJogging(int id);
private:
    SMSBL *sm;
    QVector<int> *currentPosition;
    QVector<int> targetPosition;
    bool jogging[IDN];
protected:
    void run();

};

#endif // WRITEPOSTHREAD_H
