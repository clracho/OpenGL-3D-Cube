#pragma once
#include <Cube3D/Prerequisites.h>

class VertexArrayObject
{

public:
	//constructor:
	VertexArrayObject(const VertexBufferDesc& data);
	VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	//destructor:
	~VertexArrayObject();

	ui32 getId();

	ui32 getVertexBufferSize();
	ui32 getVertexSize();

private:
	ui32 m_vertexBufferId = 0;
	ui32 m_elementBufferId = 0;
	ui32 m_vertexArrayObjectId = 0;
	VertexBufferDesc m_vertexBufferData;
};

