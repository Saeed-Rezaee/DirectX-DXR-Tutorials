#include "Primitives.h"

//#define _USE_MATH_DEFINES
//Defined in the project
#include <cmath>

#include "../../../../_externals/glm/glm/geometric.hpp"

DirectXUtil::Primitives::Shape DirectXUtil::Primitives::createSphere(float diameter, int tessellation,
                                                                     bool uvHorizontalFlip, bool uvVerticalFlip)
{
	Shape returnSphereInfo;

	const int verticalSegments = tessellation;
	const int horizontalSegments = tessellation * 2;
	float uIncrement = 1.f / horizontalSegments;
	float vIncrement = 1.f / verticalSegments;
	const float radius = diameter / 2;

	uIncrement *= uvHorizontalFlip ? 1 : -1;
	vIncrement *= uvVerticalFlip ? 1 : -1;

	float u = uvHorizontalFlip ? 0 : 1;
	float v = uvVerticalFlip ? 0 : 1;

	// Start with a single vertex at the bottom of the sphere.
	for (int i = 0; i < horizontalSegments; i++)
	{
		u += uIncrement;

		// this.AddVertex(new Vector3(0,-1,0) * radius, new Vector3(0,-1,0), new Vector2(u, v));
		Structs::VertexPositionNormalTangentTexture vertex(
			glm::vec3(0, -1, 0) * radius,
			glm::vec3(0, -1, 0),
			glm::vec3(0),
			glm::vec2(u, v)
		);

		//Add it
		returnSphereInfo.vertexData.push_back(vertex);
	}

	// Create rings of vertices at progressively higher latitudes.
	v = uvVerticalFlip ? 0 : 1;
	for (int i = 0; i < verticalSegments - 1; i++)
	{
		const float latitude = (((i + 1) * static_cast<float>(M_PI)) / verticalSegments) - static_cast<float>(M_PI) / 2;
		u = uvHorizontalFlip ? 0 : 1;
		v += vIncrement;
		const float dy = static_cast<float>(sin(latitude));
		const float dxz = static_cast<float>(cos(latitude));

		// Create a single ring of vertices at this latitude.
		for (int j = 0; j <= horizontalSegments; j++)
		{
			const float longitude = j * static_cast<float>(M_PI) * 2 / horizontalSegments;

			const float dx = static_cast<float>(cos(longitude)) * dxz;
			const float dz = static_cast<float>(sin(longitude)) * dxz;

			const glm::vec3 normal(dx, dy, dz);

			const glm::vec2 texCoord(u, v);
			u += uIncrement;

			// this.AddVertex(normal * radius, normal, texCoord);
			Structs::VertexPositionNormalTangentTexture vertex(
				normal * radius,
				normal,
				glm::vec3(0),
				texCoord
			);

			//Add it
			returnSphereInfo.vertexData.push_back(vertex);
		}
	}

	// Finish with a single vertex at the top of the sphere.
	v = uvVerticalFlip ? 1 : 0;
	u = uvHorizontalFlip ? 0 : 1;
	for (int i = 0; i < horizontalSegments; i++)
	{
		u += uIncrement;

		// this.AddVertex(new Vector3(0,1,0) * radius, new Vector3(0,1,0), new Vector2(u, v));
		Structs::VertexPositionNormalTangentTexture vertex(
			glm::vec3(0, 1, 0) * radius,
			glm::vec3(0, 1, 0),
			glm::vec3(0),
			glm::vec2(u, v)
		);

		//Add it
		returnSphereInfo.vertexData.push_back(vertex);
	}

	// Create a fan connecting the bottom vertex to the bottom latitude ring.
	for (int i = 0; i < horizontalSegments; i++)
	{
		// this.AddIndex(i);
		returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i));

		// this.AddIndex(1 + i + horizontalSegments);
		returnSphereInfo.indexData.push_back(static_cast<unsigned short>(1 + i + horizontalSegments));

		// this.AddIndex(i + horizontalSegments);
		returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i + horizontalSegments));
	}

	// Fill the sphere body with triangles joining each pair of latitude rings.
	for (int i = 0; i < verticalSegments - 2; i++)
	{
		for (int j = 0; j < horizontalSegments; j++)
		{
			const int nextI = i + 1;
			const int nextJ = j + 1;
			const int num = horizontalSegments + 1;

			const int i1 = horizontalSegments + (i * num) + j;
			const int i2 = horizontalSegments + (i * num) + nextJ;
			const int i3 = horizontalSegments + (nextI * num) + j;
			const int i4 = i3 + 1;

			// this.AddIndex(i1);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i1));

			// this.AddIndex(i2);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i2));

			// this.AddIndex(i3);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i3));

			// this.AddIndex(i2);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i2));

			// this.AddIndex(i4);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i4));

			// this.AddIndex(i3);
			returnSphereInfo.indexData.push_back(static_cast<unsigned short>(i3));
		}
	}

	// Create a fan connecting the top vertex to the top latitude ring.
	for (int i = 0; i < horizontalSegments; i++)
	{
		// this.AddIndex(this.VerticesCount - 1 - i);
		returnSphereInfo.indexData.push_back(static_cast<unsigned short>(returnSphereInfo.vertexData.size() - 1 - i));

		// this.AddIndex(this.VerticesCount - horizontalSegments - 2 - i);
		returnSphereInfo.indexData.push_back(
			static_cast<unsigned short>(returnSphereInfo.vertexData.size() - horizontalSegments - 2 - i));

		// this.AddIndex(this.VerticesCount - horizontalSegments - 1 - i);
		returnSphereInfo.indexData.push_back(
			static_cast<unsigned short>(returnSphereInfo.vertexData.size() - horizontalSegments - 1 - i));
	}

	calculateTangentSpace(returnSphereInfo);

	return returnSphereInfo;
}

