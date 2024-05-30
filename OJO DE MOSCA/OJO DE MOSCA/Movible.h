#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;


class IMovible {
public:
    virtual void Mover(float offsetX, float offsetY, const RenderWindow& ventana) = 0;
    virtual ~IMovible() = default;
};