#include "Model.h"
#include "ModelCommon.h"
#include "TextureManager.h"
#include "WinApp.h"

#include <fstream>
#include <sstream>

#include "CalculateMath.h"

void Model::Initialize(ModelCommon* modelCommon, const std::string& directorypath, const std::string& filename)
{
	// 引数で受け取ってメンバ変数に記録する
	modelCommon_ = modelCommon;

	// --- オブジェクト読み込み ---
	modelData_ = LoadModelFile(directorypath, filename);
	if (modelData_.isAnimation) {
		LoadAnimationFile(directorypath, filename);
	}

	// 頂点データの初期化
	VertexResource();
	// マテリアルの初期化
	MaterialResource();

	// --- .objの参照しているテクスチャファイル読み込み ---
	TextureManager::GetInstance()->LoadTexture(modelData_.material.textureFilePath);
	// 読み込んだテクスチャファイルの番号を取得
	modelData_.material.textureIndex =
		TextureManager::GetInstance()->GetTextureIndexByFilePath(modelData_.material.textureFilePath);
}

void Model::Update()
{
	// --- Animationを再生 ---
	animationTime += 1.0f / 60.0f;
	// loopを判別、trueの時は最初から再生
	animationTime = std::fmod(animationTime, animation.duration);
	NodeAnimation& rootNodeAnimation = animation.nodeAnimations[modelData_.rootNode.name];
	Vector3 translate = CalculateValue(rootNodeAnimation.translate, animationTime);
	Quaternion rotate = CalculateValue(rootNodeAnimation.rotate, animationTime);
	Vector3 scale = CalculateValue(rootNodeAnimation.scale, animationTime);
	Matrix4x4 localMatrix = MakeAffineMatrix(scale, rotate, translate);

	modelData_.rootNode.localMatrix = localMatrix;
}

void Model::Draw()
{
	// --- vertexBufferViewの生成 ---
	modelCommon_->GetDxCommon()->GetCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView);

	// --- マテリアルCBufferの場所を設定 --- 
	modelCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootConstantBufferView(0, materialResource->GetGPUVirtualAddress());

	// --- SRVのDescriptorTableを設定 ---
	modelCommon_->GetDxCommon()->GetCommandList()->SetGraphicsRootDescriptorTable(2, TextureManager::GetInstance()->GetSrvHandleGPU(modelData_.material.textureFilePath));

	// --- 描画(DrawCall/ドローコール) ---
	modelCommon_->GetDxCommon()->GetCommandList()->DrawInstanced(UINT(modelData_.vertices.size()), 1, 0, 0);

}

void Model::VertexResource()
{
	// --- vertexResourceの作成 ---
	vertexResource = modelCommon_->GetDxCommon()->CreateBufferResource(sizeof(VertexData) * modelData_.vertices.size());

	// --- vertexBufferViewの作成 ---
	vertexBufferView.BufferLocation = vertexResource->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = UINT(sizeof(VertexData) * modelData_.vertices.size());
	vertexBufferView.StrideInBytes = sizeof(VertexData);

	// --- vertexDataに割り当てる ---
	vertexResource->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	memcpy(vertexData, modelData_.vertices.data(), sizeof(VertexData) * modelData_.vertices.size());

}
void Model::MaterialResource()
{
	// --- materialResourceの作成 ---
	materialResource = modelCommon_->GetDxCommon()->CreateBufferResource(sizeof(Material));

	// --- materialDataに割り当てる ---
	materialResource->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	materialData->color = { 1.0f, 1.0f, 1.0f, 1.0f };
	materialData->enableLighting = true;
	materialData->uvTransform = MakeIdentity4x4();
}

MaterialData Model::LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename)
{
	MaterialData materialData;
	std::string line;
	std::ifstream file(directoryPath + "/" + filename);
	assert(file.is_open());

	while (std::getline(file, line)) {
		std::string identifier;
		std::istringstream s(line);
		s >> identifier;

		if (identifier == "map_Kd") {
			std::string textureFilename;
			s >> textureFilename;
			materialData.textureFilePath = directoryPath + "/" + textureFilename;
		}
	}
	return materialData;
}

