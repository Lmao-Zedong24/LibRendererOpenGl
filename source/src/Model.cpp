#include "Model.h"
#include "Camera.h"
#include "LibMath/Vector.h"
#include <fstream>
#include <sstream>
#include <string>
#include "VBO.h"
#include "EBO.h"

Model::Model(const std::string& p_fileName) : Transform(LibMath::Matrix4(1))
{
    SetModel(p_fileName);
}

void Model::InterpretFace(	std::istringstream& p_line,	
							const std::vector<LibMath::Vector3>& allPos,
							const std::vector<LibMath::Vector3>& allNor,
							const std::vector<LibMath::Vector2>& allUv,
							const LibMath::Vector3& offset)
{
	int v, t, n; //posIndex, uvIndex, normalIndex
	std::string strVertex;
	std::vector<int> triangleIndex;
	triangleIndex.reserve(4);

	int i = 0;
	while (p_line >> strVertex) //for each vertex in p_line
	{
		std::replace(strVertex.begin(), strVertex.end(), '/', ' ');

		std::istringstream issVertex(strVertex);
		issVertex >> v; issVertex >> t; issVertex >> n; //posIndex, uvIndex, normalIndex

		int vertexIndex = -1;
		Vertex vert{	allPos[v - static_cast<int>(offset.m_x)],
						allNor[n - static_cast<int>(offset.m_y)],
						allUv[ t - static_cast<int>(offset.m_z)] };

		for (int i = 0; i < m_vertices.size(); i++) //check if in array already
		{
			if ((m_vertices[i].m_pos == allPos[v - static_cast<int>(offset.m_x)]) &&
				(m_vertices[i].m_nor == allNor[n - static_cast<int>(offset.m_y)]) &&
				(m_vertices[i].m_pos == allUv[ t - static_cast<int>(offset.m_z)]))
			{
				vertexIndex = i;
				break;
			}
		}

		if (vertexIndex == -1) //if not in array add
		{
			m_vertices.push_back(vert);
			vertexIndex = static_cast<int>(m_vertices.size() - 1);
		}

		triangleIndex.push_back(vertexIndex); //add triangleIndex
		i++;

		if (i >= 20)
			bool b = false;
	}

	if (triangleIndex.size() >= 3) //123
	{
		this->m_indices.push_back(triangleIndex[0]);
		this->m_indices.push_back(triangleIndex[1]);
		this->m_indices.push_back(triangleIndex[2]);
	}
	if(triangleIndex.size() >= 4) //123 and 134
	{
		this->m_indices.push_back(triangleIndex[0]);
		this->m_indices.push_back(triangleIndex[2]);
		this->m_indices.push_back(triangleIndex[3]);
	}
}

bool Model::SetModel(const std::string& p_fileName)
{
	const float SCALE = 0.5f; // TODO : scale fits

	std::ifstream file;
	file.open(ModelPath + p_fileName);

	if (!file.is_open())
		return false;

	std::string line;
	std::string charac; //charac at start of line
	float f1, f2, f3;
	LibMath::Vector3 offset(1.0f); // pos/uv/norIndex offset for stack space

	std::vector<LibMath::Vector3> allPos;
	std::vector<LibMath::Vector3> allNor;
	std::vector<LibMath::Vector2> allUv;

	while (std::getline(file, line))
	{
		std::istringstream issLine(line);
		issLine >> charac;

		if (charac == "o")
		{
			offset += LibMath::Vector3(	static_cast<float>(allPos.size()),
										static_cast<float>(allNor.size()), 
										static_cast<float>(allUv.size()));	//increment offset
			allPos.clear(); 												// reset arrays
			allNor.clear();
			allUv.clear();
		}
		if (charac == "v")
		{
			issLine >> f1; issLine >> f2; issLine >> f3;
			allPos.push_back(LibMath::Vector3(f1 * SCALE, f2 * SCALE, f3 * SCALE));
			//allPos.push_back(LibMath::Vector3(f1, f2, f3));
		}
		else if (charac == "vt")
		{
			issLine >> f1; issLine >> f2;
			allUv.push_back(LibMath::Vector2(f1, f2));
		}
		else if (charac == "vn")
		{
			issLine >> f1; issLine >> f2; issLine >> f3;
			allNor.push_back(LibMath::Vector3(f1, f2, f3));
		}
		else if (charac == "f")
		{
			InterpretFace(issLine, allPos, allNor, allUv, offset);
		}
	}

	return true;
}

void Model::SetVAO()
{
	m_vao.Bind();

	VBO vbo((GLfloat*)(&m_vertices[0]), m_vertices.size() * sizeof(Vertex));
	EBO ebo((GLuint*)(&m_indices[0]), m_indices.size() * sizeof(GLuint));

	m_vao.LinkVBO(vbo, 0, 3, sizeof(Vertex), (void*)0);
	m_vao.LinkVBO(vbo, 1, 3, sizeof(Vertex), (void*)(3 * sizeof(float)));
	m_vao.LinkVBO(vbo, 2, 2, sizeof(Vertex), (void*)(6 * sizeof(float)));

	m_vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Model::Delete()
{
	m_vao.Delete();
}

void Model::Draw(Texture& p_texture, Shader& p_shader, Camera& p_camera)
{
	p_shader.Activate();
	m_vao.Bind();
	p_texture.Bind();

	
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size()), GL_UNSIGNED_INT, 0);
	m_vao.Unbind();
}