void DirectXUtil::Primitives::calculateTangentSpace(Shape& shape)
{
	const int vertexCount = shape.vertexData.size();
	const int triangleCount = shape.indexData.size() / 3;

	glm::vec3* tan1 = new glm::vec3[vertexCount * 2];
	glm::vec3* tan2 = tan1 + vertexCount;

	Structs::VertexPositionNormalTangentTexture a1, a2, a3;
	glm::vec3 v1, v2, v3;
	glm::vec2 w1, w2, w3;

	for (int a = 0; a < triangleCount; a++)
	{
		const unsigned short i1 = shape.indexData[(a * 3) + 0];
		const unsigned short i2 = shape.indexData[(a * 3) + 1];
		const unsigned short i3 = shape.indexData[(a * 3) + 2];

		a1 = shape.vertexData[i1];
		a2 = shape.vertexData[i2];
		a3 = shape.vertexData[i3];

		v1 = a1.position;
		v2 = a2.position;
		v3 = a3.position;

		w1 = a1.texCoord;
		w2 = a2.texCoord;
		w3 = a3.texCoord;

		float x1 = v2.x - v1.x;
		float x2 = v3.x - v1.x;
		float y1 = v2.y - v1.y;
		float y2 = v3.y - v1.y;
		float z1 = v2.z - v1.z;
		float z2 = v3.z - v1.z;

		float s1 = w2.x - w1.x;
		float s2 = w3.x - w1.x;
		float t1 = w2.y - w1.y;
		float t2 = w3.y - w1.y;

		const float r = 1.0F / ((s1 * t2) - (s2 * t1));
		glm::vec3 sdir(((t2 * x1) - (t1 * x2)) * r, ((t2 * y1) - (t1 * y2)) * r, ((t2 * z1) - (t1 * z2)) * r);
		glm::vec3 tdir(((s1 * x2) - (s2 * x1)) * r, ((s1 * y2) - (s2 * y1)) * r, ((s1 * z2) - (s2 * z1)) * r);

		tan1[i1] += sdir;
		tan1[i2] += sdir;
		tan1[i3] += sdir;

		tan2[i1] += tdir;
		tan2[i2] += tdir;
		tan2[i3] += tdir;
	}

	for (int a = 0; a < vertexCount; a++)
	{
		Structs::VertexPositionNormalTangentTexture vertex = shape.vertexData[a];

		const glm::vec3 n = vertex.normal;
		const glm::vec3 t = tan1[a];

		// Gram-Schmidt orthogonalize
		vertex.tangent = t - (n * glm::dot(n, t));
		vertex.tangent = glm::normalize(vertex.tangent);

		shape.vertexData[a] = vertex;
	}
}
