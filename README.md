
# OpenGL Abstraction

Basic OpenGL API abstraction with C++ classes. This project is for me to learn to use OpenGL efficiently and will be updated as I find more things to implement.


## Some Features

- Vertex Array Object.
- Buffer Layout Description.
- OpenGL Array Buffer.
- OpenGL 2D and Skybox Textures.
- OpenGL Clear and Draw Calls.
- Uniform Location Cache.


## Usage/Examples
- Example to load a shader program.
```C++
//Initialize Render System.
GLRenderSystem gl_render_system = GLRenderSystem(); 

//Create a Program.
std::shared_ptr<GLProgram> program = gl_render_system.CreateProgram(
		"basic",
		{
			{"./shaders/basic.vertex", GL_VERTEX_SHADER},
			{"./shaders/basic.fragment", GL_FRAGMENT_SHADER}
		}
);
```
- Example to Create a VBO, VAO, and describe buffer layout.
```C++
//Create Buffer Layout Description.
GLBufferLayout layout = GLBufferLayout({
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
});

//Create Vertex Buffer Object.
std::shared_ptr<GLBuffer> vbo = gl_render_system.CreateBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));

//Create Index Buffer Object.
std::shared_ptr<GLBuffer> ibo = gl_render_system.CreateBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, sizeof(indices));


//Create Vertex Array and Bind VBO.
std::shared_ptr<GLVertexArray> vao = gl_render_system.CreateVertexArray({ {layout1, vbo}, {GLBufferLayout({}), ibo} }); // ibo has not buffer layout description so it's left as an empty declartion.
```
- Example of a Program to render a triangle.
```C++
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "GLRenderSystem.h"

const float vertices[] = {
    -1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f,  1.0f, 0.0f,
};

int main(int argc, char* argv[]) {
	if (!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "GL Sandbox", NULL, NULL);
	glfwMakeContextCurrent(window);
	gl3wInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	glm::vec3 projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	glm::vec3 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f));

  GLRenderSystem gl_render_system = GLRenderSystem();

	GLBufferLayout layout = GLBufferLayout({
		GLBufferLayoutElement {3, GL_FLOAT, false, NULL},
	});
	

  //Create Vertex Array and Bind VBO.
	std::shared_ptr<GLBuffer> vbo = gl_render_system.CreateBuffer(GL_ARRAY_BUFFER, vertices, sizeof(vertices));
	std::shared_ptr<GLVertexArray> vao = gl_render_system.CreateVertexArray(layout1, vbo);

	std::shared_ptr<GLProgram> program = gl_render_system.CreateProgram(
		"basic",
		{
			{"./shaders/basic.vertex", GL_VERTEX_SHADER},
			{"./shaders/basic.fragment", GL_FRAGMENT_SHADER}
		}
    );

    //Set Uniforms
    program.get()->SetUniformMat4("model", glm::mat4(1.0), false);
    program.get()->SetUniformMat4("view", view, false);
    program.get()->SetUniformMat4("projection", projection, false);
    
	while (!glfwWindowShouldClose(window)) {
		gl_render_system.Clear();
		gl_render_system.BindProgram("basic");
		gl_render_system.BindVertexArray(vao);
		gl_render_system.Draw(GL_TRIANGLES, 0, test_vertices.size());
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
  
	return 0;
}
```


## Dependencies
- [GLFW](https://github.com/glfw/glfw) - an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan application development.
- [GL3W](https://github.com/skaslev/gl3w) - Simple OpenGL core profile loading
- [GLM](https://github.com/g-truc/glm) - a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications.