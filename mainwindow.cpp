#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include "Kaynak.cpp"
#include <QString>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //MainWindow::setPixmaps();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::degerOku()
{
    //QString neodem = "hebele";

    Pc = ui->girdi_Pc->text().toFloat();
    Dc = ui->girdi_Dc->text().toFloat();
    W_kepce = ui->girdi_W_kepce->text().toFloat();
    R1FC = ui->girdi_R1FC->text().toFloat();


    W_kol = ui->girdi_W_kol->text().toFloat();

    W_boom = ui->girdi_W_boom->text().toFloat();

    MainWindow::Hesapla();
    MainWindow::sonucGoster();
    /*
    neodem = QString::number(Pc, 'f', 8);

    ui->label_maxFc->setText(neodem);*/

}
void MainWindow::sonucGoster()
{
    //kepce icin
    QString st_maxFC;
    QString st_F_P1x;
    QString st_F_P1y;

    st_maxFC = QString::number((maxFC), 'f', 3);
    st_F_P1x = QString::number((F_P1x), 'f', 3);
    st_F_P1y = QString::number((F_P1y), 'f', 3);

    ui->label_maxFc->setText(st_maxFC);
    ui->label_F_P1x->setText(st_F_P1x);
    ui->label_F_P1y->setText(st_F_P1y);

    //kol icin
    QString st_Fb;
    QString st_F_P7x;
    QString st_F_P7y;
    QString st_Db;

    st_Fb = QString::number((Fb), 'f', 3);
    st_F_P7x = QString::number((F_P7x), 'f', 3);
    st_F_P7y = QString::number((F_P7y), 'f', 3);
    st_Db = QString::number((Db), 'f', 3);

    ui->label_Fb->setText(st_Fb);
    ui->label_F_P7x->setText(st_F_P7x);
    ui->label_F_P7y->setText(st_F_P7y);
    ui->label_Db->setText(st_Db);

    //boom icin
    QString st_Fa;
    QString st_Da;

    st_Fa = QString::number((Fa), 'f', 3);
    st_Da = QString::number((Da), 'f', 3);

    ui->label_Fa->setText(st_Fa);
    ui->label_Da->setText(st_Da);
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

void MainWindow::on_pushButtonHesapla_clicked()
{

    MainWindow::degerOku();
}
void MainWindow::Hesapla()
{
    //girdilerin çekileceği kısım
    //grafik arayüzü yapılacağı için girdiler eklenmemiştir.
    //arayüzdeki kutulardan çekilir
    // örn. Pc= read.Pc_box();

    Pc = Pc * pow(10, 5) * 1.0; //bar to pascal
    Dc = Dc / 2000;             //çap -> yarıçap;  mm to metre
    F_c();
    for (int f1 = 0; f1 < 190; f1++)
    {
        f1 = f1 * 1.0;
        F12[f1] = F_12(f1);
        F13[f1] = F_13(F12[f1], f1);
    }
    /*for (int l1 = 0; l1 < 131; l1++) {
        l1 *= 1.0;
        for (int m1 = 0; m1 < 103; m1++) {
            m1 = m1 * 1.0;
            for (int f1 = 0; f1 < 190; f1++)
            {
                float FC = abs(F_C(f1, m1, l1));
                if (FC > maxFC) {
                    maxFC = F_C(f1, m1, l1);                          //    17708.1
                    mu = 30.0;//m1 * 1.0;                                    //    102
                    fi = 40.0; // f1 * 1.0;                                    //    48
                    lamda = 60.0; l1 * 1.0;                                 //    111
                }
            }
        }
    }*/
    //FC yi max yapan açıları yazılımla bulmak için kullanılan for döngüsü
    maxFC = F_C( );
    F_Pim1x();
    F_Pim1y();
    F_b();
    F_Pim7x();
    F_Pim7y();
    F_a();
}
float MainWindow::A0(float f_i)
{
    float a0 = 0;
    a0 = 82.308 * exp(0.0035 * f_i);
    return a0;
}
float MainWindow::alfa(float f_i)
{
    float A = 1.0195 * f_i - 0.0022 * pow(f_i, 2) - 55.242;
    return A;
}
float MainWindow::beta(float f_i)
{
    float B = 0.0026 * pow(f_i, 2) - 0.7042 * f_i + 63.953;
    return B;
}
float MainWindow::R1_F12(float f_i)
{
    float R1 = 1.3613 * f_i - 0.0086 * pow(f_i, 2) + 137.84;
    return R1;
}
float MainWindow::R1_Wk()
{
    float RW = 439 * cos((97.64 - fi - mu - lamda)*M_PI*2/360);
    return RW;
}
float MainWindow::F_c()
{
    Fc = Pc * pow(Dc,2)*M_PI;
    return Fc;
}
float MainWindow::F_12(float f_i)
{
    float F12 = Fc * cos(alfa(f_i) * M_PI * 2 / 360) / cos(beta(f_i) * M_PI * 2 / 360);
    return F12;
}
float MainWindow::F_13(float F12, float f_i)
{
    float F13 = Fc * sin(alfa(f_i) * M_PI * 2 / 360) + F12*sin(beta(f_i)  * M_PI * 2 / 360);
    return F13;
}
float MainWindow::F_C()
{
    maxFC = (F_12(fi) * R1_F12(fi) + W_kepce * R1_Wk()) / R1FC;
    return maxFC;
}
float MainWindow::F_Pim1x()
{
    float A = A0(fi) + lamda + mu;
    float B = 58.32 - lamda - mu - fi;
    F_P1x = F_12(fi) * sin(A * M_PI * 2 / 360)
              - maxFC * sin(B * M_PI * 2 / 360);
    return F_P1x;
}
float MainWindow::F_Pim1y()
{
    float A = A0(fi) + lamda + mu;
    float B = 58.32 - lamda - mu - fi;
    F_P1y = F_12(fi) * cos(A * M_PI * 2 / 360)
              + maxFC * cos(B * M_PI * 2 / 360)-W_kepce;
    return F_P1y;
}
float MainWindow::F_b()
{
    float R7_Fbx = 361.7 * sin((11.3 + mu + lamda)*2*M_PI/360);
    float R7_Fby = 361.7 * cos((11.3 + mu + lamda) * 2 * M_PI / 360);
    float R7_Wkol = 550 * cos((27.73 - mu - lamda) * 2 * M_PI / 360);
    float R7_Wkepce = 1400 * cos((18.4 - mu - lamda) * M_PI * 2 / 360) +
                      439 * cos((97.64 - fi - mu - lamda) * M_PI * 2 / 360);
    float R7_FC = 2149.4;
    float C = (42.39 + lamda)*2 * M_PI / 360;
    Fb = ( maxFC*R7_FC - W_kepce*R7_Wkepce - W_kol*R7_Wkol )/
              ( sin(C)*R7_Fbx + cos(C)*R7_Fby);
    Db = sqrt(Fb/(Pc*M_PI))*200;
    Db = ceil(Db);
    Db *= 10;
    return Fb;
}
float MainWindow::F_Pim7x()
{
    float C = (42.39 + lamda) * 2 * M_PI/360;
    float B = (58.32 - fi - mu - lamda)*2*M_PI/360;
    F_P7x = Fb * sin(C) - maxFC * sin(B);
    return F_P7x;
}
float MainWindow::F_Pim7y()
{
    float C = (42.39 + lamda) * 2 * M_PI/360;
    float B = (58.32 - fi - mu - lamda) * 2 * M_PI/360;
    F_P7y = Fb * cos(C) + maxFC * cos(B) - W_kepce - W_kol;
    return F_P7y;
}
double MainWindow::F_a()
{
    double R10_Fa = 303.48;
    double R10_W = 1174.5 *cos((83.37-lamda)*M_PI*2/360);
    double R10_FP7x = 2461.75 * sin((65.75 - lamda) * M_PI * 2 / 360);
    double R10_FP7y = 2461.75 * cos((65.75 - lamda) * M_PI * 2 / 360);
    double R10_Fbx = 1592.5 * cos((2.7 - lamda) * M_PI * 2 / 360);
    double R10_Fby = 1592.5 * sin((2.7 - lamda) * M_PI * 2 / 360);
    double C = (42.39 + lamda) * 2 * M_PI / 360;
    Fa = (Fb*cos(C)*R10_Fby+ Fb * sin(C) * R10_Fbx +
          F_P7y  * R10_FP7y- F_P7x * R10_FP7x- W_boom*R10_W)/R10_Fa;
    Da = sqrt(Fa / (Pc * M_PI)) * 200;
    Da = ceil(Da);
    Da *= 10;
    return Fa;
}
