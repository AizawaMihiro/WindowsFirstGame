#include "Model.h"

namespace Model
{
	//モデルデータリスト
	std::vector<ModelData*> modelList;
}

int Model::Load(const std::string& filename)
{
	ModelData* pModelData = new ModelData;

	pModelData->filename_ = filename;
	pModelData->pFbx_ = nullptr;

	for (auto& itr:modelList)
	{
		if (itr->filename_ == filename)
		{
			pModelData->pFbx_ = itr->pFbx_;
			break;
		}
	}

	if (pModelData->pFbx_ == nullptr)
	{
		//Fbx読み込み
		pModelData->pFbx_ = new Fbx();
		pModelData->pFbx_->Load(filename.c_str());
		modelList.push_back(pModelData);
	}
	return (int)(modelList.size() - 1);
}

void Model::SetTransform(int hModel, Transform transform)
{
	modelList[hModel]->transform_ = transform;
}

void Model::Draw(int hModel)
{
	modelList[hModel]->pFbx_->Draw(modelList[hModel]->transform_);
}

void Model::Release()
{
	//モデルデータ解放（仮）
	for (auto& itr : modelList)
	{
		itr->pFbx_->Release();
		delete itr->pFbx_;
		delete itr;
	}
	modelList.clear();
}
