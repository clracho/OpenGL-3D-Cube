#include <Cube3D/Graphics/RenderSystem/GraphicsEngine.h>
#include <Cube3D/Graphics/RenderSystem/VertexArrayObject.h>
#include <Cube3D/Graphics/RenderSystem/UniformBuffer.h>
#include <Cube3D/Graphics/RenderSystem/ShaderProgram.h>
#include <Cube3D/Graphics/RenderSystem/TexturingProgram.h>
#include <glad/glad.h>
#include <assert.h>
#include <stdexcept>



VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc)
{
	//creates OVertexArrayObject using OVertexArrayObject struct which defines vertices, size of vertices, and number of vertices
	return std::make_shared<VertexArrayObject>(vbDesc);
}

VertexArrayObjectPtr GraphicsEngine::createVertexArrayObject(const VertexBufferDesc& vbDesc, const IndexBufferDesc& ibDesc)
{
	return std::make_shared<VertexArrayObject>(vbDesc, ibDesc);
}

UniformBufferPtr GraphicsEngine::createUniformBuffer(const UniformBufferDesc& desc)
{
	return std::make_shared<UniformBuffer>(desc);
}

ShaderProgramPtr GraphicsEngine::createShaderProgram(const ShaderProgramDesc& desc)
{
	// similar to above
	return std::make_shared<ShaderProgram>(desc);
}

TexturingProgramPtr GraphicsEngine::createTexturingProgram(const TexturingProgramDesc& desc)
{
	// similar to above
	return std::make_shared<TexturingProgram>(desc);
}

void GraphicsEngine::clear(const OVec4& color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::setFaceCulling(const CullType& type)
{
	// culling function to cull faces that should not be rendered.
	// e.g. only show front faces.
	
	auto cullType = GL_BACK;

	if (type == CullType::FrontFace) cullType = GL_FRONT;
	else if (type == CullType::BackFace) cullType = GL_BACK;
	else if (type == CullType::Both) cullType = GL_FRONT_AND_BACK;

	glEnable(GL_CULL_FACE);
	glCullFace(cullType);
}

void GraphicsEngine::setWindingOrder(const WindingOrder& order)
{
	// setWindingOrder sets the order that vertices are rendered on an object

	auto orderType = GL_CW;

	if (order == WindingOrder::ClockWise) orderType = GL_CW;
	else if (order == WindingOrder::CounterClockWise) orderType = GL_CCW;

	glFrontFace(orderType);
}

void GraphicsEngine::setViewport(const ORect& size)
{
	// opengls viewport function:
	glViewport(size.left, size.top, size.width, size.height);
}

void GraphicsEngine::setVertexArrayObject(const VertexArrayObjectPtr& vao)
{
	glBindVertexArray(vao->getId());
}

void GraphicsEngine::setUniformBuffer(const UniformBufferPtr& buffer, ui32 slot)
{
	glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->getId());
}

void GraphicsEngine::setShaderProgram(const ShaderProgramPtr& program)
{
	// requires id of the main program in the shader program object
	glUseProgram(program->getId());
}

void GraphicsEngine::setTexturingProgram(const TexturingProgramPtr& program)
{

}

void GraphicsEngine::drawTriangles(const TriangleType& triangleType, ui32 vertexCount, ui32 offset)
{
	auto glTriType = GL_TRIANGLES;

	// sets method to be used for drawing triangles
	switch (triangleType)
	{
		// triangle list method draws triangles from consecutive 3 vertex sequences.
		case TriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; }
		// strip method places vertices from the vertex buffer one after the others, drawing triangles inbetween.
		case TriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; }
	}
	
	// GL_TRIANGLES flag indicates we want to render from a VAO that contains a list of trianges having 3 vertices
	glDrawArrays(glTriType, offset, vertexCount);
}

void GraphicsEngine::drawIndexedTriangles(const TriangleType& triangleType, ui32 indicesCount)
{
	auto glTriType = GL_TRIANGLES;

	// sets method to be used for drawing triangles
	switch (triangleType)
	{
		// triangle list method draws triangles from consecutive 3 vertex sequences.
		case TriangleType::TriangleList: {glTriType = GL_TRIANGLES; break; }
		// strip method places vertices from the vertex buffer one after the others, drawing triangles inbetween.
		case TriangleType::TriangleStrip: {glTriType = GL_TRIANGLE_STRIP; break; }
	}

	// element rendering function
	// must pass:
	//	the triangles rendering mode, 
	//	count of indices, 
	//	type of various indices
	// pointer of array of integer (nullptr since already binded with VBO)
	glDrawElements(glTriType, indicesCount, GL_UNSIGNED_INT, nullptr);
}
