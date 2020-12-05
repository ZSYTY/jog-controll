#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < JogControll::JOINT_CNT; i++) {
        jointViewList.push_back(new JointView());
    }

    QHBoxLayout *layout = new QHBoxLayout();
    for (auto item : jointViewList) {
        layout->addWidget(item);
    }
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

