#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "Circulo.h"
#include "ManejadorEntrada.h"



using namespace sf;
using namespace std;

#define _USE_MATH_DEFINES





int main() {
    int numVertices;
    cout << "Ingrese el número de vértices que tendrá su ojo de mosca: ";
    cin >> numVertices;

    RenderWindow ventana(VideoMode(500, 500), "Ojo de Mosca");
    Circulo vertices(numVertices);
    ManejadorEntrada manejadorEntrada;

    Clock reloj;
    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed)
                ventana.close();
        }

        float deltaTime = reloj.restart().asSeconds();
        manejadorEntrada.ManejarEntrada(vertices, ventana, deltaTime);
        vertices.Dibujar(ventana);
    }

    return 0;
}
