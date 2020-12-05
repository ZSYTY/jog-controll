#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include <QHBoxLayout>
#include "jointview.h"
#include "config.h"

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

};
#endif // MAINWINDOW_H
