#ifndef FEEDBACKTHREAD_H
#define FEEDBACKTHREAD_H

#include <QObject>
#include <QThread>
#include "SCServo/SCServo.h"
#include <iostream>
#include "Motor_parameter.h"

class FeedBackThread : public QThread
{
    Q_OBJECT
public:
    FeedBackThread(SMSBL *_sm);
    ~FeedBackThread();

protected:
    void run();

signals:
//    void isDone();  //处理完成信号
    void positionReceived(int id, int cur);

public slots:

private:
    SMSBL *sm;
};

#endif // FEEDBACKTHREAD_H
