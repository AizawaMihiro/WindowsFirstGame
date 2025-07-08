#pragma once
#include "Quad.h"
class Dice :
    public Quad
{
    Quad* quad[6];
public:
    Dice();
    ~Dice();
    HRESULT Initialize();
    void Draw(XMMATRIX& worldMatrix);
    void Release();
};

