#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <memory>

class CameraGO : public GameObject
{
public:
	//CameraGO(GameObject*, Model*, Texture*) = delete;
	//void SetupEntity(Model* p_model, Texture* p_texture) = delete;

	CameraGO(GameObject* p_parent);
	CameraGO(GameObject* p_parent, const LibMath::Matrix4& p_projection);

	Camera& GetCamera();
	void Update() override;
	void UpdateMats();

private:
	Camera m_currentCam;
};

