#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES

using namespace sf;
using namespace std;

const float Pi = 3.1416 * 2;

class Circulo : Transform {
private:
    float Radio = 250.f;
    float CentroX = 250.f;
    float CentroY = 250.f;
    vector<Vertex> vertices;
    vector<Vertex> lines;

public:
    Circulo(int numVertices) {
        float angulo = 0;
        float anguloIncremento = 2 * Pi / numVertices;

        // Generar los vértices
        for (int i = 0; i < numVertices; ++i) {
            float x = CentroX + Radio * cos(angulo);
            float y = CentroY + Radio * sin(angulo);
            vertices.push_back(Vertex(Vector2f(x, y), Color::Black));
            angulo += anguloIncremento;
        }

        // Generar las líneas
        for (size_t i = 0; i < vertices.size(); ++i) {
            for (size_t j = i + 1; j < vertices.size(); ++j) {
                lines.push_back(vertices[i]);
                lines.push_back(vertices[j]);
            }
        }
    }

    void Dibujar(RenderWindow& ventana) {
        CircleShape Circulo(Radio);
        Circulo.setFillColor(Color::Yellow);
        Circulo.setOrigin(0, 0);

        ventana.clear();
        ventana.draw(Circulo);

        // Dibujar los vértices
        for (const auto& vertex : vertices) {
            Vertex point = vertex;
            ventana.draw(&point, 1, Points);
        }

        // Dibujar las líneas
        ventana.draw(lines.data(), lines.size(), Lines);
        ventana.display();
    }
};

int main() {
    int numVertices;
    cout << "Ingrese el numero de vertices que tendra tu ojo de mosca: ";
    cin >> numVertices;

    RenderWindow window(VideoMode(500, 500), "Ojo de Mosca");
    Circulo Vertices(numVertices);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        Vertices.Dibujar(window);
    }

    return 0;
}
