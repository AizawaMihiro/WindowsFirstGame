#include "Model.h"

namespace Model
{
	//���f���f�[�^���X�g
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
		//Fbx�ǂݍ���
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
	//���f���f�[�^����i���j
	for (auto& itr : modelList)
	{
		itr->pFbx_->Release();
		delete itr->pFbx_;
		delete itr;
	}
	modelList.clear();
}
