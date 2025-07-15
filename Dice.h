#pragma once
#include "Quad.h"
class Dice :
    public Quad
{
    Quad* quad[6];
public:
    Dice();
    ~Dice() override;
    HRESULT Initialize() override;
    void Draw(XMMATRIX& worldMatrix) override;
    void Release();
};

