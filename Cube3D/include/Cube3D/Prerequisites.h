#pragma once
#include <memory>
#include <sstream>
#include <iostream>
#include <stdexcept>

class VertexArrayObject;
class UniformBuffer;
class ShaderProgram;
class TexturingProgram;

//shared_ptr because can potentially be shared across multiple classes.
typedef std::shared_ptr<VertexArrayObject> VertexArrayObjectPtr;
typedef std::shared_ptr<UniformBuffer> UniformBufferPtr;
typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
typedef std::shared_ptr<TexturingProgram> TexturingProgramPtr;

// contains shortened keywords to use in reference to types

typedef float f32;
typedef int i32;
typedef unsigned int ui32;

struct VertexAttribute
{
	ui32 numElements = 0;
};

struct VertexBufferDesc
{
	// pointer to the list of vertices we want to use
	void* verticesList = nullptr;
	// size in bytes of the vertex
	ui32 vertexSize = 0;
	// amount of verteces inside list
	ui32 listSize = 0;

	VertexAttribute* attributesList = nullptr;
	ui32 attributesListSize = 0;
};

struct IndexBufferDesc
{
	// pointer to the list of vertices we want to use
	void* indicesList = nullptr;
	// amount of verteces inside list
	ui32 listSize = 0;
};


struct ShaderProgramDesc
{
	const wchar_t* vertexShaderFilePath;
	const wchar_t* fragmentShaderFilePath;
};

struct TexturingProgramDesc
{
	const char* textureFilePath;
};

struct UniformBufferDesc
{
	ui32 size = 0;
};

enum class TriangleType
{
	TriangleList = 0,
	TriangleStrip
};

enum class CullType
{
	BackFace = 0,
	FrontFace,
	Both
};

enum class WindingOrder
{
	ClockWise = 0,
	CounterClockWise,
};

enum class ShaderType
{
	VertexShader = 0,
	FragmentShader
};

//stringstream lets us concatenate variables, numbers into final string
#define OGL3D_ERROR(message)\
{\
std::stringstream m;\
m << "OGL3D Error: " << message << std::endl;\
throw std::runtime_error(m.str());\
}

#define OGL3D_WARNING(message)\
std::wclog << "OGL3D Warning: " << message << std::endl;



#define OGL3D_INFO(message)\
std::wclog << "OGL3D Info: " << message << std::endl;