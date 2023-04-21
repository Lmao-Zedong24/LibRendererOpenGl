#include "RigidBody.h"
#include "GameObject.h"


SphereCollider::SphereCollider() : SphereCollider(LibMath::Vector3(0), 1.0f)
{
}

SphereCollider::SphereCollider(LibMath::Vector3 p_pos, float p_rad): 
	m_pos(p_pos), m_rad(p_rad)
{}

bool SphereCollider::Collision(const ICollidable& p_collidable)const
{
	if (typeid(p_collidable) == typeid(SphereCollider))
		return this->CollisionSph(*dynamic_cast<const SphereCollider*>(&p_collidable));

	else if (typeid(p_collidable) == typeid(BoxCollider))
		return this->CollisionBox(*dynamic_cast<const BoxCollider*>(&p_collidable));

	return false;
}

void SphereCollider::Update(const Transform& p_tarnsform)
{
	this->m_pos = p_tarnsform.getPosition();
}

float SphereCollider::GetMin(int axis)const
{
	return m_pos[axis] - m_rad;
}

float SphereCollider::GetMax(int axis)const
{
	return m_pos[axis] + m_rad;
}

LibMath::Vector3 SphereCollider::GetCenter()const
{
	return m_pos;
}

float SphereCollider::GetRadius() const
{
	return m_rad;
}

bool SphereCollider::CollisionBox(const BoxCollider& p_box) const
{
	return p_box.CollisionSph(*this);
}

bool SphereCollider::CollisionSph(const SphereCollider& p_sphere) const
{
	return this->ShpereCollision(this->m_pos, this->m_rad, p_sphere.m_pos, p_sphere.m_rad);
}

CapsuleCollider::CapsuleCollider() : CapsuleCollider(LibMath::Vector3(0, 1, 0), LibMath::Vector3(0, -1, 0), 1.0f, LibMath::Matrix4(1))
{
}

CapsuleCollider::CapsuleCollider(const LibMath::Vector3& p_p1, const LibMath::Vector3& p_p2, float p_rad, const LibMath::Matrix4& p_mat) :
	m_mat(p_mat), m_p1(p_p1.m_x, p_p1.m_y, p_p1.m_z, 1), m_p2(p_p2.m_x, p_p2.m_y, p_p2.m_z, 1), m_rad(p_rad)
{
}

bool CapsuleCollider::Collision(const ICollidable& p_collidable)const
{
	if (typeid(CapsuleCollider) == typeid(p_collidable))
		return this->CollisionCap(*dynamic_cast<const CapsuleCollider*>(&p_collidable));
	else if (typeid(BoxCollider) == typeid(p_collidable))
		return this->CollisionBox(*dynamic_cast<const BoxCollider*>(&p_collidable));

	return false;
}

bool CapsuleCollider::CollisionCap(const CapsuleCollider& p_capsule)const
{
	//C1
	LibMath::Vector4 ptA = this->m_mat.getTransform() * this->m_p1;
	LibMath::Vector4 ptB = this->m_mat.getTransform() * this->m_p2;
	//C2
	LibMath::Vector4 ptC = p_capsule.m_mat.getTransform() * this->m_p1;
	LibMath::Vector4 ptD = p_capsule.m_mat.getTransform() * this->m_p2;

	float distSqrAC = ptA.distanceSquaredFrom(ptC);
	float distSqrAD = ptA.distanceSquaredFrom(ptD);
	float distSqrBC = ptB.distanceSquaredFrom(ptC);
	float distSqrBD = ptB.distanceSquaredFrom(ptD);

	LibMath::Vector4 bestC1, bestC2;
	if (distSqrBC < distSqrAC || distSqrBC < distSqrAD ||	//is AD closser then AC/BC
		distSqrBD < distSqrAC || distSqrBD < distSqrAD)		//is BD closser then AC/BC

		bestC1 = ptB;
	else
		bestC1 = ptA;

	bestC2 = ICollidable::ClosestPointOnSegment(ptC, ptD, bestC1);
	bestC1 = ICollidable::ClosestPointOnSegment(ptA, ptB, bestC2);

	return ICollidable::ShpereCollision(bestC1, this->m_rad, bestC2, p_capsule.m_rad);
}

bool CapsuleCollider::CollisionBox(const BoxCollider& p_box) const
{
	//Capsule pt1 and pt2
	LibMath::Vector4 c1 = (this->m_mat.getTransform() * this->m_p1);
	LibMath::Vector4 c2 = (this->m_mat.getTransform() * this->m_p2);

	//Clossest pt to box
	LibMath::Vector4 c = ICollidable::ClosestPointOnSegment(c1, c2, LibMath::Vector4(p_box.GetCenter(), 1));
	
	return p_box.Collision(SphereCollider(LibMath::Vector3(c.m_x, c.m_y, c.m_z), m_rad));
}

