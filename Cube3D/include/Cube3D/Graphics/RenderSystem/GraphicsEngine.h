#pragma once
#include <Cube3D/Prerequisites.h>
#include <Cube3D/Math/OVec4.h>
#include <Cube3D/Math/ORect.h>

class GraphicsEngine
{
public:
	GraphicsEngine();
	~GraphicsEngine();
public:
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc);
	VertexArrayObjectPtr createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc);
	UniformBufferPtr createUniformBuffer(const UniformBufferDesc& desc);
	ShaderProgramPtr createShaderProgram(const ShaderProgramDesc& desc);
	TexturingProgramPtr createTexturingProgram(const TexturingProgramDesc& desc);
public:
	void clear(const OVec4& color);
	void setFaceCulling(const CullType& type); // to only show front faces
	void setWindingOrder(const WindingOrder& order);
	void setViewport(const ORect& size);
	void setVertexArrayObject(const VertexArrayObjectPtr& vao);
	void setUniformBuffer(const UniformBufferPtr& buffer, ui32 slot);
	void setShaderProgram(const ShaderProgramPtr& program);
	void setTexturingProgram(const TexturingProgramPtr& program);
	void drawTriangles(const TriangleType& triangleType, ui32 vertexCount, ui32 offset);
	void drawIndexedTriangles(const TriangleType& triangleType, ui32 indicesCount);
};

