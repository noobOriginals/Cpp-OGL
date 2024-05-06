#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <image.h>
#include <window.h>

using namespace std;

int main() {
	Window window = Window(800, 600, "OpenGL");

	Image cat = Image("cat.png");
	Image forest = Image("forest.png");

	int catSpeed = 10;

	float currentTime;
	float lastTime = 0;
	float deltaTime;

	int swidth, sheight;

	while (!window.shouldClose()) {
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		deltaTime *= 50;
		lastTime = currentTime;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.getSize(&swidth, &sheight);
		float forestSc = (swidth - forest.getWidth(false) < sheight - forest.getHeight(false)) ? (float)swidth / forest.getWidth(false) : (float)sheight / forest.getHeight(false);
		forest.setScale(forestSc);

		forest.draw(window.getAddress());

		if (window.keyPressed(GLFW_KEY_W)) {
			cat.move(0, catSpeed * deltaTime);
		}
		if (window.keyPressed(GLFW_KEY_S)) {
			cat.move(0, -catSpeed * deltaTime);
		}
		if (window.keyPressed(GLFW_KEY_A)) {
			cat.move(-catSpeed * deltaTime, 0);
		}
		if (window.keyPressed(GLFW_KEY_D)) {
			cat.move(catSpeed * deltaTime, 0);
		}

		cat.draw(window.getAddress());

		window.flush();
	}
	return 0;
}