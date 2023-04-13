#include "GLRenderSystem.h"

GLRenderSystem::GLRenderSystem(unsigned int p_width, unsigned int p_height) {
	current_program = nullptr;
	program_map = std::unordered_map<const char*, std::shared_ptr<GLProgram>>();
	current_buffers = std::unordered_map<GLenum, std::shared_ptr<GLBuffer>>();
	width = p_width;
	height = p_height;
}

//OpenGL API Calls
void GLRenderSystem::SetClearColor(GLfloat p_r, GLfloat p_g, GLfloat p_b, GLfloat p_a) {
	if (clear_color.r == p_r && clear_color.g == p_g && clear_color.b == p_b && clear_color.a == p_a) {
		return;
	}
	glClearColor(p_r, p_g, p_b, p_a);
	clear_color = glm::vec4(p_r, p_g, p_b, p_a);
}

void GLRenderSystem::SetClearColor(const glm::vec4& p_color) {
	if (clear_color == p_color) {
		return;
	}
	glClearColor(p_color.r, p_color.g, p_color.b, p_color.a);
	clear_color = p_color;
}

//Functions for Creating and Using OpenGL Shaders
void GLRenderSystem::BindProgram(const char* p_program) {
	if (p_program != current_program) {
		if (program_map.find(p_program) == program_map.end()) {
			glUseProgram(0);
			std::cout << "Couldn't Find Selected Program." << std::endl;
		}
		else {
			std::shared_ptr<GLProgram> gl_program = program_map.at(p_program);
			glUseProgram(gl_program->GetHandle());
			current_program = p_program;
		}
	}
}

std::shared_ptr<GLProgram> GLRenderSystem::CreateProgram(const char* p_program_name, std::vector<GLShaderParameters>&& p_shaders) {
	program_map.insert(std::pair<const char*, std::shared_ptr<GLProgram>>(p_program_name, std::make_shared<GLProgram>(p_shaders)));
	return program_map.at(p_program_name);
}


//Functions for Setting Uniforms.
void GLRenderSystem::SetProgramUniformInteger(const char* p_program_name, const GLchar* p_uniform, int p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformInteger(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformFloat(const char* p_program_name, const GLchar* p_uniform, float p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformFloat(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec2(const char* p_program_name, const GLchar* p_uniform, const glm::vec2& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec2(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec3(const char* p_program_name, const GLchar* p_uniform, const glm::vec3& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec3(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformVec4(const char* p_program_name, const GLchar* p_uniform, const glm::vec4& p_data) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformVec4(p_uniform, p_data);
	}
}

void GLRenderSystem::SetProgramUniformMat3(const char* p_program_name, const GLchar* p_uniform, const glm::mat3& p_data, GLboolean p_transpose) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformMat3(p_uniform, p_data, p_transpose);
	}

}

void GLRenderSystem::SetProgramUniformMat4(const char* p_program_name, const GLchar* p_uniform, const glm::mat4& p_data, GLboolean p_transpose) {
	if (program_map.find(p_program_name) != program_map.end()) {
		program_map.at(p_program_name).get()->SetUniformMat4(p_uniform, p_data, p_transpose);
	}
}

//Functions for OpenGL Buffers.
[[nodiscard]] std::shared_ptr<GLBuffer> GLRenderSystem::CreateBuffer(GLenum p_buffer_type) {
	std::shared_ptr <GLBuffer> buffer = std::make_shared<GLBuffer>(p_buffer_type);
	return buffer;
}

[[nodiscard]] std::shared_ptr<GLBuffer> GLRenderSystem::CreateBuffer(GLenum p_buffer_type, const void* p_data, size_t p_size) {
	std::shared_ptr <GLBuffer> buffer = std::make_shared<GLBuffer>(p_buffer_type, p_data, p_size);
	return buffer;
}

void GLRenderSystem::BindBuffer(const std::shared_ptr<GLBuffer> p_buffer) {
	GLenum type = p_buffer.get()->GetType();
	if (current_buffers[type] != p_buffer) {
		glBindBuffer(type, p_buffer.get()->GetHandle());
		current_buffers[type] = p_buffer;
	}
}

//Functions for OpenGL Vertex Arrays.
[[nodiscard]] std::shared_ptr<GLVertexArray> GLRenderSystem::CreateVertexArray() {
	std::shared_ptr<GLVertexArray> vertex_array = std::make_shared<GLVertexArray>();
	return vertex_array;
}

[[nodiscard]] std::shared_ptr<GLVertexArray> GLRenderSystem::CreateVertexArray(const std::vector<LayoutBufferParam> p_buffers) {
	std::shared_ptr<GLVertexArray> vertex_array = std::make_shared<GLVertexArray>(p_buffers);

	return vertex_array;
}

void GLRenderSystem::BindVertexArray(const std::shared_ptr<GLVertexArray> p_vertex_array) {
	if (current_vertex_array != p_vertex_array) {
		current_vertex_array = p_vertex_array;
		glBindVertexArray(p_vertex_array.get()->GetHandle());
	}
}

void GLRenderSystem::UnBindVertexArray() {
	glBindVertexArray(0);
	current_vertex_array = NULL;
}

//Functions for OpenGL Textures

[[nodiscard]] std::shared_ptr<GLTexture> GLRenderSystem::CreateTexture(GLenum p_texture_type, std::vector<const char*> p_file_paths) {
	std::shared_ptr<GLTexture> texture = std::make_shared<GLTexture>(p_texture_type, p_file_paths);
	return texture;
}

void GLRenderSystem::BindTexture(unsigned int p_index, std::shared_ptr<GLTexture> p_texture) {
	current_textures[p_index] = p_texture;
	glActiveTexture(GL_TEXTURE0 + p_index);
	glBindTexture(p_texture.get()->GetType(), p_texture.get()->GetHandle());
	active_texture = GL_TEXTURE0 + p_index;
}

void GLRenderSystem::UnBindTexture(unsigned int p_index) {
	current_textures[p_index]->GetType();
}

//Functions for FrameBuffer
[[nodiscard]] std::shared_ptr<GLFrameBuffer> GLRenderSystem::CreateFrameBuffer(unsigned int p_width, unsigned int p_height, const std::vector<FrameBufferTexture>& p_textures) {
	std::shared_ptr<GLFrameBuffer> frame_buffer = std::make_shared<GLFrameBuffer>(p_width, p_height, p_textures);
	return frame_buffer;
}

void GLRenderSystem::BindFrameBuffer(const std::shared_ptr<GLFrameBuffer> p_frame_buffer) {
	if (current_frame_buffer != p_frame_buffer) {
		glViewport(0, 0, p_frame_buffer->GetWidth(), p_frame_buffer->GetHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, p_frame_buffer->GetHandle());
	}
}

void GLRenderSystem::UnBindFrameBuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, width, height);
	current_frame_buffer = NULL;
}

void GLRenderSystem::BindFrameBufferTextures(const std::shared_ptr<GLFrameBuffer> p_frame_buffer) {
	int i = 0;
	for (GLuint texture : p_frame_buffer->GetTextures()) {
		GLenum target = GL_TEXTURE0 + i;
		glActiveTexture(target);
		active_texture = target;
		glBindTexture(GL_TEXTURE_2D, texture);
		++i;
	}
}