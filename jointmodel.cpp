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
}

void JointModel::currentReceived(int id, int cur) {
    if (id >= 0 && id < IDN) {
        currentPosition[id] = cur;
        emit sendCurrent(id, cur);
    }
}
