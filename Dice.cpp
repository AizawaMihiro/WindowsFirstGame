#include "Dice.h"

Dice::Dice()
{
	for (int i = 0; i < 6; i++)
	{
		quad[i] = new Quad;
	}
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	VERTEX vertices[] =
	{
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) },   // 四角形の頂点（左上）
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) },   // 四角形の頂点（右上）
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),	XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) },   // 四角形の頂点（右下）
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) },   // 四角形の頂点（左下）
	};
	std::string filename;
	for (int i = 0; i < 6; i++)
	{
		switch (i)
		{
		case 0:
			vertices[0] = { XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(1.0f,  -1.0f, 0.0f, 0.0f),XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f),XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_1";
			break;
		case 1:
			vertices[0] = { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_2";
			break;
		case 2:
			vertices[0] = { XMVectorSet(-1.0f, 1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(-1.0f, 1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_3";
			break;
		case 3:
			vertices[0] = { XMVectorSet(1.0f,  -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(1.0f,  -1.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_4";
			break;
		case 4:
			vertices[0] = { XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_5";
			break;
		case 5:
			vertices[0] = { XMVectorSet(1.0f,   1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) };
			vertices[1] = { XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) };
			vertices[2] = { XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) };
			vertices[3] = { XMVectorSet(1.0f,  -1.0f, 2.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
			filename = "Dice_6";
			break;
		default:
			break;
		}
		hr = quad[i]->Initialize(vertices,filename);
		if (hr!=S_OK)
		{
			return hr;
		}
	}
	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	for (int i = 0; i < 6; i++)
	{
		quad[i]->Draw(worldMatrix);
	}
}

void Dice::Release()
{
	for (int i = 0; i < 6; i++)
	{
		SAFE_RELEASE(quad[i]);
	}
}
