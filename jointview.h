#ifndef JOINTVIEW_H
#define JOINTVIEW_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class JointView;
}

class JointView : public QWidget
{
    Q_OBJECT

public:
    explicit JointView(int _id, QWidget *parent = nullptr);
    ~JointView();
    void setLabelText(const QString &str);
    void setCurrentValue(double value);
    void setOriginValue(int value);
    double getTargetValue();

private:
    Ui::JointView *ui;
    int id;

signals:
    void beginJog(int id, double target);
    void endJog(int id);

private slots:
    void buttonPressed();
    void buttonReleased();

};

#endif // JOINTVIEW_H
