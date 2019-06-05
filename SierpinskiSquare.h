#pragma once

#include "Fractal.h"


/**
 * @class   [SierpinskiSquare]
 * @brief                       klasa reprezentujaca kwadrat Sierpinskiego - dziedziczy po klasie Fractal 
 */
class SierpinskiSquare : public Fractal{
public:

    /**
     * @fn      [SierpinskiSquare]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    SierpinskiSquare(const float XWINDOW, const float YWINDOW);
    

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
     * @fn      [Func_1-8]        
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
    void Func_7(int iter);
    void Func_8(int iter);
};




SierpinskiSquare::SierpinskiSquare(const float XWINDOW, const float YWINDOW)
:Fractal(XWINDOW, YWINDOW)
{
    CalculatePoints();
    MapAllPoints();
}


void SierpinskiSquare::CalcProbability(){
    m_probability = rand()% 8 + 1;
}


void SierpinskiSquare::Func_1(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f  ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f  ;
}


void SierpinskiSquare::Func_2(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f  ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f  + 1.0f / 3.0f;
}


void SierpinskiSquare::Func_3(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f  ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f  + 2.0f / 3.0f; 
}


void SierpinskiSquare::Func_4(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f  + 1.0f / 3.0f;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f  ;
}


void SierpinskiSquare::Func_5(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f + 1.0f / 3.0f ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f + 2.0f / 3.0f ;
}


void SierpinskiSquare::Func_6(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f + 2.0f / 3.0f ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f  ;
}


void SierpinskiSquare::Func_7(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f + 2.0f / 3.0f;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f + 1.0f / 3.0f;
}


void SierpinskiSquare::Func_8(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first)  / 3.0f + 2.0f / 3.0f ;
    m_xy[iteration].second = (m_xy[iteration-1].second) / 3.0f + 2.0f / 3.0f ; 
}


float SierpinskiSquare::MapPointX(float x){
    return x * m_xwindow * 0.82f + m_xwindow / 11.0f;
}

float SierpinskiSquare::MapPointY(float y){
    return y * m_ywindow * 0.82f + m_ywindow / 12.0f;
}


void SierpinskiSquare::CalculatePoints(){
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
        else if(m_probability == 7)
            Func_7(i);
        else if(m_probability == 8)
            Func_8(i);
    }
}
