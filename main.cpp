#include "person.hpp"
#include "map.hpp"

GLFWwindow* window;

SimpleVector pos {5, 0};

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if ((action == GLFW_PRESS) && (key == GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window, GL_TRUE);

	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_UP)	pos.y += 1;
		else if (key == GLFW_KEY_DOWN) pos.y -= 1;
		else if (key == GLFW_KEY_RIGHT) pos.x += 1;
		else if (key == GLFW_KEY_LEFT) pos.x -= 1;

		simpleGL::setCameraPosition(pos*CELL_SIZE);
	}
}

int main() {
	window = simpleGL::createFullscreenWindow("Title", false, SimpleColor(0.8f));

	glfwSetKeyCallback(window, keyCallback);

	simpleGL::setTextureFiltering(GL_LINEAR);

	PersonLoader persLoader;
	persLoader.load({CELL_SIZE*5, 0});

	Map map;

	simpleGL::setCameraPosition(pos*CELL_SIZE);
	//simpleGL::setCameraScale(768/(11*CELL_SIZE));

	simpleGL::draw();
}
