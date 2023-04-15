#pragma once
#include "GameObject.h"
#include "Camera.h"

class CameraG0 : public GameObject
{
public:
	CameraG0(GameObject*, Model*, Texture*) = delete;
	void SetupEntity(Model* p_model, Texture* p_texture) = delete;

	CameraG0(GameObject* p_parent);
	CameraG0(GameObject* p_parent, const LibMath::Matrix4& p_projection);

	Camera& GetCamera();
	void Update();

private:
	Camera* m_cam;
};

