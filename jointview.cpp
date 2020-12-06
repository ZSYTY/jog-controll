#include "jointview.h"
#include "ui_jointview.h"

JointView::JointView(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JointView)
{
    ui->setupUi(this);
    setLabelText("Joint " + QString::number(id));
}

void JointView::setLabelText(const QString &str) {
    ui->jointNameLabel->setText(str);
}

void JointView::setCurrentValue(int value) {
    ui->currentValue->setValue(value);
}

JointView::~JointView()
{
    delete ui;
}
