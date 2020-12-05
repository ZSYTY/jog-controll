#include "jointview.h"
#include "ui_jointview.h"

JointView::JointView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JointView)
{
    ui->setupUi(this);
}

JointView::~JointView()
{
    delete ui;
}
