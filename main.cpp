#include <simpleGL/simpleMath.hpp>

#include "person.hpp"
#include "player.hpp"

const float USE_RADIUS = 70;

GLFWwindow* window;

Player player;
Target* currentTarget = nullptr;
Target* lastTarget = nullptr;
float currentDistance = 0;

int lastX = 0, lastY = 0;

void Switch::collision(BoxObject* box) {
	BoxObject::collision(box);

	float distance = simpleMath::distance(box->getPosition(), position);
	if (distance < USE_RADIUS) {
		if (currentTarget == nullptr || distance < currentDistance) {
			currentTarget = this;
			currentDistance = distance;
		}
	} else if (currentTarget == this)	currentTarget = nullptr;
}

void Door::collision(BoxObject* box) {
	if (!opened)	BoxObject::collision(box);

	if (player.getOwn() == KEY) {
		bool current = currentTarget == this;

		float distance = simpleMath::distance(box->getPosition(), position);
		if (distance < USE_RADIUS) {
			if (currentTarget == nullptr || distance < currentDistance) {
				currentTarget = this;
				currentDistance = distance;
			}
		} else if (current) currentTarget = nullptr;

		if (current && currentTarget != this && lastTarget == this)
			targ(false);
	}
}

void ItemObject::collision(BoxObject* box) {
	float distance = simpleMath::distance(box->getPosition(), position);
	if (distance < USE_RADIUS) {
		if (currentTarget == nullptr || distance < currentDistance) {
			currentTarget = this;
			currentDistance = distance;
		}
	} else if (currentTarget == this)	currentTarget = nullptr;
}

void ItemObject::targ(bool b) {
	Item i = player.getOwn();
	player.setOwn(item);
	change(i);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GL_TRUE);
		if (key == GLFW_KEY_E && currentTarget) {
			currentTarget->targ(true);
			lastTarget = currentTarget;
		}
	}
}

void update() {
	int x, y;

	bool d = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
	bool a = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
	bool w = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
	bool s = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

	if (d && a)	x = lastX;
	else			x = d - a;

	if (w && s)	y = lastY;
	else			y = w - s;

	player.update(SimpleVector(x, y).normalize());
}

int main() {
	window = simpleGL::createFullscreenWindow("Title", false, SimpleColor(0.8f));

	glfwSetKeyCallback(window, keyCallback);

	simpleGL::setTextureFiltering(GL_LINEAR);

	Map map;

	PersonLoader persLoader;
	player = Player(persLoader.load({CELL_SIZE*5, 0}), &map);

	//simpleGL::setCameraPosition({CELL_SIZE*5});
	//simpleGL::setCameraScale(768/(11*CELL_SIZE));

	simpleGL::setUpdate(update);

	simpleGL::draw();
}
