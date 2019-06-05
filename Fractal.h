#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <utility>
#include <math.h>
#include <unistd.h>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


// predefiniowane stale w czasie kompilacji

#define ITERATION_MAX 12500 /* liczba iteracji - punktow z ktorych sklada sie kazdy fraktal
                             - im wiecej tym dokladniejszy fraktal, lecz tym wolniej dziala caly program */


#define STEPS 52 /* liczba krokow, w ktorych nastepuje transformacja jednego fraktala w drugi
                 - im wiecej tym plynniej ale i dluzej */


/**
 * @class       [Fractal]
 * @brief                           wirtualna klasa - udostepnia interfejs kazdemu fraktalowi, ktory dziedziczy po tej klasie.
 */
class Fractal{
public:

    /**
     * @fn      [Fractal]
     * @brief                       konstruktor, ktory alokuje pamiec na wszystkie punkty fraktala, inicjalizuje rozmiary okna
     *                              \ oraz ustawia poczatkowy kolor punktow,  
     * @param   [const float]       XWINDOW - szerokosc okna,
     * @param   [const float]       YWINDOW - wysokosc okna.
     */
    Fractal(const float XWINDOW, const float YWINDOW);


    /**
     * @fn      [~Fractal]
     * @brief                       wirtualny destruktor dla dziedziczenia, ktory dealokuje zarezerwowana pamiec
     *                              \ na punkty fraktala.
     */
    virtual ~Fractal();


    /**
     * @fn      [DrawFractal]
     * @brief                       wirtualna metoda, ktora rysuje fraktal - punkt po punkcie, w zaleznosci od numeru iteracji,
     * @param   [RenderWindow&]     window - okno, na ktorym ma byc rysowany fraktal,
     * @param   [int]               iter - obecna iteracja, a takze indeks punktu ktory ma byc wyrysowany na oknie.
     */
    virtual void DrawFractal(sf::RenderWindow& window, int iter);


    /**
     * @fn      [DrawWholeFractal]  
     * @brief                       wirtualna metoda, ktora rysuje odrazu caly fraktal na ekran,
     * @param   [RenderWindow&]     window - okno, na ktorym ma byc rysowany fraktal.
     */
    virtual void DrawWholeFractal(sf::RenderWindow& window);


    /**
     * @fn      [CalcProbability] 
     * @brief                       czysto wirtualna metoda, ktora wylicza prawdopodobienstwo, na podstawie ktorego
     *                              \ wolana jest odpowiednia metoda skladowa klasy przypisujaca wspolrzedne punktu do tablicy.
     */
    virtual void CalcProbability() = 0;
    

    /**
     * @fn      [CalculatePoints]   
     * @brief                       wirtualna metoda, ktora przelicza punkty fraktala na podstawie 
     *                              \ wylosowanego prawdopodobienstwa - wola ona metode @CalculatePoints oraz @MapAllPoints.
     */
    virtual void CalculatePoints() = 0;


    /**
     * @fn      [MapAllPoints]      
     * @brief                       czysto wirtualna metoda, ktora mapuje kazdy punkt fraktala tak, aby
     *                              \ znajdowal sie w obrebie okna.
     */
    virtual void MapAllPoints();


    /**
     * @fn      [MapPointX]         
     * @brief                       czysto wirtualna metoda, ktora mapuje wspolrzedna x punktu fraktala,
     * @param   [float]             x - wspolrzedna x punktu,
     * @return  [float]             odpowiednio zmapowana nowa wspolrzedna x.
     */
    virtual float MapPointX(float x) = 0;


    /**
     * @fn      [MapPointY]         
     * @brief                       czysto wirtualna metoda, ktora mapuje wspolrzedna y punktu fraktala,
     * @param   [float]             y - wspolrzedna y punktu,
     * @return  [float]             odpowiednio zmapowana nowa wspolrzedna y.
     */
    virtual float MapPointY(float y) = 0;


