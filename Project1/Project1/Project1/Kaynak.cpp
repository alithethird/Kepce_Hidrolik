#define _USE_MATH_DEFINES
#include <cmath>
//#include <QtMath>
#include <iostream>
#include <string>

using namespace std;

float   
//kepçe girdileri
Pc = 170.0,  
Dc = 65.0,
W_kepce = 820.0,
R1FC = 729.46,

//kol girdileri    
W_kol = 1500,

//boom girdileri
W_boom = 2100;

float fi = 0, mu = 0, lamda = 0;            //açýlar

//kepçe için çýktýlar
float F12[190] = { 0 };                     // 12 Nolu parçanýn açý(fi) kuvvet dizisi
float F13[190] = { 0 };                     // 13 Nolu parçanýn açý(fi) kuvvet dizisi
float maxFC = 0,                            // Max kazma kuvveti
Fc = 0,                                     // Max kepçe silindir kuvveti
F_P1x = 0,                                  // MaxFC ye göre 1. pim reaksiyonu x bileþeni
F_P1y = 0;                                  // MaxFC ye göre 1. pim reaksiyonu y bileþeni

//kol için çýktýlar:
float   Fb = 0,                             // MaxFC ye göre kol silindir kuvveti
F_P7x = 0,                                  // MaxFC ye göre 7. pim reaksiyonu x bileþeni
F_P7y = 0,                                  // MaxFC ye göre 7. pim reaksiyonu y bileþeni
Db = 0;                                     // Fb/Pc den kol silindir çapý

//boom çýktýlar
double Fa = 0;                                     // MaxFC ye göre boom silindir kuvveti
double Da=0;

void Hesapla();                                     //Kutulardan çekilenleri burda atýycan

float A0(float);
float alfa(float);
float beta(float);      //alfa,beta, a0 ve r1f12 grafiklerin fonku,
float R1_F12(float);    // lazým olursa kullanýrsýn içlerine fi fýrlatcan

float R1_Wk(float, float, float);                   // R1 w kepçe denklemi
float F_12(float);                                  // 12 nolu parça kuvvet denklemi
float F_13( float, float);                          // 13 nolu parça kuvvet denklemi
float F_c();                                        // kepçe Piston max kuvveti
float F_C( float,float,float);                      // max kazma kuvveti denklemi
float F_Pim1x();                                    // 1. Perno Kuvveti x bileþeni
float F_Pim1y();                                    // 1. Perno Kuvveti x bileþeni

float F_b();                                        // Kol Pistonu max kuvveti ve piston çapý   
float F_Pim7x();                                    // 7. Perno Kuvveti x bileþeni
float F_Pim7y();                                    // 7. Perno Kuvveti y bileþeni

double F_a();                                       // MaxFC ye göre boom silindir kuvveti

