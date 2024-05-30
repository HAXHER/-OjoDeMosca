#pragma once


class IRotable {
public:
    virtual void Rotar(float angulo) = 0;
    virtual ~IRotable() = default;
};