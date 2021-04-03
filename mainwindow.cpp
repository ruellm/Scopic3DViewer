#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // checked by default
    ui->actionPan->setChecked(true);

    /** Set callback when item is clicked */
    ui->widget->setItemCallback([&](bool flag, std::string id)
    {
        std::string message = flag ? id + " is selected"
            : "Nothing is selected";

        ui->statusbar->showMessage(QString::fromStdString(message));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionZoom_triggered()
{
    ui->actionPan->setChecked(false);
    ui->actionZoom->setChecked(true);
    ui->actionRotate->setChecked(false);
    ui->actionFree->setChecked(false);
    ui->widget->setCameraMode(GLWidget::CameraMode::Zoom);
}

void MainWindow::on_actionRotate_triggered()
{
    ui->actionPan->setChecked(false);
    ui->actionZoom->setChecked(false);
    ui->actionRotate->setChecked(true);
    ui->actionFree->setChecked(false);
    ui->widget->setCameraMode(GLWidget::CameraMode::Rotate);
}

void MainWindow::on_actionPan_triggered()
{
    ui->actionPan->setChecked(true);
    ui->actionZoom->setChecked(false);
    ui->actionRotate->setChecked(false);
    ui->actionFree->setChecked(false);
    ui->widget->setCameraMode(GLWidget::CameraMode::Pan);
}

void MainWindow::on_actionGrid_toggled(bool arg1)
{
   ui->widget->toggleGrid(arg1);
}

void MainWindow::on_actionAxis_triggered(bool checked)
{
    ui->widget->toggleAxis(checked);
}

void MainWindow::on_actionCube_triggered()
{
    ui->widget->addCube();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        // ... Perform delete rerouted to widget->scenemanager using selected scene id
    }
}
