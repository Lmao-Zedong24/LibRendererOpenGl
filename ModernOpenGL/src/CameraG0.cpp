#include "CameraG0.h"
#include "LibMath/Header/Angle/Degree.h"

using namespace LibMath::Literal;

CameraG0::CameraG0(GameObject* p_parent) :
	GameObject(p_parent), 
	m_cam( new Camera(&this->m_globalMat, LibMath::Matrix4::perspectiveProjection(
		120_deg, 16.f / 9.f, .1f, 200.f)))
{	
}

CameraG0::CameraG0(GameObject* p_parent, const LibMath::Matrix4& p_projection) :
	GameObject(p_parent), 
	m_cam( new Camera(&this->m_globalMat, p_projection))
{
}
Camera& CameraG0::GetCamera()
{
	return *m_cam;
}

void CameraG0::Update()
{
	m_cam->UpdateViewMat();
	m_cam->UpdatemViewProjMat();
}

