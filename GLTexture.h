#ifndef _GL_TEXTURE_H_
#define _GL_TEXTURE_H_
#include <GL/gl3w.h>
#include <vector>
#include "stbi.h"
#include <memory>

class GLTexture {
public:
	GLTexture() {}
	GLTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths);
	~GLTexture();
	inline GLenum GetType() const { return texture_type; };
	inline GLuint GetHandle() const { return handle; };
protected:
	GLuint handle;
	GLenum texture_type;
private:
};
#endif