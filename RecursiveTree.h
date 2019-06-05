#pragma once

#include "Fractal.h"


/**
 * @class   [RecursiveTree]
 * @brief                       klasa reprezentujaca drzewo rekursywne - dziedziczy po klasie Fractal 
 */
class RecursiveTree : public Fractal{
public:

    /**
     * @fn      [RecursiveTree]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    RecursiveTree(const float XWINDOW, const float YWINDOW);
    

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
    float MapPointX(float x);


    /**
     * @fn      [MapPointY]         
     * @brief                       czysto wirtualna metoda override, ktora mapuje wspolrzedna y punktu fraktala,
     * @param   [float]             y - wspolrzedna y punktu,
     * @return  [float]             odpowiednio zmapowana nowa wspolrzedna y.
     */
    float MapPointY(float y);


    /**
     * @fn      [Func_1-3]        
     * @brief                       zestaw metod, na podstawie ktorych przeliczane sa punkty w specyficzny dla danej metody sposob,
     * 
     * @param   [int]               iter - numer obecnej iteracji, a takze indeks dla danej pary punktow.
     */
    void Func_1(int iteration);
    void Func_2(int iteration);
    void Func_3(int iteration);

private:
    float r = 0.7f; //< wspolczynnik skalujacy dlugosc kolejnych galezi
    float angle = 45.0f * M_PI / 180.0f; //< kąt, pod ktorym rysowane sa kolejne galezie drzewa
};




RecursiveTree::RecursiveTree(const float XWINDOW, const float YWINDOW)
:Fractal(XWINDOW, YWINDOW)
{   
    CalculatePoints();
    MapAllPoints();
}
    

void RecursiveTree::CalculatePoints(){
    srand(time(NULL));

    for(int i = 1; i < ITERATION_MAX; ++i){
        CalcProbability();
        if(m_probability == 1)
            Func_1(i);
        else if(m_probability == 2)
            Func_2(i);
        else if(m_probability == 3)
            Func_3(i);    
    }
}


void RecursiveTree::CalcProbability(){
    m_probability = rand() % 3 +1;
}


float RecursiveTree::MapPointX(float x){
    return x * m_xwindow * 0.25f + m_xwindow / 2.0f;
}


float RecursiveTree::MapPointY(float y){
    return y * m_ywindow * 0.25f + m_ywindow / 8.0f;
}


void RecursiveTree::Func_1(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first) * r * std::cos(angle) + (m_xy[iteration-1].second) * -r * std::sin(angle);
    m_xy[iteration].second = (m_xy[iteration-1].first) * r * std::sin(angle) + (m_xy[iteration-1].second) * r * std::cos(angle)  + 1.0f;
}

void RecursiveTree::Func_2(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first) * r * std::cos(angle) + (m_xy[iteration-1].second) * r * std::sin(angle);
    m_xy[iteration].second = (m_xy[iteration-1].first) * -r * std::sin(angle) + (m_xy[iteration-1].second) * r * std::cos(angle)  + 1.0f;
}


void RecursiveTree::Func_3(int iteration){
    m_xy[iteration].first  = (m_xy[iteration-1].first);
    m_xy[iteration].second = (m_xy[iteration-1].second);
}

