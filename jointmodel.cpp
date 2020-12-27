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
        if (id == 2 || id == 1) {
            emit sendCurrent(2, (currentPosition[1] + currentPosition[2] - BiasPos[2]) / SMSPOSTRANS);
            emit sendCurrent(1, (currentPosition[2] - BiasPos[2]) / SMSPOSTRANS / Dirction[2]);
        } else {
            emit sendCurrent(id, (currentPosition[id] - BiasPos[id]) / SMSPOSTRANS / Dirction[id]);
        }
    }
}

void JointModel::beginJog(int id, double target) {
    if (id >= 0 && id < IDN) {
//        int targetInt = target * (id != 2 ? Dirction[id] : 1) * SMSPOSTRANS + BiasPos[id];
        if (id == 2) {
            int targetInt = target * SMSPOSTRANS + BiasPos[2] - currentPosition[2];
            writePosThread->setTargetPosition(1, targetInt);
            writePosThread->setJogging(1, true);
        } else if (id == 1) {
            int targetInt = (target * SMSPOSTRANS * Dirction[2] + BiasPos[2]);
            int delta = targetInt - currentPosition[2];
            writePosThread->setTargetPosition(2, targetInt);
            writePosThread->setTargetPosition(1, currentPosition[1] - delta);
            writePosThread->setJogging(1, true);
            writePosThread->setJogging(2, true);
        } else {
            int targetInt = target * Dirction[id] * SMSPOSTRANS + BiasPos[id];
            writePosThread->setTargetPosition(id, targetInt);
            writePosThread->setJogging(id, true);
        }
    }
}

void JointModel::endJog(int id) {
    if (id > 0 && id < IDN) {
        if (id == 1) {
            writePosThread->setJogging(1, false);
            writePosThread->setJogging(2, false);
        } else if (id == 2) {
            writePosThread->setJogging(1, false);
        } else {
            writePosThread->setJogging(id, false);
        }
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
