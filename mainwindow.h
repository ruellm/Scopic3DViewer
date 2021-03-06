#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionZoom_triggered();

    void on_actionRotate_triggered();

    void on_actionPan_triggered();

    void on_actionGrid_toggled(bool arg1);

    void on_actionAxis_triggered(bool checked);

    void on_actionCube_triggered();

    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};
