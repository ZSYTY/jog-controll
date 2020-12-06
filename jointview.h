#ifndef JOINTVIEW_H
#define JOINTVIEW_H

#include <QWidget>

namespace Ui {
class JointView;
}

class JointView : public QWidget
{
    Q_OBJECT

public:
    explicit JointView(int id, QWidget *parent = nullptr);
    ~JointView();
    void setLabelText(const QString &str);
    void setCurrentValue(int value);

private:
    Ui::JointView *ui;

};

#endif // JOINTVIEW_H