bool CapsuleCollider::CollisionSph(const SphereCollider& p_sph) const
{
	LibMath::Vector4 c1 = (this->m_mat.getTransform() * this->m_p1);
	LibMath::Vector4 c2 = (this->m_mat.getTransform() * this->m_p2);

	//Clossest pt to box
	LibMath::Vector4 c = ICollidable::ClosestPointOnSegment(c1, c2, LibMath::Vector4(p_sph.GetCenter(), 1));

	return p_sph.Collision(SphereCollider(LibMath::Vector3(c.m_x, c.m_y, c.m_z), m_rad));
}

void CapsuleCollider::Update(const Transform& p_tarnsform)
{
	m_mat = p_tarnsform;
}

float CapsuleCollider::GetMin(int axis) const
{
	float p1Min = (this->m_mat.getTransform() * this->m_p1)[axis] - m_rad;
	float p2Min = (this->m_mat.getTransform() * this->m_p2)[axis] - m_rad;

	if (p1Min < p2Min)
		return p1Min;

	return p2Min;
}

float CapsuleCollider::GetMax(int axis) const
{
	float p1Min = (this->m_mat.getTransform() * this->m_p1)[axis] + m_rad;
	float p2Min = (this->m_mat.getTransform() * this->m_p2)[axis] + m_rad;

	if (p1Min > p2Min)
		return p1Min;

	return p2Min;
}

LibMath::Vector3 CapsuleCollider::GetCenter() const
{
	return m_mat.getPosition();
}

LibMath::Vector4 ICollidable::ClosestPointOnSegment(const LibMath::Vector4& p_A, const LibMath::Vector4& p_B, const LibMath::Vector4& p_pt)
{
	LibMath::Vector3 AB(p_B - p_A);
	float t = AB.dot(p_pt - p_A) / AB.dot(AB);

	return LibMath::Vector4(p_A + LibMath::clamp(t, 0, 1.0f) * AB, 1);
}

bool ICollidable::ShpereCollision(const LibMath::Vector3& p_pt1, float p_r1, const LibMath::Vector3& p_pt2, float p_r2)
{
	float radSqrd = p_r1 + p_r2;
	radSqrd *= radSqrd;

	return p_pt1.distanceSquaredFrom(p_pt2) <= radSqrd;
}

bool ICollidable::CircleCollision(const LibMath::Vector2& p_pt1, float p_r1, const LibMath::Vector2& p_pt2, float p_r2)
{
	return ICollidable::ShpereCollision(static_cast<const LibMath::Vector3>(p_pt1), p_r1, 
										static_cast<const LibMath::Vector3>(p_pt2), p_r2);
}

bool ICollidable::test()
{
	LibMath::Vector3 ptA;
	LibMath::Vector3 ptB;
	LibMath::Vector3 planeNorAB = ptB - ptA;

	LibMath::Vector3 ptC;

	float projC = (ptC - ptA).dot(planeNorAB);

	//TriangleIntersect(const IvVector3 & v0, const IvVector3 & v1, const IvVector3 & v2, const IvRay & ray) 
	// {// test ray direction against 
	// triangleIvVector3 e1 = v1 - v0;
	// IvVector3 e2 = v2 - v0;
	// IvVector3 p =  ray.mDirection.Cross(e2);
	// float a = e1.Dot(p)// if result zero, no intersection or infinite intersections// (ray parallel to triangle plane)
	//T& F Cat #K23795 — “K23795_C012” — page 507 — 6 / 25 / 2015 — 17:5112.4  A Simple Collision System  507
	//if (IsZero(a))
	//return false;// compute denominator
	//float f = 1.0f/a;// compute barycentric coordinates
	//IvVector3 s = ray.mOrigin - v0;u = f*s.Dot(p)if (u < 0.0f || u > 1.0f) return false;IvVector3 q = s.Cross(e1);v = f*ray.mDirection.Dot(q);if (v < 0.0f || u+v > 1.0f) return false;// compute line parametert = f*e2.Dot(q);return (t >= 0);}
	
	//IvCapsule::Classify( const IvPlane& plane )
	//{float s0 = plane.Test( mSegment.GetEndpoint0() );
	//float s1 = plane.Test( mSegment.GetEndpoint1() );// points on opposite sides or intersecting plane
	//if (s0*s1 <= 0.0f)
	//return 0.0f;// intersect if either endpoint is within radius distance of plane
	//if( IvAbs(s0) <= mRadius || IvAbs(s1) <= mRadius )
	//	return 0.0f; 
	//return signed distance
	//return ( IvAbs(s0) < IvAbs(s1) ? s0 : s1 );}
	
	return false;
}