    /**
     * @fn      [GetX]              
     * @brief                       metoda, ktora zwraca pierwsza wspolrzedna pary punktu przy danym indeksie,
     * 
     * @param   [int]               iter - numer iteracji, a takze indeks pary z ktorej ma byc zwrocony x,
     * @return  [float]             wspolrzedna x danej pary.
     */
    float GetX(int iter)const{return m_xy[iter].first; }


    /**
     * @fn      [GetY]              
     * @brief                       metoda, ktora zwraca druga wspolrzedna pary punktu przy danym indeksie,
     * 
     * @param   [int]               iter - numer iteracji, a takze indeks pary z ktorej ma byc zwrocony y,
     * @return  [float]             wspolrzedna y danej pary
     */
    float GetY(int iter)const{return m_xy[iter].second; }


    /**
     * @fn      [GetX]              
     * @brief                       metoda, ktora zwraca pierwsza wspolrzedna pary punktu przy danym indeksie,
     *                              \ a takze umozliwia zapis na danej wspolrzednej,
     * 
     * @param   [int]               iter - numer iteracji, a takze indeks pary z ktorej ma byc zwrocony x,
     * @return  [float&]            wspolrzedna x danej pary.
     */
    float& GetX(int iter){return m_xy[iter].first; }


    /**
     * @fn      [GetY]              
     * @brief                       metoda, ktora zwraca pierwsza wspolrzedna pary punktu przy danym indeksie,
     *                              \ a takze umozliwia zapis na danej wspolrzednej,
     * 
     * @param   [int]               iter - numer iteracji, a takze indeks pary z ktorej ma byc zwrocony y,
     * @return  [float&]            wspolrzedna y danej pary.
     */
    float& GetY(int iter){return m_xy[iter].second; }


    /**
     * @fn      [MorphInto]
     * @brief                       zaprzyjazniona funkcja globalna, ktora umozliwia morfowanie fraktalu jednego typu w drugi                
     */
    friend void MorphInto(  Fractal& fracToMorph,
                            const Fractal& finalFrac,
                            int steps,
                            sf::RenderWindow& window,
                            const float XWINDOW,
                            const float YWINDOW);

protected:
    float m_xwindow; //< szerokosc okna,
    float m_ywindow; //< wysokosc okna

    int m_probability; //< prawdopodobienstwo przydatne do wyboru metody, ktora wyznacza polozenie punktow danego fraktala

    std::pair<float, float>* m_xy; //< wskaznik na dynamicznie alokowana tablice par punktow - reprezentuje punkty fraktala

    sf::CircleShape m_point; //< pojedynczy punkt graficznie reprezentowany jako bardzo male kolo
};




Fractal::Fractal(const float XWINDOW, const float YWINDOW)
:m_xwindow(XWINDOW), m_ywindow(YWINDOW)
{
    m_xy = new std::pair<float, float>[ITERATION_MAX];
    m_point = sf::CircleShape(0.01);
    m_point.setOutlineThickness(0.9); 
    m_xy[0].first = XWINDOW / 2;
    m_xy[0].second = YWINDOW / 2;
}


Fractal::~Fractal(){
    delete[] m_xy;
}


void Fractal::DrawFractal(sf::RenderWindow& window, int i){
    m_point.setPosition(m_xy[i].first, m_xy[i].second);
    window.draw(m_point);  
    window.display();
    
}


void Fractal::DrawWholeFractal(sf::RenderWindow& window){
    for(int i = 0; i < ITERATION_MAX; ++i){

        m_point.setPosition(m_xy[i].first, m_xy[i].second);
        window.draw(m_point);  

    }
    window.display();
}


void Fractal::MapAllPoints(){
    for(int i = 0; i < ITERATION_MAX; ++i){
        m_xy[i].first  = MapPointX(m_xy[i].first);
        m_xy[i].second = MapPointY(m_xy[i].second);
    }
}   