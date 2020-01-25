#include "Mesh.h"
#include <errno.h>
#include <GLFW\glfw3.h>

/*
**	MESH 
*/

void divide_triangle(const std::vector<glm::vec3>& points, int divisions, std::vector<glm::vec3>& positions, std::vector<glm::vec4>& colours) {
	// IF we have more divisions to do?
	std::vector<glm::vec3> newPoints;

	if (divisions > 0) {
		// *********************************
		// Calculate new vertices to work on (Normalize each element!)
		glm::vec3 v0 = normalize(points[0]) + normalize(points[1]);
		glm::vec3 v1 = normalize(points[0]) + normalize(points[2]);
		glm::vec3 v2 = normalize(points[1]) + normalize(points[2]);

		// Divide new triangles

		newPoints = { points[0], v0, v1 };
		divide_triangle(newPoints, divisions - 1, positions, colours);

		newPoints = { points[2], v1, v2 };
		divide_triangle(newPoints, divisions - 1, positions, colours);

		newPoints = { points[1], v2, v0 };
		divide_triangle(newPoints, divisions - 1, positions, colours);

		newPoints = { v0, v2, v1 };
		divide_triangle(newPoints, divisions - 1, positions, colours);


		// *********************************
	}
	else {
		positions.insert(positions.end(), points.begin(), points.end());
		for (auto i = 0; i < 3; ++i) {
			colours.push_back(glm::vec4(0.6f, i % 2, i % 3, 1.0f));
		}
	}
}

// default constructor creates a horizontal plane or dimensions 1 x 1 centered on the origin
Mesh::Mesh()
{

	
	// Create triangle vertices
	Vertex vertices[] = { Vertex(glm::vec3(-1.0,-1.0,0.0)),
		Vertex(glm::vec3(0, 1.0, 0.0)),
		Vertex(glm::vec3(1.0, -1.0, 0.0))
	};

	// tirangle normals
	glm::vec3 normals[] = { glm::vec3(.0f, .0f, 1.0f), glm::vec3(.0f, .0f, 1.0f), glm::vec3(.0f, .0f, 1.0f) };

	// number of vertices
	m_numIndices = 3;


	//create mesh
	initMesh(vertices, normals);
}

// create mesh from a .obj file
Mesh::Mesh(const std::string& fileName)
{
	InitMesh(OBJModel(fileName).ToIndexedModel());
	initTransform();
}

