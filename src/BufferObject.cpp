#include <BufferObject.h>

BufferObject::BufferObject(GLenum target, const void* data, GLsizeiptr size, GLenum usage) {
    this->target = target;
    glGenBuffers(1, &ID);
    glBindBuffer(target, ID);
    glBufferData(target, size, data, usage);
}

void BufferObject::bind() {
    glBindBuffer(target, ID);
}

void BufferObject::unbind() {
    glBindBuffer(target, 0);
}

void BufferObject::deleteBuffer() {
    glDeleteBuffers(1, &ID);
}
