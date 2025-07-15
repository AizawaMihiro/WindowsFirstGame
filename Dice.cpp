#include "Dice.h"
#include "DirectXMath.h"

Dice::Dice()
	:Quad()
{	
}

Dice::~Dice()
{
}

HRESULT Dice::Initialize()
{
	HRESULT hr;
	VERTEX vertices[] =
	{
		//1
		{ XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(1.0f,   1.0f, -1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet( 1.0f, 1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet( 1.0f,-1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, 1.0f, -1.0f, 0.0f)},

		//6
		{ XMVectorSet(1.0f,   1.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(-1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,-1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  -1.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet( 1.0f,-1.0f, 1.0f, 0.0f)},

		//2
		{ XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,  1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,  1.0f,  1.0f, 0.0f)},
		{ XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f, -1.0f,  1.0f, 0.0f)},
		{ XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f, -1.0f, -1.0f, 0.0f)},

		//5
		{ XMVectorSet(-1.0f,  1.0f,  1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,  1.0f,  1.0f, 0.0f)},
		{ XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f,  1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, -1.0f,  1.0f, 0.0f)},

		//3
		{ XMVectorSet(-1.0f, 1.0f,-1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, 1.0f,-1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, 1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,  1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  1.0f,-1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,  1.0f,-1.0f, 0.0f)},

		//4
		{ XMVectorSet(1.0f,  -1.0f, 1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(1.0f,  -1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f), XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f) ,XMVectorSet(-1.0f, -1.0f, 1.0f, 0.0f)},
		{ XMVectorSet(-1.0f, -1.0f, -1.0f, 0.0f), XMVectorSet(1.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(-1.0f, -1.0f,-1.0f, 0.0f)},
		{ XMVectorSet(1.0f,  -1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f),XMVectorSet(1.0f,  -1.0f,-1.0f, 0.0f)},

	};
	int index[] = {
		0, 2, 3, 0, 1, 2,		//1 front
		4, 6, 7, 4, 5, 6,		//6 back
		8, 10, 11, 8, 9, 10,	//2 right
		12, 14, 15, 12, 13, 14,	//5 left
		16, 18, 19, 16, 17, 18,	//3 upper
		20, 22, 23, 20, 21, 22	//4 under
	};

	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"頂点バッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"インデックスバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"コンスタントバッファの作成に失敗しました", L"エラー", MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Assets\\Dice_6.png");

	return S_OK;
}

void Dice::Draw(XMMATRIX& worldMatrix)
{
	D3D11_MAPPED_SUBRESOURCE pdata;
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用


	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->DrawIndexed(36, 0, 0);
}

void Dice::Release()
{
	for (int i = 0; i < 6; i++)
	{
		SAFE_RELEASE(quad[i]);
	}
}
