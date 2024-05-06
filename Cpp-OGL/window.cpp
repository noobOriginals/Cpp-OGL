#include <window.h>

unsigned int windowCount = 0;
bool callouts = true;

unsigned int windowGetCount() {
	return windowCount;
}
void windowEnableCallouts() {
	callouts = true;
}
void windowDisableCallouts() {
	callouts = false;
}

void def_framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height, string title) {
	this->title = title;

	if (callouts) {
		cout << "Creating window " << title << endl;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	address = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (address == NULL) {
		cout << "Failed to create window " << title << endl;
		if (windowCount < 1) {
			glfwTerminate();
			cout << "Terminating GLFW" << endl;
		}
	}

	glfwMakeContextCurrent(address);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		if (windowCount < 1) {
			glfwTerminate();
			cout << "Terminating GLFW" << endl;
		}
	}

	glViewport(0, 0, width, height);

	glfwSetFramebufferSizeCallback(address, def_framebuffer_size_callback);
	glfwSwapInterval(1);
	glfwSetInputMode(address, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwShowWindow(address);

	windowCount++;
}

void Window::enableVSync() {
	glfwSwapInterval(1);
}
void Window::disableVSync() {
	glfwSwapInterval(0);
}
void Window::showMouse() {
	glfwSetInputMode(address, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void Window::hideMouse() {
	glfwSetInputMode(address, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
void Window::show() {
	glfwShowWindow(address);
}
void Window::hide() {
	glfwHideWindow(address);
}
void Window::getSize(int* width, int* height) {
	glfwGetWindowSize(address, width, height);
}
GLFWwindow* Window::getAddress() {
	return address;
}
void Window::makeCurrentContext() {
	glfwMakeContextCurrent(address);
}
bool Window::shouldClose() {
	return glfwWindowShouldClose(address);
}
bool Window::keyPressed(short key) {
	return (glfwGetKey(address, key) == GLFW_PRESS);
}
bool Window::mousePressed(short button) {
	return (glfwGetMouseButton(address, button) == GLFW_PRESS);
}

void Window::setFramebufferSizeCallback(void(*func)(GLFWwindow* window, int width, int height)) {
	glfwSetFramebufferSizeCallback(address, func);
}
void Window::setCursorPosCallback(void(*func)(GLFWwindow* window, double xpos, double ypos)) {
	glfwSetCursorPosCallback(address, func);
}

void Window::flush() {
	glfwSwapBuffers(address);
	glfwPollEvents();
}

Window::~Window() {
	windowCount--;
	if (callouts) {
		cout << "Destructing window " << title << endl;
	}
	if (windowCount < 1) {
		glfwTerminate();
		cout << "Terminating GLFW" << endl;
	}
}