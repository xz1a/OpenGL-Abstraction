#ifndef _GL_RENDER_SYSTEM_H_
#define _GL_RENDER_SYSTEM_H_
#include <GL/gl3w.h>
#include "GLShader.h"
#include "GLProgram.h"
#include "GLVertexArray.h"
#include "GLTexture.h"
#include "GLFrameBuffer.h"
#include <unordered_map>
#include <memory>

typedef struct RenderOperation {
	bool indexed;
} RenderOperation;

class GLRenderSystem {
public:
	GLRenderSystem(unsigned int p_width, unsigned int p_height);

	//GL Calls
	inline void Clear(GLenum param) { glClear(param); };
	inline void Enable(GLenum p_param) { glEnable(p_param); };
	inline void Disable(GLenum p_param) { glDisable(p_param); };
	inline void SetDepthFunction(GLenum p_param) { glDepthFunc(p_param); };
	void SetClearColor(GLfloat p_r, GLfloat p_g, GLfloat p_b, GLfloat p_a);
	void SetClearColor(const glm::vec4& p_color);
	inline void Draw(GLenum p_draw_mode, GLint p_first, GLsizei p_count) { glDrawArrays(p_draw_mode, p_first, p_count); };
	inline void DrawElements(GLenum p_draw_mode, GLsizei p_count, GLenum p_type, const void* p_indices) { glDrawElements(p_draw_mode, p_count, p_type, p_indices); };
	inline void DrawArrays(GLenum p_draw_mode, GLint p_first, GLsizei p_count) { glDrawArrays(p_draw_mode, p_first, p_count); };
	inline void SetLineWidth(GLfloat p_line_width) { glLineWidth(p_line_width); };
	inline void SetCullFace(GLenum p_mode) { glCullFace(p_mode); };
	inline void SetPolygonMode(GLenum p_face, GLenum p_mode) { glPolygonMode(p_face, p_mode); };
	inline void SetPolygonOffest(GLfloat p_factor, GLfloat p_units) { glPolygonOffset(p_factor, p_units); };
	//Functions for Creating and Using Shaders
	void BindProgram(const char* p_program);
	std::shared_ptr<GLProgram> CreateProgram(const char* p_program_name, std::vector<GLShaderParameters>&& p_shaders);
	inline std::shared_ptr<GLProgram> GetProgram(const char* p_program_name) { return program_map.at(p_program_name); };
	void SetProgramUniformInteger(const char* p_program_name, const GLchar* p_uniform, int p_data);
	void SetProgramUniformFloat(const char* p_program_name, const GLchar* p_uniform, float p_data);
	void SetProgramUniformVec2(const char* p_program_name, const GLchar* p_uniform, const glm::vec2& p_data);
	void SetProgramUniformVec3(const char* p_program_name, const GLchar* p_uniform, const glm::vec3& p_data);
	void SetProgramUniformVec4(const char* p_program_name, const GLchar* p_uniform, const glm::vec4& p_data);
	void SetProgramUniformMat3(const char* p_program_name, const GLchar* p_uniform, const glm::mat3& p_data, GLboolean p_transpose);
	void SetProgramUniformMat4(const char* p_program_name, const GLchar* p_uniform, const glm::mat4& p_data, GLboolean p_transpose);

	//Functions for Buffers
	[[nodiscard]] std::shared_ptr<GLBuffer> CreateBuffer(GLenum p_buffer_type);
	[[nodiscard]] std::shared_ptr<GLBuffer> CreateBuffer(GLenum p_buffer_type, const void* p_data, size_t p_size);
	void BindBuffer(const std::shared_ptr<GLBuffer> p_buffer);

	//Functions for Vertex Array
	[[nodiscard]] std::shared_ptr<GLVertexArray> CreateVertexArray();
	[[nodiscard]] std::shared_ptr<GLVertexArray> CreateVertexArray(const std::vector<LayoutBufferParam> p_buffers);
	void BindVertexArray(const std::shared_ptr<GLVertexArray> p_vertex_array);
	void UnBindVertexArray();

	//Functions for Textures
	[[nodiscard]] std::shared_ptr<GLTexture> CreateTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths);
	void BindTexture(unsigned int p_index, std::shared_ptr<GLTexture> p_texture);
	void UnBindTexture(unsigned int p_index);

	//Functions for FrameBuffer
	[[nodiscard]] std::shared_ptr<GLFrameBuffer> CreateFrameBuffer(unsigned int p_width, unsigned int p_height, const std::vector<FrameBufferTexture>& p_textures);
	void BindFrameBuffer(const std::shared_ptr<GLFrameBuffer> p_frame_buffer);
	void UnBindFrameBuffer();
	void BindFrameBufferTextures(const std::shared_ptr<GLFrameBuffer> p_frame_buffer);
protected:
private:
	std::shared_ptr<GLTexture> current_textures[32];
	GLenum active_texture;
	std::unordered_map<const char*, std::shared_ptr<GLProgram>> program_map;
	std::unordered_map<GLenum, std::shared_ptr<GLBuffer>> current_buffers;
	const char* current_program;
	std::shared_ptr<GLVertexArray> current_vertex_array;
	std::shared_ptr<GLFrameBuffer> current_frame_buffer;
	glm::vec4 clear_color;
	unsigned int width;
	unsigned int height;
};
#endif