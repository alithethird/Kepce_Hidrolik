#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    //kepce girdiler
    float Pc = 170.0, Dc = 65.0, W_kepce = 820.0, R1FC = 729.46;

    //kol girdileri
    float W_kol = 1500;

    //boom girdileri
    float W_boom = 2100;

    float fi = 40, mu = 30, lamda = 60;            //açılar

    //kepçe için çıktılar
    float F12[190] = { 0 };                     // 12 Nolu parçanın açı(fi) kuvvet dizisi
    float F13[190] = { 0 };                     // 13 Nolu parçanın açı(fi) kuvvet dizisi
    float maxFC = 0;                            // Max kazma kuvveti
    float Fc = 0;                                     // Max kepçe silindir kuvveti
    float F_P1x = 0;                                  // MaxFC ye göre 1. pim reaksiyonu x bileşeni
    float F_P1y = 0;                                  // MaxFC ye göre 1. pim reaksiyonu y bileşeni

    //kol için çıktılar:
    float   Fb = 0;                             // MaxFC ye göre kol silindir kuvveti
    float F_P7x = 0;                                  // MaxFC ye göre 7. pim reaksiyonu x bileşeni
    float F_P7y = 0;                                  // MaxFC ye göre 7. pim reaksiyonu y bileşeni
    float Db = 0;                                     // Fb/Pc den kol silindir çapı

    //boom çıktılar
    double Fa = 0;                                     // MaxFC ye göre boom silindir kuvveti
    double Da=0;

    void Hesapla();                                     //Kutulardan çekilenleri burda atıycan

    float A0(float);
    float alfa(float);
    float beta(float);      //alfa,beta, a0 ve r1f12 grafiklerin fonku,
    float R1_F12(float);    // lazım olursa kullanırsın içlerine fi fırlatcan

    float R1_Wk();                   // R1 w kepçe denklemi
    float F_12(float);                                  // 12 nolu parça kuvvet denklemi
    float F_13( float, float);                          // 13 nolu parça kuvvet denklemi
    float F_c();                                        // kepçe Piston max kuvveti
    float F_C();                      // max kazma kuvveti denklemi
    float F_Pim1x();                                    // 1. Perno Kuvveti x bileşeni
    float F_Pim1y();                                    // 1. Perno Kuvveti x bileşeni

    float F_b();                                        // Kol Pistonu max kuvveti ve piston çapı
    float F_Pim7x();                                    // 7. Perno Kuvveti x bileşeni
    float F_Pim7y();                                    // 7. Perno Kuvveti y bileşeni

    double F_a();

private slots:

    void setPixmaps();
    void on_pushButtonHesapla_clicked();
    void degerOku();
    void sonucGoster();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
