#include <image.h>

const char* vshader =
"#version 330 core\n"
"layout (location = 0) in vec3 pos;\n"
"layout (location = 1) in vec2 tex;\n"
"uniform mat4 model;\n"
"uniform vec2 screen;\n"
"out vec2 texCoords;\n"
"void main() {\n"
"	vec4 pos2 = model * vec4(pos, 1.0);\n"
"	float x = pos2.x / (screen.x);\n"
"	float y = pos2.y / (screen.y);\n"
"	texCoords = tex;\n"
"	gl_Position = vec4(x, y, 0.0, 1.0);\n"
"}\n";
const char* fshader =
"#version 330 core\n"
"out vec4 color;\n"
"in vec2 texCoords;\n"
"uniform sampler2D tex;\n"
"void main() {\n"
"	color = texture(tex, texCoords);\n"
"}\n";

unsigned int shaderID = 0;
unsigned int imageCount = 0;

void shaderInit() {
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	int success;
	char infoLog[512];

	glShaderSource(vs, 1, &vshader, NULL);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		cout << "Vertex shader compilation failed:\n" << infoLog << endl;
	}
	glShaderSource(fs, 1, &fshader, NULL);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		cout << "Fragment shader compilation failed:\n" << infoLog << endl;
	}

	shaderID = glCreateProgram();
	glAttachShader(shaderID, vs);
	glAttachShader(shaderID, fs);
	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
		cout << "Shader linking failed:\n" << infoLog << endl;
	}

	glDeleteShader(vs);
	glDeleteShader(fs);
}

Image::Image(string path) {
	x = 0;
	y = 0;
	scale = 1.0f;
	visible = true;
	modelt = mat4(1.0f);
	models = mat4(1.0f);

	if (imageCount < 1) {
		shaderInit();
	}

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data;
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	GLenum format;
	if (!data) {
		cout << "Image failed to load from " << path << endl;
		texID = 0;
		goto image;
	}
	if (nrChannels == 1) {
		format = GL_RED;
	}
	else if (nrChannels == 3) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

image:
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	Vertex vec;
	// top right
	vec.pos = vec3(width, height, 0.0f);
	vec.tex = vec2(1.0f, 1.0f);
	vertices.push_back(vec);
	// bottom right
	vec.pos = vec3(width, -height, 0.0f);
	vec.tex = vec2(1.0f, 0.0f);
	vertices.push_back(vec);
	// bottom left
	vec.pos = vec3(-width, -height, 0.0f);
	vec.tex = vec2(0.0f, 0.0f);
	vertices.push_back(vec);
	// top right
	vec.pos = vec3(width, height, 0.0f);
	vec.tex = vec2(1.0f, 1.0f);
	vertices.push_back(vec);
	// top left
	vec.pos = vec3(-width, height, 0.0f);
	vec.tex = vec2(0.0f, 1.0f);
	vertices.push_back(vec);
	// bottom left
	vec.pos = vec3(-width, -height, 0.0f);
	vec.tex = vec2(0.0f, 0.0f);
	vertices.push_back(vec);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	imageCount++;
}

void Image::show() {
	visible = true;
}
void Image::hide() {
	visible = false;
}
void Image::setPos(int x, int y) {
	modelt = glm::translate(mat4(1.0f), vec3(x * 2, y * 2, 0.0f));
	this->x = x;
	this->y = y;
}
void Image::setScale(float scale) {
	models = glm::scale(mat4(1.0f), vec3(scale, scale, 1.0f));
	this->scale = scale;
}
void Image::move(int x, int y) {
	this->x += x;
	this->y += y;
	modelt = glm::translate(modelt, vec3(x * 2, y * 2, 0.0f));
}
int Image::getHeight(bool b) {
	if (b) {
		return height * scale;
	}
	else {
		return height;
	}
}
int Image::getWidth(bool b) {
	if (b) {
		return width * scale;
	}
	else {
		return width;
	}
}

void Image::draw(GLFWwindow* window) {
	int sx, sy;
	glfwGetWindowSize(window, &sx, &sy);
	
	glUseProgram(shaderID);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, value_ptr(models * modelt));
	glUniform2f(glGetUniformLocation(shaderID, "screen"), sx, sy);

	glBindVertexArray(VAO);

	glUniform1i(glGetUniformLocation(shaderID, "tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

Image::~Image() {
	imageCount--;
	if (imageCount < 1) {
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(1, &texID);
}

unsigned int imageGetCount() {
	return imageCount;
}