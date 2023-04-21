#include "CameraG0.h"
#include "LibMath/Angle/Degree.h"

using namespace LibMath::Literal;

CameraGO::CameraGO(GameObject* p_parent) :
	GameObject(p_parent), 
	m_currentCam( Camera(this->m_globalMat, LibMath::Matrix4::perspectiveProjection(
		120_deg, 16.f / 9.f, .1f, 200.f)))
{
}

CameraGO::CameraGO(GameObject* p_parent, const LibMath::Matrix4& p_projection) :
	GameObject(p_parent), 
	m_currentCam( Camera(this->m_globalMat, p_projection))
{
}
Camera& CameraGO::GetCamera()
{
	return m_currentCam;
}

void CameraGO::UpdateMats()
{
	this->UpdateGlobalMat();
	m_currentCam.UpdateViewMat();
	m_currentCam.UpdatemViewProjMat();
}

void CameraGO::Update()
{
	this->UpdateMats();

	for (auto& child : m_children)
		child.second->Update();
}

