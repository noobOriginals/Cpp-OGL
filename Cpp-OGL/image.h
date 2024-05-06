#pragma once
#ifndef IMAGE_H_
#define IMAGE_H_

#include <iostream>
#include <string>
#include <vector>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
using namespace glm;

unsigned int imageGetCount();

class Image {
public:
	Image() {x = 0; y = 0; VAO = 0; VBO = 0; texID = 0; scale = 0.0f; height = 0; width = 0; modelt = models = mat4(0.0f); visible = false; nrChannels = 0;}
	Image(string path);
	void draw(GLFWwindow* window);
	void setPos(int x, int y);
	void move(int x, int y);
	void setScale(float scale);
	void show();
	void hide();
	int getHeight(bool b);
	int getWidth(bool b);
	~Image();

private:
	struct Vertex {
		vec3 pos;
		vec2 tex;
	};

	int x, y, width, height, nrChannels;
	float scale;
	bool visible;
	mat4 modelt, models;
	vector<Vertex> vertices;
	unsigned int texID, VAO, VBO;
};

#endif