#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include "Texture.h"
#include <vector>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class Fbx
{
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMFLOAT4	diffuse;
		BOOL	materialFlag;	//マテリアルがあるかどうか
	};

	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;
	};

	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	//MATERIAL* pMaterialList_;
	//pMaterialList_をvectorで管理するためmaterialList_を追加
	std::vector<MATERIAL> pMaterialList_;
	std::vector<int> indexCount_;	//マテリアルごとのインデックス数を格納する配列

	int vertexCount_;
	int polygonCount_;
	int materialCount_;

public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();

	void InitVertex(FbxMesh* mesh);
	void InitIndex(FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(FbxNode* pNode);
};