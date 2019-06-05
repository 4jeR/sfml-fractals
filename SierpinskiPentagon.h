#pragma once

#include "Fractal.h"


/**
 * @class   [SierpinskiPentagon]
 * @brief                       klasa reprezentujaca pieciokat Sierpinskiego - dziedziczy po klasie Fractal 
 */
class SierpinskiPentagon : public Fractal{
public:

    /**
     * @fn      [SierpinskiPentagon]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    SierpinskiPentagon(const float XWINDOW, const float YWINDOW);
    

    /**
     * @fn      [CalculatePoints]   
     * @brief                       wirtualna metoda override, ktora przelicza punkty fraktala na podstawie 
     *                              \ wylosowanego prawdopodobienstwa - wola ona metode @CalculatePoints oraz @MapAllPoints.
     */
    void CalculatePoints()override;


    /**
     * @fn      [CalcProbability] 
     * @brief                       czysto wirtualna metoda override, ktora wylicza prawdopodobienstwo, na podstawie ktorego
     *                              \ wolana jest odpowiednia metoda skladowa klasy przypisujaca wspolrzedne punktu do tablicy.
     */
    void CalcProbability()override;


    /**
     * @fn      [MapPointX]         
     * @brief                       czysto wirtualna metoda override, ktora mapuje wspolrzedna x punktu fraktala,
     * @param   [float]             x - wspolrzedna x punktu,
     * @return  [float]             odpowiednio zmapowana nowa wspolrzedna x.
     */
    float MapPointX(float x)override;


    /**
     * @fn      [MapPointY]         
     * @brief                       czysto wirtualna metoda override, ktora mapuje wspolrzedna y punktu fraktala,
     * @param   [float]             y - wspolrzedna y punktu,
     * @return  [float]             odpowiednio zmapowana nowa wspolrzedna y.
     */
    float MapPointY(float y)override;

    
    /**
     * @fn      [Func_1-5]        
     * @brief                       zestaw metod, na podstawie ktorych przeliczane sa punkty w specyficzny dla danej metody sposob,
     * 
     * @param   [int]               iter - numer obecnej iteracji, a takze indeks dla danej pary punktow.
     */
    void Func_1(int iter);
    void Func_2(int iter);
    void Func_3(int iter);
    void Func_4(int iter);
    void Func_5(int iter);
    
    

};



SierpinskiPentagon::SierpinskiPentagon(const float XWINDOW, const float YWINDOW)
:Fractal(XWINDOW, YWINDOW)
{
    CalculatePoints();
    MapAllPoints();
}


void SierpinskiPentagon::CalcProbability(){
    m_probability = rand()% 5 + 1;
}


void SierpinskiPentagon::Func_1(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  * 0.382f;
    m_xy[iteration].second = (m_xy[iteration-1].second) * 0.382f;
}


void SierpinskiPentagon::Func_2(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  * 0.382f + 0.618f;
    m_xy[iteration].second = (m_xy[iteration-1].second) * 0.382f;
}


void SierpinskiPentagon::Func_3(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  * 0.382f + 0.809f;
    m_xy[iteration].second = (m_xy[iteration-1].second) * 0.382f + 0.588f;
}


void SierpinskiPentagon::Func_4(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.382f + 0.309f;
    m_xy[iteration].second =   (m_xy[iteration-1].second) * 0.382f + 0.951f;
}


void SierpinskiPentagon::Func_5(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  * 0.382f - 0.191f;
    m_xy[iteration].second = (m_xy[iteration-1].second) * 0.382f + 0.588f;
}


float SierpinskiPentagon::MapPointX(float x){
    return 0.6f * x * m_xwindow + m_xwindow / 5.0f;
}


float SierpinskiPentagon::MapPointY(float y){
    return 0.6f * y * m_ywindow + m_ywindow / 10.0f - 45.0f;
}


void SierpinskiPentagon::CalculatePoints(){
    srand(time(NULL));

    for(int i = 1; i < ITERATION_MAX; ++i){
        CalcProbability();
        if(m_probability == 1)
            Func_1(i);
        else if(m_probability == 2)
            Func_2(i);
        else if(m_probability == 3)
            Func_3(i);
        else if(m_probability == 4)
            Func_4(i);
        else if(m_probability == 5)
            Func_5(i);
    }
}
