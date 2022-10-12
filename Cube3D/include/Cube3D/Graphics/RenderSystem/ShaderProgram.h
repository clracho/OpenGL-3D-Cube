#pragma once
#include <Cube3D/Prerequisites.h>

class ShaderProgram
{
public:
	ShaderProgram(const ShaderProgramDesc& desc);
	~ShaderProgram();
	ui32 getId();
	void setUniformBufferSlot(const char* name, ui32 slot);
private:
	void attach(const wchar_t* shaderFilePath, const ShaderType& type);
	void link();
private:
	// create suitable attribute to store program Id
	ui32 m_programId = 0;
	// array to store Ids of vertex and fragment shaders, so that we can deconstruct them
	ui32 m_attachedShaders[2] = {};
};

