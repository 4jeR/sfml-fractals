#pragma once

#include "Fractal.h"


/**
 * @class   [Pentadentrite]
 * @brief                       klasa reprezentujaca pentadentryt - dziedziczy po klasie Fractal 
 */
class Pentadentrite : public Fractal{
public:

    /**
     * @fn      [Pentadentrite]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    Pentadentrite(const float XWINDOW, const float YWINDOW);
    

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
     * @fn      [Func_1-6]        
     * @brief                       zestaw metod, na podstawie ktorych przeliczane sa punkty w specyficzny dla danej metody sposob,
     * 
     * @param   [int]               iter - numer obecnej iteracji, a takze indeks dla danej pary punktow.
     */
    void Func_1(int iter);
    void Func_2(int iter);
    void Func_3(int iter);
    void Func_4(int iter);
    void Func_5(int iter);
    void Func_6(int iter);
};




Pentadentrite::Pentadentrite(const float XWINDOW, const float YWINDOW)
:Fractal(XWINDOW, YWINDOW)
{
    CalculatePoints();
    MapAllPoints();
}

void Pentadentrite::CalcProbability(){
    m_probability = rand()% 6 + 1;
}


void Pentadentrite::Func_1(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.341f - (m_xy[iteration-1].second) *0.071f ;
    m_xy[iteration].second =   (m_xy[iteration-1].first)  * 0.071f + (m_xy[iteration-1].second) * 0.341f;
}


void Pentadentrite::Func_2(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.038f - (m_xy[iteration-1].second) * 0.346f + 0.341f;
    m_xy[iteration].second =   (m_xy[iteration-1].first)  * 0.346f + (m_xy[iteration-1].second) * 0.038f + 0.071f;
}


void Pentadentrite::Func_3(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.341f - (m_xy[iteration-1].second) * 0.071f + 0.379f;
    m_xy[iteration].second =   (m_xy[iteration-1].first)  * 0.071f + (m_xy[iteration-1].second) * 0.341f + 0.418f;
}


void Pentadentrite::Func_4(int iteration){
    m_xy[iteration].first  =   -(m_xy[iteration-1].first)  * 0.234f + (m_xy[iteration-1].second) * 0.258f + 0.720f;
    m_xy[iteration].second =   -(m_xy[iteration-1].first)  * 0.258f - (m_xy[iteration-1].second) * 0.234f + 0.489f;
}


void Pentadentrite::Func_5(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.173f + (m_xy[iteration-1].second) * 0.302f + 0.486f;
    m_xy[iteration].second =   -(m_xy[iteration-1].first)  * 0.302f + (m_xy[iteration-1].second) * 0.173f + 0.231f;
}


void Pentadentrite::Func_6(int iteration){
    m_xy[iteration].first  =   (m_xy[iteration-1].first)  * 0.341f - (m_xy[iteration-1].second) * 0.071f + 0.659f;
    m_xy[iteration].second =   (m_xy[iteration-1].first)  * 0.071f + (m_xy[iteration-1].second) * 0.341f - 0.071f;
}


float Pentadentrite::MapPointX(float x){
    return 0.78f * x * m_xwindow + m_xwindow / 8.0f;
}


float Pentadentrite::MapPointY(float y){
    return 1.05f * y * m_ywindow + m_ywindow / 5.0f ;
}


void Pentadentrite::CalculatePoints(){
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
        else if(m_probability == 6)
            Func_6(i);
    }
}
