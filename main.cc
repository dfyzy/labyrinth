#include "person.h"
#include "player.h"

const float USE_RADIUS = 70;

GLFWwindow* window;

Player player;
Target* currentTarget = nullptr;
Target* lastTarget = nullptr;
float currentDistance = 0;

int lastX = 0, lastY = 0;

void checkProximity(float distance, Target* target, bool check) {
	if (distance < USE_RADIUS) {
		if (check && (currentTarget == nullptr || distance < currentDistance)) {
			if (currentTarget != target) {
				if (currentTarget)	currentTarget->setEnabled(false);
				target->setEnabled(true);
				currentTarget = target;
			}
			currentDistance = distance;
		}
	} else if (currentTarget == target) {
		target->setEnabled(false);
		currentTarget = nullptr;
	}
}

void Switch::collision(BoxObject* box) {
	BoxObject::collision(box);

	checkProximity(sgl::math::distance(box->getPosition(), position), this, true);
}

void Door::collision(BoxObject* box) {
	if (!opened)	BoxObject::collision(box);

	if (player.getOwn() == KEY) {
		bool current = currentTarget == this;
		bool last = lastTarget == this;

		checkProximity(sgl::math::distance(box->getPosition(), position), this, last || !opened);

		if (current && currentTarget != this)
			targ(false);
	}
}

void ItemObject::collision(BoxObject* box) {

	checkProximity(sgl::math::distance(box->getPosition(), position), this, true);
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

	player.update(sgl::Vector(x, y).normalize());
}

int main() {
	window = sgl::createFullscreenWindow("Title", false, sgl::Color(0.8f));

	glfwSetKeyCallback(window, keyCallback);

	Map map;

	PersonLoader persLoader;
	player = Player(persLoader.load({CELL_SIZE*5, 0}), &map);

	//sgl::setCameraPosition({CELL_SIZE*5});
	//sgl::setCameraScale(768/(11*CELL_SIZE));

	sgl::setUpdate(update);

	sgl::draw();
}
