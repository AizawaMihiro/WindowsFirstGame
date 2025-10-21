#include "Model.h"
#include "Direct3D.h"

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
	bool isReffered = false;//参照されているかどうか
	for (int i = 0; i < modelList.size(); i++)
	{
		isReffered = false;
		for (int j = i; j < modelList.size(); j++)
		{
			if (modelList[i]->pFbx_ == modelList[j]->pFbx_)
			{
				isReffered = true;
				break;
			}
		}
		if (isReffered)
		{
			SAFE_DELETE(modelList[i]->pFbx_);
		}
		SAFE_DELETE(modelList[i]);
	}
	modelList.clear();
}
