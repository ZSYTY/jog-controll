#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < IDN; i++) {
        jointViewList.push_back(new JointView(i));
    }

    QHBoxLayout *layout = new QHBoxLayout();
    for (auto item : jointViewList) {
        layout->addWidget(item);
    }
    ui->centralwidget->setLayout(layout);
    jointModel = new JointModel();
    connect(jointModel, &JointModel::sendCurrent, this, &MainWindow::currentReceived);
    connect(jointModel, &JointModel::sendOrigin, this, &MainWindow::originReceived);
    for (int i = 0; i < IDN; i++) {
        connect(jointViewList[i], &JointView::beginJog, jointModel, &JointModel::beginJog);
        connect(jointViewList[i], &JointView::endJog, jointModel, &JointModel::endJog);
    }
    moveHomeButton = new QPushButton("Move home");
    layout->addWidget(moveHomeButton);
    connect(moveHomeButton, &QPushButton::pressed, jointModel, &JointModel::startMoveHome);
    connect(moveHomeButton, &QPushButton::clicked, jointModel, &JointModel::endMoveHome);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentReceived(int id, double cur) {
    jointViewList[id]->setCurrentValue(cur);
}

void MainWindow::originReceived(int id, int cur) {
    jointViewList[id]->setOriginValue(cur);
}

