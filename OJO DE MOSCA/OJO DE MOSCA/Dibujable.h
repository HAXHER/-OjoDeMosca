#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;




    class IDibujable {
    public:
        virtual void Dibujar(RenderWindow& ventana) = 0;
        virtual ~IDibujable() = default;
    };