ModelData Model::LoadModelFile(const std::string& directoryPath, const std::string& filename)
{
	ModelData modelData;

	// --- assimpでobjを読み込む ---
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs);
	// メッシュがない場合はエラーとして出力
	assert(scene->HasMeshes());

	if (scene->mNumAnimations) {
		modelData.isAnimation = true;
	}
	else {
		modelData.isAnimation = false;
	}

	// --- meshを解析 ---
	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());
		assert(mesh->HasTextureCoords(0));

		// faceを解析
		for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
			aiFace& face = mesh->mFaces[faceIndex];
			// 三角形以外を読み込むとエラー
			assert(face.mNumIndices == 3);

			// vertexを解析
			for (uint32_t element = 0; element < face.mNumIndices; ++element) {
				uint32_t vertexIndex = face.mIndices[element];
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
				VertexData vertex;
				vertex.position = { position.x,position.y,position.z,1.0f };
				vertex.normal = { normal.x,normal.y,normal.z };
				vertex.texcoord = { texcoord.x,texcoord.y };
				// 右手->左手に変換
				vertex.position.x *= -1.0f;
				vertex.normal.x *= -1.0f;
				modelData.vertices.push_back(vertex);
			}
		}
	}

	// --- materialの解析 ---
	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			modelData.material.textureFilePath = directoryPath + "/" + textureFilePath.C_Str();
		}
		if (modelData.material.textureFilePath.empty()) {
			modelData.material.textureFilePath = "resources/images/white1x1.png";
		}
	}

	// --- rootNodeを読み込む ---
	modelData.rootNode = ReadNode(scene->mRootNode);

	return modelData;
}

Node Model::ReadNode(aiNode* node)
{
	Node result;
	aiMatrix4x4 aiLocalMatrix = node->mTransformation;
	aiLocalMatrix.Transpose();
	for (uint32_t i = 0; i < 4; ++i) {
		for (uint32_t j = 0; j < 4; ++j) {
			result.localMatrix.m[i][j] = aiLocalMatrix[i][j];
		}
	}
	result.name = node->mName.C_Str();
	result.children.resize(node->mNumChildren);
	for (uint32_t childrenIndex = 0; childrenIndex < node->mNumChildren; ++childrenIndex) {
		result.children[childrenIndex] = ReadNode(node->mChildren[childrenIndex]);
	}

	return result;
}

Animation Model::LoadAnimationFile(const std::string& directoryPath, const std::string& filename)
{
	// --- LoadAnimation ---
	Assimp::Importer importer;
	std::string filePath = directoryPath + "/" + filename;
	const aiScene* scene = importer.ReadFile(filePath.c_str(), 0);

	aiAnimation* animationAssimp = scene->mAnimations[0];
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);	// 秒に変換

	// --- NodeAnimationの解析 ---
	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; ++channelIndex) {
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];
		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];

		// translate
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; ++keyIndex) {
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { -keyAssimp.mValue.x,keyAssimp.mValue.y,keyAssimp.mValue.z };	// 右->左
			nodeAnimation.translate.push_back(keyframe);
		}

		// rotate
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; ++keyIndex) {
			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];
			KeyframeQuaternion keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond); // 秒に変換
			// 右手→左手に変換するために y, z を反転させる
			keyframe.value = Quaternion(keyAssimp.mValue.x, -keyAssimp.mValue.y, -keyAssimp.mValue.z, keyAssimp.mValue.w);
			nodeAnimation.rotate.push_back(keyframe);
		}

		// scale
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; ++keyIndex) {
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond); // 秒に変換
			keyframe.value = { keyAssimp.mValue.x, keyAssimp.mValue.y, keyAssimp.mValue.z };
			nodeAnimation.scale.push_back(keyframe);
		}
	}

	// 解析完了
	return animation;
}

Vector3 Model::CalculateValue(const std::vector<KeyframeVector3>& keyframes, float time)
{
	// 値が不明な場合はエラーを返す
	assert(!keyframes.empty());

	// キーが１つ or 時刻がキーフレーム前なら初期値を返す
	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}

	// 指定した時刻が範囲内の時、補間を行いその値を返す
	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
		// indexとnextIndexの二つのkeyframeを取得して範囲内に時刻があるか判定
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time - keyframes[index].time);
			return Lerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}

	// for文を抜けたら最後の値を返す
	return (*keyframes.rbegin()).value;
}
Quaternion Model::CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time)
{
	// 値が不明な場合はエラーを返す
	assert(!keyframes.empty());

	// キーが１つ or 時刻がキーフレーム前なら初期値を返す
	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}

	// 指定した時刻が範囲内の時、補間を行いその値を返す
	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
		// indexとnextIndexの二つのkeyframeを取得して範囲内に時刻があるか判定
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time - keyframes[index].time);
			return Slerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}

	// for文を抜けたら最後の値を返す
	return (*keyframes.rbegin()).value;
}