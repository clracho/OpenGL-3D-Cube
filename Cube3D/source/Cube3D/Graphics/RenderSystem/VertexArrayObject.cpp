#include <Cube3D/Graphics/RenderSystem/VertexArrayObject.h>
#include <glad/glad.h>
#include <stdio.h>

// code to create a VAO (VertexArrayObject) for OpenGL functions

//constructor:
VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc)
{
	if (!vbDesc.listSize) OGL3D_ERROR("VertexArrayObject | listSize is NULL");
	if (!vbDesc.vertexSize) OGL3D_ERROR("VertexArrayObject | vertexSize is NULL");
	if (!vbDesc.verticesList) OGL3D_ERROR("VertexArrayObject | verticesList is NULL");
	
	// generates vertex arrays similar to previous function
	glGenVertexArrays(1, &m_vertexArrayObjectId);
	glBindVertexArray(m_vertexArrayObjectId);

	// generates buffers
	// PARAMETERS: number of buffers (1) 
	// and         array to place the handles of generated buffers. use & operator to pass address
	glGenBuffers(1, &m_vertexBufferId);

	// bind buffer created previously as an array buffer
	glBindBuffer(GL_ARRAY_BUFFER,m_vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, vbDesc.vertexSize * vbDesc.listSize, vbDesc.verticesList, GL_STATIC_DRAW);

	// vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vbDesc.vertexSize, 0);
	glEnableVertexAttribArray(0);
	// vertex normals
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vbDesc.vertexSize, (void*)(vbDesc.attributesList[0].numElements * sizeof(f32)));
	glEnableVertexAttribArray(1);
	// vertex texture coords
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vbDesc.vertexSize, (void*)(vbDesc.attributesList[2].numElements * sizeof(f32)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	


	m_vertexBufferData = vbDesc;
}

VertexArrayObject::VertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc):VertexArrayObject(vbDesc)
{
	if (!ibDesc.listSize) OGL3D_ERROR("OVertexArrayObject | listSize is NULL");
	if (!ibDesc.indicesList) OGL3D_ERROR("OVertexArrayObject | indicesList is NULL");

	// generates vertex arrays similar to previous function
	glBindVertexArray(m_vertexArrayObjectId);

	// generates buffers
	// PARAMETERS: number of buffers (1) 
	// and         array to place the handles of generated buffers. use & operator to pass address
	glGenBuffers(1, &m_elementBufferId);

	// bind buffer created previously as an array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibDesc.listSize, ibDesc.indicesList, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

//destructor:
VertexArrayObject::~VertexArrayObject()
{
	glDeleteBuffers(1, &m_elementBufferId);
	glDeleteBuffers(1, &m_vertexBufferId);
	glDeleteVertexArrays(1, &m_vertexArrayObjectId);
}

ui32 VertexArrayObject::getId()
{
	return m_vertexArrayObjectId;
}

ui32 VertexArrayObject::getVertexBufferSize()
{
	return m_vertexBufferData.listSize;
}

ui32 VertexArrayObject::getVertexSize()
{
	return m_vertexBufferData.vertexSize;
}