BoxCollider::BoxCollider() : BoxCollider(LibMath::Vector3(1), LibMath::Vector3(0))
{
}

BoxCollider::BoxCollider(const LibMath::Vector3& p_dim, const LibMath::Vector3& p_pos) :
	m_dim(p_dim), m_pos(p_pos)
{
}

bool BoxCollider::Collision(const ICollidable& p_collidable)const
{
	if (typeid(p_collidable) == typeid(BoxCollider))
		return this->CollisionBox(*dynamic_cast<const BoxCollider*>(&p_collidable));

	else if (typeid(p_collidable) == typeid(SphereCollider))
		return this->CollisionSph(*dynamic_cast<const SphereCollider*>(&p_collidable));

	else if (typeid(p_collidable) == typeid(CapsuleCollider))
		return this->CollisionCap(*dynamic_cast<const CapsuleCollider*>(&p_collidable));

	return false;
}

void BoxCollider::Update(const Transform& p_tarnsform)
{
	this->m_pos = p_tarnsform.getPosition();
}

float BoxCollider::GetMin(int axis)const
{
	return m_pos[axis] - m_dim[axis];
}

float BoxCollider::GetMax(int axis)const
{
	return m_pos[axis] + m_dim[axis];
}

LibMath::Vector3 BoxCollider::GetCenter()const
{
	return m_pos;
}

bool BoxCollider::CollisionBox(const BoxCollider& p_box) const
{
	LibMath::Vector2 aMinMax[3] //XYZ min and maxs for first box collider
	{
		LibMath::Vector2(this->m_pos.m_x - this->m_dim.m_x / 2.f, this->m_pos.m_x + this->m_dim.m_x / 2.f),
		LibMath::Vector2(this->m_pos.m_y - this->m_dim.m_y / 2.f, this->m_pos.m_y + this->m_dim.m_y / 2.f),
		LibMath::Vector2(this->m_pos.m_z - this->m_dim.m_z / 2.f, this->m_pos.m_z + this->m_dim.m_z / 2.f)
	};

	LibMath::Vector2 bMinMax[3] //XYZ min and maxs for second box collider
	{
		LibMath::Vector2(p_box.m_pos.m_x - p_box.m_dim.m_x / 2.f, p_box.m_pos.m_x + p_box.m_dim.m_x / 2.f),
		LibMath::Vector2(p_box.m_pos.m_y - p_box.m_dim.m_y / 2.f, p_box.m_pos.m_y + p_box.m_dim.m_y / 2.f),
		LibMath::Vector2(p_box.m_pos.m_z - p_box.m_dim.m_z / 2.f, p_box.m_pos.m_z + p_box.m_dim.m_z / 2.f)
	};

	if (	(this->m_pos.m_x <= p_box.m_pos.m_x ?	// X axis
				aMinMax[0][1] >= bMinMax[0][0] :	// a[X][max], b[X][min]
				bMinMax[0][1] >= aMinMax[0][0]) &&	// b[X][max], a[X][min]

			(this->m_pos.m_y <= p_box.m_pos.m_y ?	// Y axis
				aMinMax[1][1] >= bMinMax[1][0] :	// a[Y][max], b[Y][min]
				bMinMax[1][1] >= aMinMax[1][0]) &&	// b[Y][max], a[Y][min]

			(this->m_pos.m_z <= p_box.m_pos.m_z ?	// Z axis
				aMinMax[2][1] >= bMinMax[2][0] :	// a[Z][max], b[Z][min]
				bMinMax[2][1] >= aMinMax[2][0]))	// b[Z][max], a[Z][min]
	{
		return true;
	}

	return false;
}

bool BoxCollider::CollisionSph(const SphereCollider& p_sphere) const
{
	return this->Collision(BoxCollider(LibMath::Vector3(p_sphere.GetRadius()), p_sphere.GetCenter())); // TODO : make better sphere and box collider
}

bool BoxCollider::CollisionCap(const CapsuleCollider& p_cap) const
{
	return p_cap.CollisionBox(*this);
}

VertCapsuleCollider::VertCapsuleCollider() : VertCapsuleCollider(2, 1, LibMath::Vector3(0))
{
}

VertCapsuleCollider::VertCapsuleCollider(float p_height, float p_rad, const LibMath::Vector3& p_pos) :
	m_height(p_height), m_rad(p_rad), m_pos(p_pos)
{
}

bool VertCapsuleCollider::Collision(const ICollidable& p_collidable)const
{
	if (typeid(VertCapsuleCollider) == typeid(VertCapsuleCollider))
		return this->Collision(*dynamic_cast<const VertCapsuleCollider*>(&p_collidable));

	return false;
}