Mesh::Mesh(MeshType type)
{
	Vertex vertices[36];
	glm::vec3 normals[36];

	switch (type)
	{
	case TRIANGLE:
		// Create triangle
		vertices[0] = Vertex(glm::vec3(-1.0, -1.0, 0.0));
		vertices[1] = Vertex(glm::vec3(0, 1.0, 0.0));
		vertices[2] = Vertex(glm::vec3(1.0, -1.0, 0.0));
		normals[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[1] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[2] = glm::vec3(0.0f, 1.0f, 0.0f);

		// number of vertices
		m_numIndices = 3;

		break;

	case QUAD:
		// create quad vertices
		vertices[0] = Vertex(glm::vec3(-1.0f, 0.0f, -1.0f));
		vertices[1] = Vertex(glm::vec3(1.0f, 0.0f, -1.0f));
		vertices[2] = Vertex(glm::vec3(-1.0f, 0.0f, 1.0f));
		vertices[3] = Vertex(glm::vec3(1.0f, 0.0f, -1.0f));
		vertices[4] = Vertex(glm::vec3(-1.0f, 0.0f, 1.0f));
		vertices[5] = Vertex(glm::vec3(1.0f, 0.0f, 1.0f));

		// create normals
		normals[0] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[1] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[2] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[3] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[4] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[5] = glm::vec3(0.0f, 1.0f, 0.0f);

		// number of vertices
		m_numIndices = 6;

		break;

	case CUBE:
		// create cube
		vertices[0] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[1] = Vertex(glm::vec3(1.0f, -1.0f, -1.0f));
		vertices[2] = Vertex(glm::vec3(1.0f, 1.0f, -1.0f));
		vertices[3] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[4] = Vertex(glm::vec3(1.0f, 1.0f, -1.0f));
		vertices[5] = Vertex(glm::vec3(-1.0f, 1.0f, -1.0f));
		vertices[6] = Vertex(glm::vec3(-1.0f, -1.0f, 1.0f));
		vertices[7] = Vertex(glm::vec3(1.0f, -1.0f, 1.0f));
		vertices[8] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[9] = Vertex(glm::vec3(-1.0f, -1.0f, 1.0f));
		vertices[10] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[11] = Vertex(glm::vec3(-1.0f, 1.0f, 1.0f));
		vertices[12] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[13] = Vertex(glm::vec3(1.0f, -1.0f, -1.0f));
		vertices[14] = Vertex(glm::vec3(1.0f, -1.0f, 1.0f));
		vertices[15] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[16] = Vertex(glm::vec3(1.0f, -1.0f, 1.0f));
		vertices[17] = Vertex(glm::vec3(-1.0f, -1.0f, 1.0f));
		vertices[18] = Vertex(glm::vec3(-1.0f, 1.0f, -1.0f));
		vertices[19] = Vertex(glm::vec3(1.0f, 1.0f, -1.0f));
		vertices[20] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[21] = Vertex(glm::vec3(-1.0f, 1.0f, -1.0f));
		vertices[22] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[23] = Vertex(glm::vec3(-1.0f, 1.0f, 1.0f));
		vertices[24] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[25] = Vertex(glm::vec3(-1.0f, 1.0f, -1.0f));
		vertices[26] = Vertex(glm::vec3(-1.0f, 1.0f, 1.0f));
		vertices[27] = Vertex(glm::vec3(-1.0f, -1.0f, -1.0f));
		vertices[28] = Vertex(glm::vec3(-1.0f, 1.0f, 1.0f));
		vertices[29] = Vertex(glm::vec3(-1.0f, -1.0f, 1.0f));
		vertices[30] = Vertex(glm::vec3(1.0f, -1.0f, -1.0f));
		vertices[31] = Vertex(glm::vec3(1.0f, 1.0f, -1.0f));
		vertices[32] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[33] = Vertex(glm::vec3(1.0f, -1.0f, -1.0f));
		vertices[34] = Vertex(glm::vec3(1.0f, 1.0f, 1.0f));
		vertices[35] = Vertex(glm::vec3(1.0f, -1.0f, 1.0f));

		//normals
		normals[0] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[1] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[2] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[3] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[4] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[5] = glm::vec3(0.0f, 0.0f, -1.0f);
		normals[6] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[7] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[8] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[9] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[10] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[11] = glm::vec3(0.0f, 0.0f, 1.0f);
		normals[12] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[13] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[14] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[15] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[16] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[17] = glm::vec3(0.0f, -1.0f, 0.0f);
		normals[18] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[19] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[20] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[21] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[22] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[23] = glm::vec3(0.0f, 1.0f, 0.0f);
		normals[24] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[25] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[26] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[27] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[28] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[29] = glm::vec3(-1.0f, 0.0f, 0.0f);
		normals[30] = glm::vec3(1.0f, 0.0f, 0.0f);
		normals[31] = glm::vec3(1.0f, 0.0f, 0.0f);
		normals[32] = glm::vec3(1.0f, 0.0f, 0.0f);
		normals[33] = glm::vec3(1.0f, 0.0f, 0.0f);
		normals[34] = glm::vec3(1.0f, 0.0f, 0.0f);
		normals[35] = glm::vec3(1.0f, 0.0f, 0.0f);

		// number of vertices
		m_numIndices = 36;

		m_vertices = std::vector<Vertex>(std::begin(vertices), std::end(vertices));

		for (int i = 0; i < m_vertices.size() - 1; i++)
		{
			for (int j = 0; j < m_vertices.size(); j++)
			{
				if (i != j && m_vertices[i].getCoord() == m_vertices[j].getCoord())
				{
					m_vertices.erase(m_vertices.begin() + j);
				}
			}
		}

		break;

	case SPHERE:

		const int subdivisions = 6;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec4> colours;
		// Define the initial tetrahedron - 4 points
		std::vector<glm::vec3> v{ glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.942809f, -0.333333f), glm::vec3(-0.816497f, -0.471405f, -0.333333f),
					   glm::vec3(0.816497f, -0.471405f, 0.333333f) };
		// Divide the triangles
		divide_triangle({ v[0], v[1], v[2] }, subdivisions, positions, colours);
		divide_triangle({ v[3], v[2], v[1] }, subdivisions, positions, colours);
		divide_triangle({ v[0], v[3], v[1] }, subdivisions, positions, colours);
		divide_triangle({ v[0], v[2], v[3] }, subdivisions, positions, colours);

		break;
	}

	//create mesh
	initMesh(vertices, normals);
	//initMesh(vertices, normals, sizeof(vertices));

	// create model matrix (identity)
	initTransform();
}

Mesh::~Mesh()
{
}


/* 
** INIT METHODS 
*/

// initialise transform matrices to identity
void Mesh::initTransform() {
	m_translate = glm::mat4(1.0f);
	m_rotate = glm::mat4(1.0f);
	m_scale = glm::mat4(1.0f);
}

// create mesh from vertices
void Mesh::initMesh(Vertex* vertices, glm::vec3* normals) {

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_numIndices * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

	// normal buffer
	glGenBuffers(1, &m_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_numIndices * sizeof(vertices[0]), &normals[0], GL_STATIC_DRAW);

	// vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}


// create mesh from model (typically loaded from file)
void Mesh::InitMesh(const IndexedModel& model)
{

	m_numIndices = model.indices.size();
	

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	// vertex buffer
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);

	// normal buffer
	glGenBuffers(1, &m_normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);

	// vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

// load .obj file
void Mesh::loadOBJ(const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE * stream;
	errno_t err;

	err = fopen_s(&stream, path, "r");

	if (err != 0)
	{
		printf("The file was not opened\n");
	}
	else{
		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(stream, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader
			if (strcmp(lineHeader, "v") == 0) {
				glm::vec3 vertex;
				fscanf_s(stream, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				glm::vec2 uv;
				fscanf_s(stream, "%f %f\n", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				glm::vec3 normal;
				fscanf_s(stream, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) {
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf_s(stream, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					std::cerr << "file can't be read by parser" << std::endl;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
	}
	// For each vertex of each triangle
	for (unsigned int i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

}



/*
** TRANSFORMATION METHODS
*/

// translate
void Mesh::translate(const glm::vec3 &vect) {
	m_translate = glm::translate(m_translate, vect);
}

// rotate
void Mesh::rotate(const float &angle, const glm::vec3 &vect) {
	m_rotate = glm::rotate(m_rotate, angle, vect);
}

// scale
void Mesh::scale(const glm::vec3 &vect) {
	m_scale = glm::scale(m_scale, vect);
}


