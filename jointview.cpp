#include "jointview.h"
#include "ui_jointview.h"

JointView::JointView(int _id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JointView)
{
    ui->setupUi(this);
    setLabelText("Joint " + QString::number(_id + 1));
    id = _id;
    connect(ui->jogButton, &QPushButton::pressed, this, &JointView::buttonPressed);
    connect(ui->jogButton, &QPushButton::clicked, this, &JointView::buttonReleased);
}

void JointView::setLabelText(const QString &str) {
    ui->jointNameLabel->setText(str);
}

void JointView::setCurrentValue(double value) {
    ui->currentValue->setValue(value);
}

void JointView::setOriginValue(int value) {
    ui->originValue->setValue(value);
}

double JointView::getTargetValue() {
    return ui->targetValue->value();
}

JointView::~JointView()
{
    delete ui;
}

void JointView::buttonPressed() {
    qDebug() << "Button pressed";
    emit beginJog(id, getTargetValue());
}

void JointView::buttonReleased() {
    qDebug() << "Button released";
    emit endJog(id);
}