bool VertCapsuleCollider::Collision(const VertCapsuleCollider& p_vertCapsule)const
{
	const VertCapsuleCollider& C1 = this->m_pos.m_y <= p_vertCapsule.m_pos.m_y? *this : p_vertCapsule;	//lowest capsule
	const VertCapsuleCollider& C2 = &C1 == this? p_vertCapsule : *this;									//highest capsule

	if (C1.m_pos.m_y + C1.m_height / C2.m_pos.m_y - C2.m_height / 2) //if at height within range use circle Collision
		return ICollidable::CircleCollision(	{ C1.m_pos.m_x, C1.m_pos.m_z }, C1.m_rad, 
												{ C2.m_pos.m_x, C2.m_pos.m_z }, C2.m_rad);

	return ICollidable::ShpereCollision(	C1.m_pos + (0.0f, C1.m_height, 0.0f), C1.m_rad, //use sphere Collision with ends
											C2.m_pos - (0.0f, C2.m_height, 0.0f), C2.m_rad);
}

Collider::Collider(GameObject* p_GO) :
	m_GO(p_GO),
	m_onCollsionEnterFunc(nullptr),
	m_onCollsionStayFunc(nullptr),
	m_onCollsionExitFunc(nullptr),
	m_isActive(false)//, m_applyGravity(true)
{
}

Collider::Collider(	GameObject* p_GO, std::vector<std::unique_ptr<ICollidable>>& p_collidables, 
					CollsionFunc p_collisionFuncs[3]) :
	m_GO(p_GO), m_collidables(std::move(p_collidables)),
	m_isActive(static_cast<bool>(p_collidables.size()))//, m_applyGravity(true)
{
	this->SetCollisionFuncs(p_collisionFuncs);
}

void Collider::SetActive(bool p_active)
{
	if (!m_collidables.empty())
		m_isActive = p_active;
}

//void Collider::SetApplyGravity(bool p_gravity)
//{
//	m_applyGravity = p_gravity;
//}

void Collider::SetCollisionFuncs(CollsionFunc p_collisionFuncs[3])
{
	if (p_collisionFuncs)
	{
		if (p_collisionFuncs[0])
			m_onCollsionEnterFunc = (p_collisionFuncs[0]);

		if (p_collisionFuncs[1])
			m_onCollsionStayFunc = (p_collisionFuncs[1]);

		if (p_collisionFuncs[2])
			m_onCollsionExitFunc = (p_collisionFuncs[2]);
	}
}

void Collider::OverrideCollisionFuncs(CollsionFunc p_collisionFuncs[3])
{
	if (p_collisionFuncs)
	{
		if (p_collisionFuncs[0])
			m_onCollsionEnterFunc = (p_collisionFuncs[0]);
		else
			m_onCollsionEnterFunc = nullptr;

		if (p_collisionFuncs[1])
			m_onCollsionStayFunc = (p_collisionFuncs[1]);
		else
			m_onCollsionStayFunc = nullptr;

		if (p_collisionFuncs[2])
			m_onCollsionExitFunc = (p_collisionFuncs[2]);
		else
			m_onCollsionExitFunc = nullptr;
	}
	else
	{
		m_onCollsionEnterFunc = nullptr;
		m_onCollsionStayFunc = nullptr;
		m_onCollsionExitFunc = nullptr;
	}
}

bool Collider::CheckCollision(const Collider& p_other)
{
	return this->GetCollidables()[0].get()->Collision(*p_other.GetCollidables()[0].get());
}

void Collider::OnCollsionEnter(const Collider& p_other)
{
	if (m_onCollsionEnterFunc)
		m_onCollsionEnterFunc(p_other);
}

void Collider::OnCollsionStay(const Collider& p_other)
{
	if (m_onCollsionStayFunc)
		m_onCollsionStayFunc(p_other);
}

void Collider::OnCollsionExit(const Collider& p_other)
{
	if (m_onCollsionExitFunc)
		m_onCollsionExitFunc(p_other);
}

bool Collider::HasACollisionFunc() const
{
	return m_onCollsionEnterFunc || m_onCollsionExitFunc || m_onCollsionStayFunc;
}

bool Collider::IsActive() const
{
	return m_isActive;
}

GameObject* Collider::GetGameObj() const
{
	return m_GO;
}

void Collider::UpdateCollidables(const Transform& p_transform)
{
	for (auto& collider : m_collidables)
		collider->Update(p_transform);
}

const std::vector<std::unique_ptr<ICollidable>>& Collider::GetCollidables() const
{
	return m_collidables;
}

//void Collider::DefaultDoNothingCollision(const Collider&)
//{
//}
