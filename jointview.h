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
    explicit JointView(QWidget *parent = nullptr);
    ~JointView();

private:
    Ui::JointView *ui;
};

#endif // JOINTVIEW_H