int main(int argc, char* argv[])
{       
    /*
        Hesapla butanu
        {
            Hesapla();

            kepçe çýktý atamasý :
            write.box1(maxFC),
            write.box2(F_P1x),
            write.box3(F_P1y);

            kol için çýktý atamasý:
            write.box4(Fb)
            write.box5(F_P7x)
            write.box6(F_P7x)
            write.box7(Db)


        }
    */
    Hesapla();
    cout <<"Fc=   "<< Fc    << endl;
    cout <<"FC=   " <<maxFC << endl;
    cout <<"P1x=  " <<F_P1x << endl;
    cout <<"P1y=  " <<F_P1y << endl;
    cout << "Fb=  " << Fb << endl;
    cout << "P7x=  " << F_P7x << endl;
    cout << "P7y=  " << F_P7y << endl;
    cout << "Db=  " << Db<<endl;
    cout << "Fa=  " << Fa << endl;
    cout << "Da=  " << Da << endl;

    return 0;
}
void Hesapla()
{   
    //girdilerin atanmasý gereken kýsým
   /*
       kepçe bölümü için. örn. (Pc= read.box)
       Pc= piston çalýþma basýncý,
       Dc= piston çapý,
       R1FC,
       W_kepce
       
       kol için:
       W_kol
       
       boom için:
       w_boom

    */
    //arasý senindir
    Pc = Pc * pow(10, 5) * 1.0;
    Dc = Dc / 2000;
    F_c();
    for (int f1 = 0; f1 < 190; f1++)
    {
        f1 = f1 * 1.0;
        F12[f1] = F_12(f1);
        F13[f1] = F_13(F12[f1], f1);
    }
    for (int l1 = 0; l1 < 131; l1++) {
        l1 *= 1.0;
        for (int m1 = 0; m1 < 103; m1++) {
            m1 = m1 * 1.0;
            for (int f1 = 0; f1 < 190; f1++)
            {
                float FC = abs(F_C(f1, m1, l1));
                if (FC > maxFC) {
                    maxFC = F_C(f1, m1, l1);  //    17708.1
                    mu = m1 * 1.0;                                    //    102
                    fi = f1 * 1.0;                                    //    48
                    lamda = l1 * 1.0;                                 //    111
                }
            }
        }
    }
    F_Pim1x();
    F_Pim1y();
    F_b();
    F_Pim7x();
    F_Pim7y();
    F_a();
}
float A0(float f_i)
{
    float a0 = 0;
    a0 = 82.308 * exp(0.0035 * f_i);
    return a0;
}
float alfa(float f_i)
{
    float A = 1.0195 * f_i - 0.0022 * pow(f_i, 2) - 55.242;
    return A;
}
float beta(float f_i)
{
    float B = 0.0026 * pow(f_i, 2) - 0.7042 * f_i + 63.953;
    return B;
}
float R1_F12(float f_i)
{
    float R1 = 1.3613 * f_i - 0.0086 * pow(f_i, 2) + 137.84;
    return R1;
}
float R1_Wk(float f_i, float m_u, float l_amda)
{
    float RW = 439 * cos((97.64 - f_i - m_u - l_amda)*M_PI*2/360);
    return RW;
}
float F_c()
{
    Fc = Pc * pow(Dc,2)*M_PI;
    return Fc;
}
float F_12(float f_i)
{
    float F12 = Fc * cos(alfa(f_i) * M_PI * 2 / 360) / cos(beta(f_i) * M_PI * 2 / 360);
    return F12;
}
float F_13(float F12, float f_i)
{
    float F13 = Fc * sin(alfa(f_i) * M_PI * 2 / 360) + F12*sin(beta(f_i)  * M_PI * 2 / 360);
    return F13;
}
float F_C(float f_i, float m_u, float l_amda)
{
    float FC = (F_12(f_i) * R1_F12(f_i) + W_kepce * R1_Wk(f_i, m_u, l_amda)) / R1FC;
    return FC;
}
float F_Pim1x()
{
    float A = A0(fi) + lamda + mu;
    float B = 58.32 - lamda - mu - fi;
    F_P1x = F_12(fi) * sin(A * M_PI * 2 / 360)
              - maxFC * sin(B * M_PI * 2 / 360);
    return F_P1x;
}
float F_Pim1y()
{   
    float A = A0(fi) + lamda + mu;
    float B = 58.32 - lamda - mu - fi;
    F_P1y = F_12(fi) * cos(A * M_PI * 2 / 360) 
              + maxFC * cos(B * M_PI * 2 / 360)-W_kepce;
    return F_P1y;
}
float F_b()
{
    float R7_Fbx = 361.7 * sin((11.3 + mu + lamda)*2*M_PI/360);
    float R7_Fby = 361.7 * cos((11.3 + mu + lamda) * 2 * M_PI / 360);
    float R7_Wkol = 550 * cos((27.73 - mu - lamda) * 2 * M_PI / 360);
    float R7_Wkepce = 1400 * cos((18.4 - mu - lamda) * M_PI * 2 / 360) +
                      439 * cos((97.64 - fi - mu - lamda) * M_PI * 2 / 360);
    float R7_FC = 2125;
    float C = (51.4 + lamda)*2*M_PI/360;
    Fb = ( maxFC*R7_FC - W_kepce*R7_Wkepce - W_kol*R7_Wkol )/
              ( sin(C)*R7_Fbx + cos(C)*R7_Fby);
    Db = sqrt(Fb/(Pc*M_PI))*200;
    Db = ceil(Db);
    Db *= 10;
    return Fb;
}
float F_Pim7x()
{
    float C = (51.4 + lamda) * 2 * M_PI;
    float B = (58.32 - fi - mu - lamda)*2*M_PI;
    F_P7x = Fb * sin(C) - maxFC * sin(B);
    return F_P7x;
}
float F_Pim7y()
{
    float C = (51.4 + lamda) * 2 * M_PI;
    float B = (58.32 - fi - mu - lamda) * 2 * M_PI;
    F_P7y = Fb * cos(C) + maxFC * cos(B) - W_kepce - W_kol;
    return F_P7y;
}
double F_a()
{
    double R10_Fa = 200;
    double R10_W = 1174.5 *cos(83.37-lamda);
    double R10_FP7x = 2461.75 * sin(65.75 - lamda);
    double R10_FP7y = 2461.75 * cos(65.75 - lamda);
    double R10_Fbx = 1592.5 * cos(2.7 - lamda);
    double R10_Fby = 1592.5 * sin(2.7 - lamda);
    double C = (51.4 + lamda) * 2 * M_PI / 360;
    Fa = (Fb*cos(C)*R10_Fby+ Fb * sin(C) * R10_Fbx + 
          F_P7y  * R10_FP7y- F_P7x * R10_FP7x- W_boom*R10_W)/R10_Fa;
    Da = sqrt(Fa / (Pc * M_PI)) * 200;
    Da = ceil(Da);
    Da *= 10;
    return Fa;
}