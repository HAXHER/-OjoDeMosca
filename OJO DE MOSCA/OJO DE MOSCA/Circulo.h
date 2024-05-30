#pragma once
#include <SFML/Graphics.hpp>
#include "Dibujable.h"
#include "Movible.h"
#include "Rotable.h"

using namespace sf;
using namespace std;



const float Pi = 3.1416;




class Circulo : public Transformable, public IDibujable, public IMovible, public IRotable {
private:
    float radio = 100.f;
    float centroX = 250.f;
    float centroY = 250.f;
    vector<Vertex> vertices;
    vector<Vector2f> posicionesIniciales;
    float anguloRotacion = 0.f;

    bool DentroPantalla(float offsetX, float offsetY, const RenderWindow& ventana) const {
        float nuevoX = centroX + offsetX;
        float nuevoY = centroY + offsetY;
        float izquierda = nuevoX - radio;
        float derecha = nuevoX + radio;
        float arriba = nuevoY - radio;
        float abajo = nuevoY + radio;

        return (izquierda >= 0 && derecha <= ventana.getSize().x && arriba >= 0 && abajo <= ventana.getSize().y);
    }

public:
    Circulo(int numVertices) {
        float angulo = 0;
        float incrementoAngulo = Pi * 2 / numVertices;

        for (int i = 0; i < numVertices; ++i) {
            float x = centroX + radio * cos(angulo);
            float y = centroY + radio * sin(angulo);
            vertices.push_back(Vertex(Vector2f(x, y), Color::Black));
            posicionesIniciales.push_back(Vector2f(x, y));
            angulo += incrementoAngulo;
        }
    }

    void Dibujar(RenderWindow& ventana) override {
        CircleShape formaCirculo(radio);
        formaCirculo.setFillColor(Color::Yellow);
        formaCirculo.setOrigin(radio, radio);
        formaCirculo.setPosition(centroX, centroY);
        formaCirculo.setRotation(anguloRotacion);
        ventana.clear();
        ventana.draw(formaCirculo);

        Vector2f centroCirculo(centroX, centroY);
        float anguloRadianes = anguloRotacion * Pi / 180;
        vector<Vector2f> posicionesRotadas;

        for (size_t i = 0; i < posicionesIniciales.size(); ++i) {
            Vector2f posicionVertice = posicionesIniciales[i] - centroCirculo;
            float xRotado = posicionVertice.x * cos(anguloRadianes) - posicionVertice.y * sin(anguloRadianes);
            float yRotado = posicionVertice.x * sin(anguloRadianes) + posicionVertice.y * cos(anguloRadianes);
            Vector2f posicionRotada = centroCirculo + Vector2f(xRotado, yRotado);
            posicionesRotadas.push_back(posicionRotada);
            Vertex punto(posicionRotada, vertices[i].color);
            ventana.draw(&punto, 1, Points);
        }

        for (size_t i = 0; i < posicionesRotadas.size(); ++i) {
            for (size_t j = i + 1; j < posicionesRotadas.size(); ++j) {
                Vertex linea[] = {
                    Vertex(posicionesRotadas[i], Color::Black),
                    Vertex(posicionesRotadas[j], Color::Black)
                };
                ventana.draw(linea, 2, Lines);
            }
        }

        ventana.display();
    }

    void Mover(float offsetX, float offsetY, const RenderWindow& ventana) override {
        if (DentroPantalla(offsetX, offsetY, ventana)) {
            move(offsetX, offsetY);
            centroX += offsetX;
            centroY += offsetY;
            for (auto& posicionInicial : posicionesIniciales) {
                posicionInicial.x += offsetX;
                posicionInicial.y += offsetY;
            }
        }
    }

    void Rotar(float angulo) override {
        anguloRotacion += angulo;
    }

    Vector2f ObtenerCentro() const {
        return Vector2f(centroX, centroY);
    }
};