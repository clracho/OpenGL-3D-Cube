#pragma once
#include <Cube3D/Prerequisites.h>



class UniformBuffer
{
public:
	UniformBuffer(const UniformBufferDesc& desc);
	~UniformBuffer();

	void setData(void* data);

	ui32 getId();
private:
	ui32 m_id = 0;
	ui32 m_size = 0;
};

