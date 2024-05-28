#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#define _USE_MATH_DEFINES

using namespace sf;
using namespace std;

const float Pi = 3.1416;

// Interfaz para representar objetos que se pueden dibujar
class IDrawable {
public:
    virtual void Dibujar(RenderWindow& ventana) = 0;
    virtual ~IDrawable() = default;
};

// Interfaz para representar objetos que se pueden mover
class IMovable {
public:
    virtual void Mover(float offsetX, float offsetY, const RenderWindow& ventana) = 0;
    virtual ~IMovable() = default;
};

// Interfaz para representar objetos que se pueden rotar
class IRotatable {
public:
    virtual void Rotar(float angle) = 0;
    virtual ~IRotatable() = default;
};

class Circulo : public Transformable, public IDrawable, public IMovable, public IRotatable {
private:
    float Radio = 200.f;
    float CentroX = 250.f;
    float CentroY = 250.f;
    vector<Vertex> vertices;
    vector<Vector2f> initialPositions; // Almacena las posiciones iniciales de los vértices
    float rotationAngle = 0.f;

    // Check if the circle is within the window bounds
    bool dentroPantalla(float offsetX, float offsetY, const RenderWindow& ventana) const {
        float newX = CentroX + offsetX;
        float newY = CentroY + offsetY;
        float left = newX - Radio;
        float right = newX + Radio;
        float top = newY - Radio;
        float bottom = newY + Radio;

        return (left >= 0 && right <= ventana.getSize().x && top >= 0 && bottom <= ventana.getSize().y);
    }

public:
    Circulo(int numVertices) {
        float angulo = 0;
        float anguloIncremento = Pi * 2 / numVertices;

        // Generar los vértices y almacenar sus posiciones iniciales
        for (int i = 0; i < numVertices; ++i) {
            float x = CentroX + Radio * cos(angulo);
            float y = CentroY + Radio * sin(angulo);
            vertices.push_back(Vertex(Vector2f(x, y), Color::Black));
            initialPositions.push_back(Vector2f(x, y));
            angulo += anguloIncremento;
        }
    }

    void Dibujar(RenderWindow& ventana) override {
        CircleShape circuloShape(Radio);
        circuloShape.setFillColor(Color::Yellow);
        circuloShape.setOrigin(Radio, Radio);
        circuloShape.setPosition(CentroX, CentroY);
        circuloShape.setRotation(rotationAngle);
        ventana.clear();
        ventana.draw(circuloShape);

        // Dibujar los vértices y las líneas
        Vector2f circleCenter(CentroX, CentroY);
        float radianAngle = rotationAngle * Pi / 180;

        // Vector para almacenar las posiciones rotadas
        vector<Vector2f> rotatedPositions;

        // Calcular y dibujar los vértices rotados
        for (size_t i = 0; i < initialPositions.size(); ++i) {
            Vector2f vertexPosition = initialPositions[i] - circleCenter;
            float rotatedX = vertexPosition.x * cos(radianAngle) - vertexPosition.y * sin(radianAngle);
            float rotatedY = vertexPosition.x * sin(radianAngle) + vertexPosition.y * cos(radianAngle);
            Vector2f rotatedPosition = circleCenter + Vector2f(rotatedX, rotatedY);
            rotatedPositions.push_back(rotatedPosition);
            Vertex point(rotatedPosition, vertices[i].color);
            ventana.draw(&point, 1, Points);
        }

        // Dibujar las líneas entre los vértices rotados
        for (size_t i = 0; i < rotatedPositions.size(); ++i) {
            for (size_t j = i + 1; j < rotatedPositions.size(); ++j) {
                Vertex line[] = {
                    Vertex(rotatedPositions[i], Color::Black),
                    Vertex(rotatedPositions[j], Color::Black)
                };
                ventana.draw(line, 2, Lines);
            }
        }

        ventana.display();
    }

    void Mover(float offsetX, float offsetY, const RenderWindow& ventana) override {
        if (dentroPantalla(offsetX, offsetY, ventana)) {
            move(offsetX, offsetY);
            CentroX += offsetX;
            CentroY += offsetY;
            // Actualizar las coordenadas de los vértices
            for (auto& initialPosition : initialPositions) {
                initialPosition.x += offsetX;
                initialPosition.y += offsetY;
            }
        }
    }

    void Rotar(float angle) override {
        rotationAngle += angle;
    }

    // Función para obtener el centro del círculo
    Vector2f getCentro() const {
        return Vector2f(CentroX, CentroY);
    }
};

class InputHandler {
public:
    void handleInput(Circulo& circulo, const RenderWindow& ventana, float deltaTime) const {
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

        circulo.Rotar(50 * deltaTime); // Rotar más lento a 50 grados por segundo
    }
};

int main() {
    int numVertices;
    cout << "Ingrese el numero de vertices que tendra tu ojo de mosca: ";
    cin >> numVertices;

    RenderWindow window(VideoMode(500, 500), "Ojo de Mosca");
    Circulo Vertices(numVertices);
    InputHandler inputHandler;

    Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        inputHandler.handleInput(Vertices, window, deltaTime);
        Vertices.Dibujar(window);
    }

    return 0;
}
