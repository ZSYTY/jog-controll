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
<<<<<<< HEAD
        if (id == 2 || id == 1) {
            emit sendCurrent(2, (currentPosition[1] + currentPosition[2] - BiasPos[2]) / SMSPOSTRANS);
            emit sendCurrent(1, (currentPosition[2] - BiasPos[2]) / SMSPOSTRANS / Dirction[2]);
=======
        if (id == 2) {
            emit sendCurrent(id, (currentPosition[1] + currentPosition[2] - BiasPos
                    [2]) / SMSPOSTRANS);
>>>>>>> e2d829c5872bd609dd2c53b4d02fa86bf37e276b
        } else {
            emit sendCurrent(id, (currentPosition[id] - BiasPos[id]) / SMSPOSTRANS / Dirction[id]);
        }
    }
}

void JointModel::beginJog(int id, double target) {
    if (id >= 0 && id < IDN) {
//        double target =
<<<<<<< HEAD
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
=======
        int targetInt = target * (id != 2 ? Dirction[id] : 1) * SMSPOSTRANS + BiasPos[id];
        if (id == 2) {
            targetInt -= currentPosition[1];
        }
        writePosThread->setTargetPosition(id, targetInt);
        writePosThread->setJogging(id, true);
>>>>>>> e2d829c5872bd609dd2c53b4d02fa86bf37e276b
    }
}

void JointModel::endJog(int id) {
<<<<<<< HEAD
    if (id > 0 && id < IDN) {
        if (id == 1) {
            writePosThread->setJogging(1, false);
            writePosThread->setJogging(2, false);
        } else if (id == 2) {
            writePosThread->setJogging(1, false);
        } else {
            writePosThread->setJogging(id, false);
        }
=======
    if (id >= 0 && id < IDN) {
        writePosThread->setJogging(id, false);
>>>>>>> e2d829c5872bd609dd2c53b4d02fa86bf37e276b
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
