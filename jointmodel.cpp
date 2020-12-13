#include "jointmodel.h"

JointModel::JointModel(QObject *parent) : QObject(parent)
{
    currentPosition.resize(IDN);
    if (! sm.begin(1000000, "/dev/ttyUSB0")) {
        qDebug() << "/dev/ttyUSB0 connect error" << endl;
    }
    feedBackThread = new FeedBackThread(&sm);
    connect(feedBackThread, &FeedBackThread::positionReceived, this, &JointModel::currentReceived);
    feedBackThread->start();
    writePosThread = new WritePosThread(&sm, &currentPosition);
    writePosThread->start();
}

void JointModel::currentReceived(int id, int cur) {
    if (id >= 0 && id < IDN) {
        currentPosition[id] = cur;
        emit sendOrigin(id, cur);
        if (id == 2) {
            emit sendCurrent(id, (currentPosition[1] + currentPosition[2] - BiasPos
                    [2]) / SMSPOSTRANS);
        } else {
            emit sendCurrent(id, (currentPosition[id] - BiasPos[id]) / SMSPOSTRANS / Dirction[id]);
        }
    }
}

void JointModel::beginJog(int id, double target) {
    if (id >= 0 && id < IDN) {
//        double target =
        int targetInt = target * (id != 2 ? Dirction[id] : 1) * SMSPOSTRANS + BiasPos[id];
        if (id == 2) {
            targetInt -= currentPosition[1];
        }
        writePosThread->setTargetPosition(id, targetInt);
        writePosThread->setJogging(id, true);
    }
}

void JointModel::endJog(int id) {
    if (id >= 0 && id < IDN) {
        writePosThread->setJogging(id, false);
    }
}

void JointModel::startMoveHome() {
    for (int i = 0; i < IDN; i++) {
        writePosThread->setTargetPosition(i, 2048);
        writePosThread->setJogging(i, true);
    }
}

void JointModel::endMoveHome() {
    for (int i = 0; i < IDN; i++) {
        writePosThread->setJogging(i, false);
    }
}
