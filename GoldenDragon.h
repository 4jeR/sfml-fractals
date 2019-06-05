#pragma once

#include "Fractal.h"


/**
 * @class   [GoldenDragon]
 * @brief                       klasa reprezentujaca fraktal zloty smok - dziedziczy po klasie Fractal 
 */
class GoldenDragon : public Fractal{
public:

    /**
     * @fn      [GoldenDragon]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    GoldenDragon(const float XWINDOW, const float YWINDOW);
    

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
     * @fn      [Func_1-2]        
     * @brief                       zestaw metod, na podstawie ktorych przeliczane sa punkty w specyficzny dla danej metody sposob,
     * 
     * @param   [int]               iter - numer obecnej iteracji, a takze indeks dla danej pary punktow.
     */
    void Func_1(int iter);
    void Func_2(int iter);
};




GoldenDragon::GoldenDragon(const float XWINDOW, const float YWINDOW)
:Fractal(XWINDOW, YWINDOW)
{
    CalculatePoints();
    MapAllPoints();
}


void GoldenDragon::CalcProbability(){
    m_probability = rand()% 2 + 1;
}


void GoldenDragon::Func_1(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first) * 0.62367f + (m_xy[iteration-1].second) * -0.40337f;
    m_xy[iteration].second = (m_xy[iteration-1].first) * 0.40337f + (m_xy[iteration-1].second) * 0.62367f;
}


void GoldenDragon::Func_2(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first) * -0.37633f + (m_xy[iteration-1].second) * -0.40337f +1.0f;
    m_xy[iteration].second = (m_xy[iteration-1].first) * 0.40337f + (m_xy[iteration-1].second) * -0.37633f;      ;
}


float GoldenDragon::MapPointX(float x){
    return 0.70f * x * m_xwindow + m_xwindow / 5.0f;
}


float GoldenDragon::MapPointY(float y){
    return 1.2f * y * m_ywindow + m_ywindow / 4.0f;
}


void GoldenDragon::CalculatePoints(){
    srand(time(NULL));

    for(int i = 1; i < ITERATION_MAX; ++i){
        CalcProbability();
        if(m_probability == 1)
            Func_1(i);
        else if(m_probability == 2)
            Func_2(i);
    }
}
