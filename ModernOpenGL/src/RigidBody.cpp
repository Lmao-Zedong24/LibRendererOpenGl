#include "RigidBody.h"


bool ICollidable::collision(const ICollidable& p_collidable)
{
	return false;
}

SphereCollider::SphereCollider() : SphereCollider(LibMath::Vector3(0), 1.0f)
{
}

SphereCollider::SphereCollider(LibMath::Vector3 p_pos, float p_rad): 
	m_pos(p_pos), m_rad(p_rad)
{}

bool SphereCollider::collision(const ICollidable& p_collidable)
{
	if (typeid(SphereCollider) == typeid(p_collidable))
		return this->collision(*dynamic_cast<const SphereCollider*>(&p_collidable));

	return false;
}

bool SphereCollider::collision(const SphereCollider& p_sphere)
{
	return this->ShpereCollision(this->m_pos, this->m_rad, p_sphere.m_pos, p_sphere.m_rad);
}

CapsuleCollider::CapsuleCollider() : CapsuleCollider(LibMath::Vector3(0, 1, 0), LibMath::Vector3(0, -1, 0), 1.0f, LibMath::Matrix4(1))
{
}

CapsuleCollider::CapsuleCollider(const LibMath::Vector3& p_p1, const LibMath::Vector3& p_p2, float p_rad, const LibMath::Matrix4& p_mat) :
	m_mat(p_mat), m_p1(p_p1, 1), m_p2(p_p2, 1), m_rad(p_rad)
{
}

bool CapsuleCollider::collision(const ICollidable& p_collidable)
{
	if (typeid(CapsuleCollider) == typeid(p_collidable))
		return this->collision(*dynamic_cast<const CapsuleCollider*>(&p_collidable));

	return false;
}

bool CapsuleCollider::collision(const CapsuleCollider& p_capsule)
{
	//C1
	LibMath::Vector4 ptA = this->m_mat * this->m_p1;
	LibMath::Vector4 ptB = this->m_mat * this->m_p2;
	//C2
	LibMath::Vector4 ptC = p_capsule.m_mat * this->m_p1;
	LibMath::Vector4 ptD = p_capsule.m_mat * this->m_p2;

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

LibMath::Vector4 ICollidable::ClosestPointOnSegment(const LibMath::Vector4& p_A, const LibMath::Vector4& p_B, const LibMath::Vector4& p_pt)
{
	LibMath::Vector4 AB(p_B- p_A);
	float t = AB.dot(p_pt - p_A) / AB.dot(AB);

	return p_A + LibMath::clamp(t, 0, 1.0f) * AB;
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

BoxCollider::BoxCollider() : BoxCollider(LibMath::Vector3(1), LibMath::Vector3(0))
{
}

BoxCollider::BoxCollider(const LibMath::Vector3& p_dim, const LibMath::Vector3& p_pos) :
	m_dim(p_dim), m_pos(p_pos)
{
}

bool BoxCollider::collision(const ICollidable& p_collidable)
{
	if (typeid(BoxCollider) == typeid(p_collidable))
		return this->collision(*dynamic_cast<const BoxCollider*>(&p_collidable));

	return false;
}

bool BoxCollider::collision(const BoxCollider& p_box)
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

	return (this->m_pos.m_x <= p_box.m_pos.m_x ?	// X axis
				aMinMax[0][1] >= bMinMax[0][0] :	// a[X][max], b[X][min]
				bMinMax[0][1] >= aMinMax[0][0] &&	// b[X][max], a[X][min]

			this->m_pos.m_y <= p_box.m_pos.m_y ?	// Y axis
				aMinMax[1][1] >= bMinMax[1][0] :	// a[Y][max], b[Y][min]
				bMinMax[1][1] >= aMinMax[1][0] &&	// b[Y][max], a[Y][min]

			this->m_pos.m_z <= p_box.m_pos.m_z ?	// Z axis
				aMinMax[2][1] >= bMinMax[2][0] :	// a[Z][max], b[Z][min]
				bMinMax[2][1] >= aMinMax[2][0]);	// b[Z][max], a[Z][min]
}

VertCapsuleCollider::VertCapsuleCollider() : VertCapsuleCollider(2, 1, LibMath::Vector3(0))
{
}

VertCapsuleCollider::VertCapsuleCollider(float p_height, float p_rad, const LibMath::Vector3& p_pos) :
	m_height(p_height), m_rad(p_rad), m_pos(p_pos)
{
}

bool VertCapsuleCollider::collision(const ICollidable& p_collidable)
{
	if (typeid(VertCapsuleCollider) == typeid(VertCapsuleCollider))
		return this->collision(*dynamic_cast<const VertCapsuleCollider*>(&p_collidable));

	return false;
}

bool VertCapsuleCollider::collision(const VertCapsuleCollider& p_vertCapsule)
{
	const VertCapsuleCollider& C1 = this->m_pos.m_y <= p_vertCapsule.m_pos.m_y? *this : p_vertCapsule;	//lowest capsule
	const VertCapsuleCollider& C2 = &C1 == this? p_vertCapsule : *this;									//highest capsule

	if (C1.m_pos.m_y + C1.m_height / C2.m_pos.m_y - C2.m_height / 2) //if at height within range use circle collision
		return ICollidable::CircleCollision(	{ C1.m_pos.m_x, C1.m_pos.m_z }, C1.m_rad, 
												{ C2.m_pos.m_x, C2.m_pos.m_z }, C2.m_rad);

	return ICollidable::ShpereCollision(	C1.m_pos + (0, C1.m_height, 0), C1.m_rad, //use sphere collision with ends
											C2.m_pos - (0, C2.m_height, 0), C2.m_rad);
}

RigidBody::RigidBody() :
	m_onCollsionEnterFunc(RigidBody::DefaultCollision),
	m_onCollsionStayFunc(RigidBody::DefaultCollision),
	m_onCollsionExitFunc(RigidBody::DefaultCollision)
{
}

RigidBody::RigidBody(std::vector<std::unique_ptr<ICollidable>>& p_collidables, CollsionFunc p_collisionFuncs[3]) :
	m_collidable(std::move(p_collidables)), m_onCollsionEnterFunc(p_collisionFuncs[0]),
	m_onCollsionStayFunc(p_collisionFuncs[1]), m_onCollsionExitFunc(p_collisionFuncs[2])
{
}

void RigidBody::DefaultCollision(const RigidBody&)
{
}
