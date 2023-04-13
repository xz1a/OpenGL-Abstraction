#ifndef _GL_FRAME_BUFFER_H_
#define _GL_FRAME_BUFFER_H_
#include <GL/gl3w.h>
#include <vector>
#include <memory>
#include <iostream>

typedef struct FrameBufferTexture {
	unsigned int levels;
	GLenum internal_format;
	GLenum attachment_type;
} FrameBufferTexture;

class GLFrameBuffer {
public:
	GLFrameBuffer(unsigned int p_width, unsigned int p_height, const std::vector<FrameBufferTexture>& p_textures);
	~GLFrameBuffer();
	inline GLuint GetHandle() const { return handle; };
	inline const std::vector<GLuint>& GetTextures() const { return textures; };
	inline unsigned int GetWidth() const { return width; };
	inline unsigned int GetHeight() const { return height; };
protected:
private:
	std::vector<GLuint> textures;
	std::vector<GLenum> attachments;
	GLuint handle;
	//GLuint depth_handle;
	unsigned int width;
	unsigned int height;
};
#endif