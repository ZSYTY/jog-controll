#ifndef JOINTMODEL_H
#define JOINTMODEL_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <iostream>
#include "SCServo/SCServo.h"
#include "feedbackthread.h"

int RegWritePos_main(SMSBL &sm);
int FeedBack_main(SMSBL &sm);

class JointModel : public QObject
{
    Q_OBJECT
public:
    explicit JointModel(QObject *parent = nullptr);

private:
    SMSBL sm;
    FeedBackThread *feedBackThread;
    QVector<int> currentPosition;

signals:
    void sendCurrent(int id, int cur);

private slots:
    void currentReceived(int id, int cur);

};

#endif // JOINTMODEL_H
