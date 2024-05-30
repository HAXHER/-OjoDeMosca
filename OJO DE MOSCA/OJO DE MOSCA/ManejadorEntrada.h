#pragma once
#include <SFML/Graphics.hpp>
#include "Circulo.h"
using namespace sf;
using namespace std;


class ManejadorEntrada {
public:
    void ManejarEntrada(Circulo& circulo, const RenderWindow& ventana, float deltaTime) const {
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            circulo.Mover(0, -200 * deltaTime, ventana);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            circulo.Mover(0, 200 * deltaTime, ventana);
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            circulo.Mover(-200 * deltaTime, 0, ventana);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            circulo.Mover(200 * deltaTime, 0, ventana);
        }

        circulo.Rotar(50 * deltaTime);
    }
};