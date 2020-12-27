#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include "jointview.h"
#include "Motor_parameter.h"
#include "jointmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector<JointView*> jointViewList;
    JointModel *jointModel;
    QPushButton *moveHomeButton;

private slots:
    void currentReceived(int id, double cur);
    void originReceived(int id, int cur);


};
#endif // MAINWINDOW_H
