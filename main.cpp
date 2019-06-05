/**
 * Projekt z Podstaw Grafiki Komputerowej generujący fraktale oraz transformacje między nimi.
 * 
 * Wykonany przez:
 * 
 * - Mikołaj Baczyński
 * - Bartłomiej Długosz
 * - Igor Półchłopek
 * 
 * © Copyright 2019. All rights reserved.
*/


#include "AllFractals.h"



/**
 * @fn      [MorphInto]
 * @brief                       funkcja, która przyjmuje fraktal dowolnego typu i morfuje ten obiekt w fraktal podany 
 *                              \ w drugim argumencie,
 * 
 * @param   [Fractal&]          fracToMorph - fraktal, który bedzie poddany morfowaniu,
 * @param   [const Fractal&]    finalFrac - typ fraktala, w ktory ma sie przemienic @fracToMorph ,
 * @param   [int]               steps - liczba kroków, w których dokona się przemiana,
 * @param   [RenderWindow&]     window - okno, na którym powstaje animacja,
 * @param   [const float]       XWINDOW - szerokosc okna,
 * @param   [const float]       YWINDOW - wysokosc okna
 * 
 */
void MorphInto(Fractal& fracToMorph,
               const Fractal& finalFrac,
               int steps,
               sf::RenderWindow& window,
               const float XWINDOW,
               const float YWINDOW);

int main(int argc, char ** argv){ 
    
    const float X_WINDOW = 1200; //< szerokosc okna typu [const float]
    const float Y_WINDOW = 800; //< wysokosc okna typu [const float]
    int ITERATION = 0; //< obecna iteracja typu [int]
    bool animation = false; //< pomocnicza zmienna typu [bool] przechowujaca informacje o tym,
                             // czy ma sie wyswietlac animacja morfowania fraktali 

    sf::RenderWindow window(sf::VideoMode(X_WINDOW, Y_WINDOW),
     "Fractals",
      sf::Style::Default | sf::Style::Titlebar | sf::Style::Close); //< okno typu [RenderWindow] wyswietlajace fraktale
    
    
    /* DOSTEPNE FRAKTALE */

    BarnsleyFern barn_fern(X_WINDOW, Y_WINDOW); //< wzor paproci Barnsleya typu [BarnsleyFern]
    SierpinskiTriangle sierp_triangle(X_WINDOW, Y_WINDOW); //< wzor trojkata Sierpinskiego typu [SierpinskiTriangle]
    SierpinskiSquare sierp_square(X_WINDOW, Y_WINDOW); //< wzor kwadratu Sierpinskiego typu [SierpinskiSquare]
    SierpinskiPentagon sierp_pentagon(X_WINDOW, Y_WINDOW); //< wzor pieciokata Sierpinskiego typu [SierpinskiPentagon]
    RecursiveTree rec_tree(X_WINDOW, Y_WINDOW); //< wzor drzewa rekursywnego typu [RecursiveTree]
    GoldenDragon dragon(X_WINDOW, Y_WINDOW); //< wzor zlotego smoka typu [GoldenDragon]
    Pentadentrite dentrite(X_WINDOW, Y_WINDOW); //< wzor pentadentrytu typu [Pentadentrite]

    Fractal* frac_ptr;
    // BarnsleyFern fractal(X_WINDOW, Y_WINDOW); /* glowny fraktal, ktory bedzie sluzyl przez caly proces animacji oraz generowania,
    //                                              \ poczatkowo typu [BarnsleyFern] */
    frac_ptr = &barn_fern;
    frac_ptr = &sierp_pentagon;

    sf::Event event; 
    srand(time(NULL));

    while(window.isOpen())
    {
        ITERATION++;
        
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
                window.close();
        }
        
        if(animation == false){
            frac_ptr->DrawFractal(window, ITERATION);

            if(ITERATION == ITERATION_MAX){  
                frac_ptr->DrawWholeFractal(window);
                animation = true;
                ITERATION = 0;
            }
        }
        else if(animation == true){
            usleep(1000000); // wyswietlenie fraktala na jedna sekunde
            int PROBABILITY = rand () % 7; //< zmienna pomocnicza, ktora jest odpowiedzialna za wybor obecnej animacji 

            switch(PROBABILITY){
                case 0:{
                    MorphInto(*frac_ptr, barn_fern, STEPS, window, X_WINDOW,Y_WINDOW); 
                    break;
                }
                case 1:{
                    MorphInto(*frac_ptr, sierp_triangle, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
                case 2:{
                    MorphInto(*frac_ptr, sierp_square, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
                case 3:{
                    MorphInto(*frac_ptr, sierp_pentagon, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
                case 4:{
                    MorphInto(*frac_ptr, rec_tree, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
                case 5:{
                    MorphInto(*frac_ptr, dragon, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
                case 6:{
                    MorphInto(*frac_ptr, dentrite, STEPS, window, X_WINDOW,Y_WINDOW);
                    break;
                }
            }                
        }
    } // end of while window is open
    
    return 0;   
 
} // end of main




void MorphInto(Fractal& fracToMorph, const Fractal& finalFrac, int steps, sf::RenderWindow& window, const float XWINDOW, const float YWINDOW){
    
    std::pair<double, double>* step = new std::pair<double, double>[ITERATION_MAX];

    for(unsigned j = 0; j < ITERATION_MAX; j++){
        step[j].first = (finalFrac.GetX(j) - fracToMorph.GetX(j)) / (steps);
        step[j].second = (finalFrac.GetY(j) - fracToMorph.GetY(j)) / (steps);
    }
  
    for(int iteration = 0; iteration < steps; ++iteration){
        for(int j = 1; j < ITERATION_MAX; ++j){

            fracToMorph.GetX(j) += step[j].first;
            fracToMorph.GetY(j) += step[j].second;

            sf::Color currentColor = sf::Color( static_cast<int>(fracToMorph.m_point.getPosition().y + j) % 256,
                                                100,
                                                static_cast<int>(fracToMorph.m_point.getPosition().x + 2 * j) % 256 );

            fracToMorph.m_point.setOutlineColor(currentColor);
        }

        window.clear();
        fracToMorph.DrawWholeFractal(window);

    }

    delete[] step;
}

