#include "Fbx.h"
#include "Direct3D.h"
#include "Camera.h"
#include <filesystem>

namespace fs = std::filesystem;

Fbx::Fbx() :
	pVertexBuffer_(nullptr),
	pIndexBuffer_(nullptr),
	pConstantBuffer_(nullptr),
	vertexCount_(0),
	polygonCount_(0),
	materialCount_(0)
{
}

HRESULT Fbx::Load(std::string fileName)
{	
	//テクスチャのパスをAssetsに変更
	std::string subDir("Assets");
	fs::path  currPath, basePath;
	currPath = fs::current_path();
	basePath = currPath;
	currPath = currPath / subDir;
	//fs::path subPath(currPath.string() + "\\" + subDir);
	assert(fs::exists(currPath));//Assetsフォルダがあるか確認
	fs::current_path(currPath);

	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//メッシュ情報を取得
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//各情報の個数を取得

	vertexCount_ = mesh->GetControlPointsCount();	//頂点の数
	polygonCount_ = mesh->GetPolygonCount();	//ポリゴンの数
	materialCount_ = pNode->GetMaterialCount();	//マテリアルの数

	InitVertex(mesh);		//頂点バッファ準備
	InitIndex(mesh);		//インデックスバッファ準備
	InitConstantBuffer();	//コンスタントバッファ準備
	InitMaterial(pNode);	//マテリアル準備

	fs::current_path(basePath);	//カレントディレクトリを元に戻す

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

void Fbx::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_TYPE::SHADER_3D);
	transform.Calclation();

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = transform.GetWorldMatrix();

	//for (int i = 0; i < materialCount_; i++)
	//{
	//	if (pMaterialList_[i].pTexture)
	//	{
	//		cb.materialFlag = TRUE;
	//		cb.diffuse = XMFLOAT4(1, 1, 1, 1);
	//	}
	//	else
	//	{
	//		cb.materialFlag = FALSE;
	//		cb.diffuse = pMaterialList_[i].diffuse;
	//	}
	//}



	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	for (int i = 0; i < materialCount_; i++)
	{
		if (pMaterialList_[i].pTexture)
		{
			cb.materialFlag = TRUE;
			cb.diffuse = XMFLOAT4(1, 1, 1, 1);
		}
		else
		{
			cb.materialFlag = FALSE;
			cb.diffuse = pMaterialList_[i].diffuse;
		}

		//コンスタントバッファにデータ転送
		D3D11_MAPPED_SUBRESOURCE pdata;
		Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
		memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
		Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

		// インデックスバッファーをセット
		stride = sizeof(int);
		offset = 0;
		Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);

		//コンスタントバッファ
		Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
		Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用


		if (pMaterialList_[i].pTexture)
		{
			ID3D11SamplerState* pSampler = pMaterialList_[i].pTexture->GetSampler();
			Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

			ID3D11ShaderResourceView* pSRV = pMaterialList_[i].pTexture->GetSRV();
			Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);
		}

		Direct3D::pContext->DrawIndexed(indexCount_[i], 0, 0);
	}
	
}

void Fbx::Release()
{/*
	SAFE_RELEASE(pVertexBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pConstantBuffer_);*/
}

void Fbx::InitVertex(FbxMesh* mesh)
{
	//頂点情報を入れる配列
	VERTEX* vertices = new VERTEX[vertexCount_];

	//全ポリゴン
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3頂点分
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//調べる頂点の番号
			int index = mesh->GetPolygonVertex(poly, vertex);

			//頂点の位置
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);

			//頂点のUV
			FbxLayerElementUV* pUV = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex, FbxLayerElement::eTextureDiffuse);
			FbxVector2  uv = pUV->GetDirectArray().GetAt(uvIndex);
			vertices[index].uv = XMVectorSet((float)uv.mData[0], (float)(1.0f - uv.mData[1]), 0.0f, 0.0f);

			//頂点の法線
			FbxVector4 normal;
			mesh->GetPolygonVertexNormal(poly, vertex, normal);
			vertices[index].normal = XMVectorSet((float)normal[0], (float)normal[1], (float)normal[2], 0.0f);
		}
	}
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX)*vertexCount_;
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
}

void Fbx::InitIndex(FbxMesh* mesh)
{
	//インデックスバッファ用配列
	pIndexBuffer_ = new ID3D11Buffer*[materialCount_];

	int* index = new int[polygonCount_ * 3];
	indexCount_ = std::vector<int>(materialCount_);
	//indexCount_.resize(materialCount_);

	for (int i = 0; i < materialCount_; i++)
	{
		int count = 0;

		//全ポリゴン
		for (DWORD poly = 0; poly < polygonCount_; poly++)
		{
			//ポリゴンのマテリアル番号を取得
			FbxLayerElementMaterial* mtl = mesh->GetLayer(0)->GetMaterials();
			int mtlId = mtl->GetIndexArray().GetAt(poly);

			//マテリアル番号が同じならインデックス情報として追加
			if (mtlId == i)
			{
				//3頂点分
				for (DWORD vertex = 0; vertex < 3; vertex++)
				{
					index[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}
		}
		indexCount_[i] = count;


		// インデックスバッファを生成する
		D3D11_BUFFER_DESC   bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = index;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;
		Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_[i]);
	}
}

void Fbx::InitConstantBuffer()
{
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	// コンスタントバッファの作成
	Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
}

void Fbx::InitMaterial(FbxNode* pNode)
{
#if 0
	//配列に格納する方法	資料より
	pMaterialList_ = new MATERIAL[materialCount_];

	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();

			//ファイル名+拡張だけにする
			char name[_MAX_FNAME];	//ファイル名
			char ext[_MAX_EXT];	//拡張子
			_splitpath_s(textureFilePath, nullptr, 0, nullptr, 0, name, _MAX_FNAME, ext, _MAX_EXT);
			wsprintf(name, "%s%s", name, ext);

			//上のエラーはcharからwcharに変換していないためのもの
			//あとはLoad関数の方でカレントディレクトリの変更を行う

			//ファイルからテクスチャ作成
			pMaterialList_[i].pTexture = new Texture;
			pMaterialList_[i].pTexture->Load(name);
		}
		//テクスチャ無し
		else
		{

		}
	}

#else
	//vectorに格納する方法	陽悦先生
	pMaterialList_.resize(materialCount_);
	for (int i = 0; i < materialCount_; i++)
	{
		//i番目のマテリアル情報を取得
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//テクスチャ情報
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//テクスチャの数数
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//テクスチャあり
		if (fileTextureCount > 0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();
			fs::path tPath(textureFilePath);
			if (fs::is_regular_file(tPath))
			{
				pMaterialList_[i].pTexture = new Texture;
				pMaterialList_[i].pTexture->Load(tPath.string());
			}
			else
			{

			}
		}
		//テクスチャ無し
		else
		{
			pMaterialList_[i].pTexture = nullptr;

			//マテリアルの色を取得
			FbxDouble3 color = ((FbxSurfaceLambert*)pMaterial)->Diffuse.Get();
			pMaterialList_[i].diffuse = XMFLOAT4((float)color[0], (float)color[1], (float)color[2], 1.0f);
		}
	}

#endif // 0

}
