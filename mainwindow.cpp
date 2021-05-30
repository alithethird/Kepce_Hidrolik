#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainWindow::setPixmaps();
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::makePlot()
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->plot_kepce_kepce_1->addGraph();
    ui->plot_kepce_kepce_1->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot_kepce_kepce_1->xAxis->setLabel("x");
    ui->plot_kepce_kepce_1->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot_kepce_kepce_1->xAxis->setRange(-1, 1);
    ui->plot_kepce_kepce_1->yAxis->setRange(0, 1);
    ui->plot_kepce_kepce_1->replot();

    ui->plot_kepce_kepce_2->addGraph();
    ui->plot_kepce_kepce_2->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->plot_kepce_kepce_2->xAxis->setLabel("x");
    ui->plot_kepce_kepce_2->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->plot_kepce_kepce_2->xAxis->setRange(-1, 1);
    ui->plot_kepce_kepce_2->yAxis->setRange(0, 1);
    ui->plot_kepce_kepce_2->replot();
}

void MainWindow::setPixmaps(){
    //:/new/prefix1/png/boom_serbest_diagram.png
    // kepce serbest diagramı
    QPixmap pix_kepce_1(":/new/prefix1/kepce_serbest_diagram");
    int w_kepce_1 = ui->label_5->width();
    int h_kepce_1 = ui->label_5->height();
    ui->label_5->setPixmap(pix_kepce_1.scaled(w_kepce_1,h_kepce_1,Qt::KeepAspectRatio));

    QPixmap pix_boom_1(":/new/prefix1/png/boom_serbest_diagram.png");
    int w_boom_1 = ui->label_kepce_boom_serbest->width();
    int h_boom_1 = ui->label_kepce_boom_serbest->height();
    ui->label_kepce_boom_serbest->setPixmap(pix_boom_1.scaled(w_boom_1,h_boom_1,Qt::KeepAspectRatio));

    QPixmap pix_boom_eq_1(":/new/prefix1/png/boom_serbest_diagram_eq.png");
    int w_boom_eq_1 = ui->label_kepce_boom_serbest_eq->width();
    int h_boom_eq_1 = ui->label_kepce_boom_serbest_eq->height();
    ui->label_kepce_boom_serbest_eq->setPixmap(pix_boom_eq_1.scaled(w_boom_eq_1,h_boom_eq_1,Qt::KeepAspectRatio));

}
