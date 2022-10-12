#include <Cube3D/Graphics/RenderSystem/UniformBuffer.h>
#include <glad/glad.h>

UniformBuffer::UniformBuffer(const UniformBufferDesc& desc)
{
    // use gl function to generate buffers similar to vertex buffers (same function)
    glGenBuffers(1, &m_id);
    // next gl functions called will act toward buffer after binding:
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);

    glBufferData(GL_UNIFORM_BUFFER, desc.size, nullptr, GL_STATIC_DRAW);

    // unbind buffer from graphics pipeline:
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_size = desc.size;
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &m_id);
}

void UniformBuffer::setData(void* data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_id);
    // allows to update already created buffer with new data:
    glBufferSubData(GL_UNIFORM_BUFFER, 0, m_size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

ui32 UniformBuffer::getId()
{
    return m_id;
}
