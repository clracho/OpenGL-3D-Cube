#include <Cube3D/Graphics/RenderSystem/ShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

ShaderProgram::ShaderProgram(const ShaderProgramDesc& desc)
{
	// returns: program Id
	// requires: shader file path
	m_programId = glCreateProgram();
	// compile vertex and fragment shaders (using code from below):
	attach(desc.vertexShaderFilePath, ShaderType::VertexShader);
	attach(desc.fragmentShaderFilePath, ShaderType::FragmentShader);
	link();
}

ShaderProgram::~ShaderProgram()
{
	// release all shaders:
	for (ui32 i = 0; i < 2; i++) 
	{
		glDetachShader(m_programId, m_attachedShaders[i]);
		glDeleteShader(m_attachedShaders[i]);
	}
	//deallocate program created in constructor
	glDeleteProgram(m_programId);
}

ui32 ShaderProgram::getId()
{
	return m_programId;
}

void ShaderProgram::setUniformBufferSlot(const char* name, ui32 slot)
{
	ui32 index = glGetUniformBlockIndex(m_programId, name);
	glUniformBlockBinding(m_programId, index, slot);
}

void ShaderProgram::attach(const wchar_t* shaderFilePath, const ShaderType& type)
{
	// in order to pass shader code to opengl function, must pass again to string object
	std::string shaderCode;
	std::ifstream shaderStream(shaderFilePath);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf(); // at this point, entire source code of shader is stored in string stream
		shaderCode = sstr.str(); // source code of shader now in string object
		shaderStream.close(); // close file when finished
	}
	else 
	{
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " not found");
		return;
	}

	ui32 shaderId = 0; // store shader ID for future use
	if (type == ShaderType::VertexShader)
		shaderId = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::FragmentShader)
		shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// pass shader source code to opengl
	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderId, 1, &sourcePointer, NULL);
	// once source code is ready, compile with opengl compile function:
	glCompileShader(shaderId);

	// get compile errors
	i32 logLength = 0;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(shaderId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " << shaderFilePath << " compiled with errors:" << std::endl << &errorMessage[0]);
		return;
	}


	// attach opengl shader to main program object
	glAttachShader(m_programId, shaderId);
	m_attachedShaders[(ui32) type] = shaderId;

	OGL3D_INFO("OShaderProgram | " << shaderFilePath << " compiled successfully");
}

void ShaderProgram::link()
{
	// finalize program object:
	glLinkProgram(m_programId);

	// get compile errors
	i32 logLength = 0;
	glGetShaderiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		std::vector<char> errorMessage(logLength + 1);
		glGetShaderInfoLog(m_programId, logLength, NULL, &errorMessage[0]);
		OGL3D_WARNING("OShaderProgram | " <<  &errorMessage[0]);
		return;
	}
}
