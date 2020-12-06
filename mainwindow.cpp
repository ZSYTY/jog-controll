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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::currentReceived(int id, int cur) {
    jointViewList[id]->setCurrentValue(cur);
}

