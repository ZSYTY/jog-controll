#ifndef JOINTMODEL_H
#define JOINTMODEL_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QFile>
#include <iostream>
#include "SCServo/SCServo.h"
#include "feedbackthread.h"
#include "writeposthread.h"

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
    WritePosThread *writePosThread;
    QVector<int> currentPosition;

signals:
    void sendCurrent(int id, double cur);
    void sendOrigin(int id, int cur);

private slots:
    void currentReceived(int id, int cur);

public slots:
    void beginJog(int id, double target);
    void endJog(int id);
    void startMoveHome();
    void endMoveHome();
    void openCsv(QString filename);
};

#endif // JOINTMODEL_H
