//I'm not proud of all of this

#ifndef MAP_H
#define MAP_H

#include <simpleGL/lighting.h>
#include <simpleGL/shaderData.h>

#include "door.h"
#include "switch.h"
#include "wire.h"
#include "adder.h"
#include "item.h"

const float HALF_PI = 1.57079632679f;

const float WALL_WIDTH = 13;
const float DOOR_LENGTH = 60;

const float CELL_SIZE = 250;
const float ROOM_MARGIN = 10;

const float ROOM_OFFSET = CELL_SIZE/2 - ROOM_MARGIN - WALL_WIDTH/2;
const float REAL_CELL_SIZE = CELL_SIZE - 2*ROOM_MARGIN;

const float SIDE_LEN = (REAL_CELL_SIZE - DOOR_LENGTH)/2;
const float SIDE_OFFSET = CELL_SIZE/2 - ROOM_MARGIN - SIDE_LEN/2;

const float OFF_Y = (CELL_SIZE - ROOM_MARGIN)/2;

const float CORR_OFFSET = (DOOR_LENGTH + WALL_WIDTH)/2;

const float CORR_SMALL_LEN = (CELL_SIZE - DOOR_LENGTH)/2;
const float CORR_SMALL_OFFSET = (CELL_SIZE - CORR_SMALL_LEN)/2;

const float CORR_BIG_LEN = (CELL_SIZE + DOOR_LENGTH)/2 + WALL_WIDTH;
const float CORR_BIG_OFFSET = (CELL_SIZE - CORR_BIG_LEN)/2;

const float FOG_LEN = CORR_SMALL_LEN - WALL_WIDTH;
const float FOG_OFFSET = (CELL_SIZE - FOG_LEN)/2;

const float SWITCH_MARGIN = 5;
const float SWITCH_BIG_OFFSET = ROOM_OFFSET - (WALL_WIDTH + SWITCH_SIZE)/2 - SWITCH_MARGIN;
const float SWITCH_SMALL_OFFSET = (DOOR_LENGTH - SWITCH_SIZE)/2 - SWITCH_MARGIN;

const float WIRE_MARGIN = 5;

const float TORCH_MARGIN = 5;

const float TORCH_BIG_OFFSET = ROOM_OFFSET - WALL_WIDTH/2 - TORCH_MARGIN;
const float TORCH_SMALL_OFFSET = DOOR_LENGTH/2 - TORCH_MARGIN;

class Map {
private:
	enum Direction { NORTH, WEST, SOUTH, EAST };

	sgl::Lighting* light = new sgl::Lighting(sgl::Data().position({5*CELL_SIZE}), -50, 11*CELL_SIZE, 11*CELL_SIZE, {0});
	GLuint lampShader = sgl::loadShaderSource(sgl::shaderData::getLightingPow2Fragment(), GL_FRAGMENT_SHADER);

	SwitchLoader switchLoader;
	WireLoader wireLoader;
	AdderLoader adderLoader;
	ItemLoader itemLoader;

	std::list<BoxObject*> objects;

	sgl::Vector cursor;

	inline void wall(sgl::Vector position, bool vert, float length) {
		sgl::Vector bounds{vert ? sgl::Vector(WALL_WIDTH, length) : sgl::Vector(length, WALL_WIDTH)};
		objects.push_back(new BoxObject(bounds, position, 10, {0.2f}));
		new sgl::Lighting::Shadow(light, bounds, sgl::Data().position(position));
	}

	inline void fog(sgl::Vector position, sgl::Vector bounds) {
		new sgl::Sprite(bounds, sgl::Data().position(position).color({0}), -100);
	}

	inline void empty(sgl::Vector pos) {
		fog(pos*CELL_SIZE, {CELL_SIZE});
	}

	void room1(sgl::Vector pos, Direction dir) {
		pos *= CELL_SIZE;

		bool vert = dir == NORTH || dir == SOUTH;
		float rot = HALF_PI*dir;

		wall(pos + sgl::Vector(-ROOM_OFFSET, 0).rotate(rot), vert, REAL_CELL_SIZE - 2*WALL_WIDTH);
		wall(pos + sgl::Vector(ROOM_OFFSET, 0).rotate(rot), vert, REAL_CELL_SIZE - 2*WALL_WIDTH);
		wall(pos + sgl::Vector(0, -ROOM_OFFSET).rotate(rot), !vert, REAL_CELL_SIZE);

		wall(pos + sgl::Vector(-SIDE_OFFSET, ROOM_OFFSET).rotate(rot), !vert, SIDE_LEN);
		wall(pos + sgl::Vector(SIDE_OFFSET, ROOM_OFFSET).rotate(rot), !vert, SIDE_LEN);

		wall(pos + sgl::Vector(-CORR_OFFSET, OFF_Y).rotate(rot), vert, ROOM_MARGIN);
		wall(pos + sgl::Vector(CORR_OFFSET, OFF_Y).rotate(rot), vert, ROOM_MARGIN);

		fog(pos + sgl::Vector(OFF_Y, 0).rotate(rot), sgl::Vector(ROOM_MARGIN, CELL_SIZE).rotate(rot));
		fog(pos + sgl::Vector(-OFF_Y, 0).rotate(rot), sgl::Vector(ROOM_MARGIN, CELL_SIZE).rotate(rot));
		fog(pos + sgl::Vector(0, -OFF_Y).rotate(rot), sgl::Vector(CELL_SIZE, ROOM_MARGIN).rotate(rot));
		fog(pos + sgl::Vector(FOG_OFFSET, OFF_Y).rotate(rot), sgl::Vector(FOG_LEN, ROOM_MARGIN).rotate(rot));
		fog(pos + sgl::Vector(-FOG_OFFSET, OFF_Y).rotate(rot), sgl::Vector(FOG_LEN, ROOM_MARGIN).rotate(rot));
	}

	void room2horiz(sgl::Vector pos) {
		pos *= CELL_SIZE;

		wall(pos - sgl::Vector(ROOM_OFFSET, 0), true, REAL_CELL_SIZE - 2*WALL_WIDTH);
		wall(pos + sgl::Vector(ROOM_OFFSET, 0), true, REAL_CELL_SIZE - 2*WALL_WIDTH);

		wall(pos - sgl::Vector(SIDE_OFFSET, ROOM_OFFSET), false, SIDE_LEN);
		wall(pos - sgl::Vector(-SIDE_OFFSET, ROOM_OFFSET), false, SIDE_LEN);
		wall(pos + sgl::Vector(-SIDE_OFFSET, ROOM_OFFSET), false, SIDE_LEN);
		wall(pos + sgl::Vector(SIDE_OFFSET, ROOM_OFFSET), false, SIDE_LEN);

		wall(pos - sgl::Vector(CORR_OFFSET, OFF_Y), true, ROOM_MARGIN);
		wall(pos - sgl::Vector(-CORR_OFFSET, OFF_Y), true, ROOM_MARGIN);
		wall(pos + sgl::Vector(-CORR_OFFSET, OFF_Y), true, ROOM_MARGIN);
		wall(pos + sgl::Vector(CORR_OFFSET, OFF_Y), true, ROOM_MARGIN);

		fog(pos + sgl::Vector(OFF_Y, 0), {ROOM_MARGIN, CELL_SIZE});
		fog(pos + sgl::Vector(-OFF_Y, 0), {ROOM_MARGIN, CELL_SIZE});
		fog(pos + sgl::Vector(FOG_OFFSET, OFF_Y), {FOG_LEN, ROOM_MARGIN});
		fog(pos + sgl::Vector(FOG_OFFSET, -OFF_Y), {FOG_LEN, ROOM_MARGIN});
		fog(pos + sgl::Vector(-FOG_OFFSET, OFF_Y), {FOG_LEN, ROOM_MARGIN});
		fog(pos + sgl::Vector(-FOG_OFFSET, -OFF_Y), {FOG_LEN, ROOM_MARGIN});
	}

	void corridor1(sgl::Vector pos, Direction dir) {
		pos *= CELL_SIZE;

		bool vert = dir == NORTH || dir == SOUTH;
		float rot = HALF_PI*dir;

		wall(pos + sgl::Vector(CORR_OFFSET, CORR_BIG_OFFSET).rotate(rot), vert, CORR_BIG_LEN);
		wall(pos + sgl::Vector(-CORR_OFFSET, CORR_BIG_OFFSET).rotate(rot), vert, CORR_BIG_LEN);

		wall(pos + sgl::Vector(0, -CORR_OFFSET).rotate(rot), !vert, DOOR_LENGTH + 2*WALL_WIDTH);

		fog(pos + sgl::Vector(FOG_OFFSET, 0).rotate(rot), sgl::Vector(FOG_LEN, CELL_SIZE).rotate(rot));
		fog(pos + sgl::Vector(-FOG_OFFSET, 0).rotate(rot), sgl::Vector(FOG_LEN, CELL_SIZE).rotate(rot));
		fog(pos + sgl::Vector(0, -FOG_OFFSET).rotate(rot), sgl::Vector(DOOR_LENGTH + 2*WALL_WIDTH, FOG_LEN).rotate(rot));
	}

	void corridor2(sgl::Vector pos, bool vert) {
		pos *= CELL_SIZE;

		sgl::Vector offset;
		sgl::Vector fogOff;
		sgl::Vector fogBounds;

		if (vert) {
			offset = sgl::Vector(CORR_OFFSET, 0);
			fogOff = sgl::Vector(FOG_OFFSET, 0);
			fogBounds = sgl::Vector(FOG_LEN, CELL_SIZE);
		} else {
			offset = sgl::Vector(0, CORR_OFFSET);
			fogOff = sgl::Vector(0, FOG_OFFSET);
			fogBounds = sgl::Vector(CELL_SIZE, FOG_LEN);
		}

		wall(pos - offset, vert, CELL_SIZE);
		wall(pos + offset, vert, CELL_SIZE);

		fog(pos - fogOff, fogBounds);
		fog(pos + fogOff, fogBounds);
	}

	void corridorG(sgl::Vector pos, Direction dir) {
		pos *= CELL_SIZE;

		sgl::Vector factor(1);
		if (dir != NORTH) {
			if (dir != EAST)	factor.y = -1;
			if (dir != WEST)	factor.x = -1;
		}

		wall(pos + factor*sgl::Vector(-CORR_SMALL_OFFSET, CORR_OFFSET), false, CORR_SMALL_LEN);
		wall(pos + factor*sgl::Vector(-CORR_BIG_OFFSET, -CORR_OFFSET), false, CORR_BIG_LEN);

		wall(pos + factor*sgl::Vector(-CORR_OFFSET, CORR_SMALL_OFFSET), true, CORR_SMALL_LEN);
		wall(pos + factor*sgl::Vector(CORR_OFFSET, CORR_BIG_OFFSET), true, CORR_BIG_LEN);

		fog(pos + factor*sgl::Vector(-FOG_OFFSET, FOG_OFFSET), {FOG_LEN});
		fog(pos + factor*sgl::Vector(FOG_OFFSET, 0), {FOG_LEN, CELL_SIZE});
		fog(pos + factor*sgl::Vector(0, -FOG_OFFSET), {CELL_SIZE, FOG_LEN});
	}

	void corridor3(sgl::Vector pos, Direction dir) {
		pos *= CELL_SIZE;

		bool vert = dir == NORTH || dir == SOUTH;
		float rot = HALF_PI*dir;

		wall(pos + sgl::Vector(0, CORR_OFFSET).rotate(rot), !vert, CELL_SIZE);

		wall(pos + sgl::Vector(CORR_SMALL_OFFSET, -CORR_OFFSET).rotate(rot), !vert, CORR_SMALL_LEN);
		wall(pos + sgl::Vector(-CORR_SMALL_OFFSET, -CORR_OFFSET).rotate(rot), !vert, CORR_SMALL_LEN);

		wall(pos + sgl::Vector(CORR_OFFSET, -CORR_SMALL_OFFSET).rotate(rot), vert, CORR_SMALL_LEN);
		wall(pos + sgl::Vector(-CORR_OFFSET, -CORR_SMALL_OFFSET).rotate(rot), vert, CORR_SMALL_LEN);

		fog(pos + sgl::Vector(FOG_OFFSET, -FOG_OFFSET).rotate(rot), {FOG_LEN});
		fog(pos + sgl::Vector(-FOG_OFFSET, -FOG_OFFSET).rotate(rot), {FOG_LEN});
		fog(pos + sgl::Vector(0, FOG_OFFSET).rotate(rot), sgl::Vector(CELL_SIZE, FOG_LEN).rotate(rot));
	}

	void corridor4(sgl::Vector pos) {
		pos *= CELL_SIZE;

		wall(pos + sgl::Vector(CORR_SMALL_OFFSET, -CORR_OFFSET), false, CORR_SMALL_LEN);
		wall(pos + sgl::Vector(CORR_SMALL_OFFSET, CORR_OFFSET), false, CORR_SMALL_LEN);
		wall(pos + sgl::Vector(-CORR_SMALL_OFFSET, -CORR_OFFSET), false, CORR_SMALL_LEN);
		wall(pos + sgl::Vector(-CORR_SMALL_OFFSET, CORR_OFFSET), false, CORR_SMALL_LEN);

		wall(pos - sgl::Vector(CORR_OFFSET, CORR_SMALL_OFFSET), true, CORR_SMALL_LEN);
		wall(pos - sgl::Vector(-CORR_OFFSET, CORR_SMALL_OFFSET), true, CORR_SMALL_LEN);
		wall(pos - sgl::Vector(CORR_OFFSET, -CORR_SMALL_OFFSET), true, CORR_SMALL_LEN);
		wall(pos - sgl::Vector(-CORR_OFFSET, -CORR_SMALL_OFFSET), true, CORR_SMALL_LEN);

		fog(pos + sgl::Vector(FOG_OFFSET, FOG_OFFSET), {FOG_LEN});
		fog(pos + sgl::Vector(FOG_OFFSET, -FOG_OFFSET), {FOG_LEN});
		fog(pos + sgl::Vector(-FOG_OFFSET, FOG_OFFSET), {FOG_LEN});
		fog(pos + sgl::Vector(-FOG_OFFSET, -FOG_OFFSET), {FOG_LEN});
	}

	Door* door(sgl::Vector pos, Direction dir, bool longOffset) {
		pos *= CELL_SIZE;

		bool vert = dir == WEST || dir == EAST;

		sgl::Vector bounds {vert ? sgl::Vector(WALL_WIDTH, DOOR_LENGTH) : sgl::Vector(DOOR_LENGTH, WALL_WIDTH)};

		Door* res = new Door(
			BoxObject(
				bounds,
				pos + sgl::Vector(0, longOffset ? ROOM_OFFSET : CORR_OFFSET).rotate(HALF_PI*dir),
				0,
				{0, 0, 1}
			)
		);
		objects.push_back(res);

		new sgl::Lighting::Shadow(light, bounds, sgl::Data().parent(res->getSprite()));

		return res;
	}

	Switch* swtch(sgl::Vector pos, sgl::Vector offset, bool type) {
		Switch* res = new Switch(switchLoader.load(pos*CELL_SIZE + offset), type);
		objects.push_back(res);
		return res;
	}

	Wire* wire(bool vert, float length) {
		Wire* result = new Wire(wireLoader.load(cursor+(vert? sgl::Vector(0, length/2) : sgl::Vector(length/2, 0)), vert,
																													std::abs(length) + WIRE_WIDTH));
		cursor += vert ? sgl::Vector(0, length) : sgl::Vector(length, 0);
		return result;
	}

	Wire* wire(Link* src, bool vert, float length) {
		Wire* result = wire(vert, length);
		src->connect(result);
		return result;
	}

	Wire* wire(Link* src, Link* dest, bool vert) {
		sgl::Vector dist = dest->getPosition() - cursor;
		float length = vert ? dist.y : dist.x;

		Wire* result = wire(vert, length);

		src->connect(result);
		result->connect(dest);
		return result;
	}

	Wire* wireStart(Link* src, bool vert, float length) {
		cursor = src->getPosition();
		return wire(src, vert, length);
	}

	Wire* wireStart(Link* src, Link* dest, bool vert) {
		cursor = src->getPosition();
		return wire(src, dest, vert);
	}

	inline Adder* adder(sgl::Vector pos, sgl::Vector offset) {
		return new Adder(adderLoader.load(pos*CELL_SIZE + offset));
	}

public:
	Map() {
		room2horiz({5, 0});			torch({5, 0}, 400);
		corridor2({5, 1}, true);	torch({5, 1}, 300);
		room2horiz({5, 2});			torch({5, 2}, 400);
		corridor4({5, 3});			torch({5, 3}, 400);	objects.push_back(new ItemObject(itemLoader.load(sgl::Vector(5, 3)*CELL_SIZE)));
			corridorG({6, 3}, WEST);	torch({6, 3}, 350);
			corridorG({6, 2}, EAST);	torch({6, 2}, 300);
			corridor1({7, 2}, WEST);	torch({7, 2}, 350);

			corridor2({4, 3}, false);	torch({4, 3}, 350);
			corridor2({3, 3}, false);	torch({3, 3}, 350);
			corridor3({2, 3}, NORTH);	torch({2, 3}, 350);
				corridor2({2, 2}, true);	torch({2, 2}, 350);
				corridorG({2, 1}, NORTH);	torch({2, 1}, 350);
				corridor2({1, 1}, false);	torch({1, 1}, 300);
				room1({0, 1}, EAST);			torch({0, 1}, 400);

				corridor2({1, 3}, false);	torch({1, 3}, 350);
				corridorG({0, 3}, EAST);	torch({0, 3}, 350);
				corridor2({0, 4}, true);	torch({0, 4}, 300);
				room1({0, 5}, SOUTH);		torch({0, 5}, 400);

			corridor2({5, 4}, true);		torch({5, 4}, 350);
			corridor4({5, 5});				torch({5, 5}, 400);
				corridor2({5, 6}, true);	torch({5, 6}, 350);
				corridor2({5, 7}, true);	torch({5, 7}, 300);
				room1({5, 8}, SOUTH);		torch({5, 8}, 400);

				corridorG({4, 5}, SOUTH);	torch({4, 5}, 350);
				corridorG({4, 4}, NORTH);	torch({4, 4}, 350);
				corridor2({3, 4}, false);	torch({3, 4}, 350);
				corridor2({2, 4}, false);	torch({2, 4}, 350);
				corridorG({1, 4}, EAST);	torch({1, 4}, 350);
				corridor2({1, 5}, true);	torch({1, 5}, 300);
				corridor2({1, 6}, true);	torch({1, 6}, 300);
				corridor3({1, 7}, NORTH);	torch({1, 7}, 350);
					corridorG({0, 7}, EAST);
					corridor3({0, 8}, WEST);
						corridor2({1, 8}, false);
						corridor1({2, 8}, WEST);	torch({2, 8}, 300);

						corridorG({0, 9}, SOUTH);
						corridor2({1, 9}, false);
						corridor1({2, 9}, WEST);	torch({2, 9}, 300);

					corridor2({2, 7}, false);
					corridor3({3, 7}, NORTH);
						corridor2({3, 6}, true);
						corridorG({3, 5}, NORTH);
						corridorG({2, 5}, EAST);
						room1({2, 6}, SOUTH);		torch({2, 6}, 300);

					corridorG({4, 7}, NORTH);		torch({4, 7}, 200);
					corridor3({4, 8}, EAST);
						corridorG({3, 8}, EAST);
						corridor1({3, 9}, SOUTH);

						corridor2({4, 9}, true);
						corridorG({4, 10}, WEST);
						corridor2({3, 10}, false);
						corridor2({2, 10}, false);
						corridor2({1, 10}, false);
						corridor1({0, 10}, EAST);

				corridor3({6, 5}, NORTH);		torch({6, 5}, 350);
					corridorG({6, 4}, EAST);	torch({6, 4}, 350);
					corridorG({7, 4}, WEST);	torch({7, 4}, 350);
					corridor1({7, 3}, NORTH);	torch({7, 3}, 350);

					corridor2({7, 5}, false);
					corridor3({8, 5}, EAST);	torch({8, 5}, 200);
						corridor3({8, 6}, EAST);
						corridor2({7, 6}, false);
						corridorG({6, 6}, EAST);
						corridor2({6, 7}, true);	torch({6, 7}, 200);
						corridorG({6, 8}, SOUTH);
						corridor2({7, 8}, false);
						corridorG({8, 8}, WEST);
						room2horiz({8, 7});			torch({8, 7}, 300);

						corridor2({8, 4}, true);
						corridor2({8, 3}, true);
						corridor3({8, 2}, WEST);
							corridor3({8, 1}, EAST);
								corridor1({7, 1}, EAST);

								corridorG({8, 0}, EAST);
								corridor2({9, 0}, false);
								corridor1({10, 0}, WEST);

							corridor3({9, 2}, EAST);
								corridor2({9, 3}, true);
								corridor2({9, 4}, true);
								corridor1({9, 5}, SOUTH);

								corridorG({9, 1}, EAST);
								corridorG({10, 1}, NORTH);
								corridor2({10, 2}, true);
								corridor2({10, 3}, true);
								corridor2({10, 4}, true);
								corridor2({10, 5}, true);
								corridor3({10, 6}, EAST);
									corridorG({9, 6}, EAST);
									corridor2({9, 7}, true);	torch({9, 7}, 200);
									corridor2({9, 8}, true);
									corridor1({9, 9}, SOUTH);

									corridor2({10, 7}, true);
									corridor2({10, 8}, true);
									corridor2({10, 9}, true);
									corridorG({10, 10}, WEST);
									corridor2({9, 10}, false);
									corridor3({8, 10}, NORTH);
										corridor2({7, 10}, false);
										corridor1({6, 10}, EAST);

										corridorG({8, 9}, NORTH);
										corridor2({7, 9}, false);
										corridor2({6, 9}, false);
										corridorG({5, 9}, EAST);
										room2horiz({5, 10});			torch({5, 10}, 400);

		empty({0, 0}); empty({1, 0}); empty({2, 0}); empty({3, 0}); empty({4, 0}); empty({6, 0}); empty({7, 0}); empty({3, 1});
		empty({4, 1}); empty({6, 1}); empty({0, 2}); empty({1, 2}); empty({3, 2}); empty({4, 2}); empty({0, 6}); empty({4, 6}); empty({7, 7});
		fog(sgl::Vector(-3, 5)*CELL_SIZE, sgl::Vector(5, 11)*CELL_SIZE);
		fog(sgl::Vector(13, 5)*CELL_SIZE, sgl::Vector(5, 11)*CELL_SIZE);

		Link* w = wireStart(swtch({5, 2}, {SWITCH_BIG_OFFSET}, true), false, -SWITCH_BIG_OFFSET);
			w = wire(w, door({5, 2}, NORTH, true), true);

		w = wireStart(swtch({7, 2}, {SWITCH_SMALL_OFFSET, 0}, true), false, -SWITCH_SMALL_OFFSET - CELL_SIZE);
			w = wire(w, true, CELL_SIZE - WIRE_MARGIN);
			w = wire(w, false, -4*CELL_SIZE);
			wire(w, door({2, 3}, SOUTH, false), true);

		Adder* add = adder({0, 1}, {SWITCH_BIG_OFFSET, 0});
		w = wireStart(swtch({0, 1}, {-SWITCH_BIG_OFFSET, SWITCH_BIG_OFFSET - SWITCH_SIZE}, false), false, 2*SWITCH_BIG_OFFSET);
			wire(w, add, true);

		w = wireStart(swtch({0, 1}, {-SWITCH_BIG_OFFSET, -SWITCH_BIG_OFFSET + SWITCH_SIZE}, true), false, 2*SWITCH_BIG_OFFSET);
			wire(w, add, true);

			w = wire(add, false, 2*CELL_SIZE - SWITCH_BIG_OFFSET - 2*WIRE_MARGIN);
			w = wire(w, true, 2*CELL_SIZE + WIRE_MARGIN);
			w = wire(w, false, 3*CELL_SIZE + 2*WIRE_MARGIN);
			wire(w, door({5, 3}, NORTH, true), true);


		add = adder({0, 5}, {0, SWITCH_BIG_OFFSET});
		wireStart(swtch({0, 5}, {SWITCH_BIG_OFFSET - SWITCH_SIZE, SWITCH_BIG_OFFSET}, false), add, false);

		const float off = std::round(SWITCH_BIG_OFFSET/2);
		wireStart(swtch({0, 5}, {-SWITCH_BIG_OFFSET + SWITCH_SIZE, SWITCH_BIG_OFFSET}, false), add, false);
			w = wire(add, true, -off);

			add = adder({1, 5}, {0, off});
			wire(w, add, false);
			wire(add, door({1, 5}, SOUTH, false), true);

		Switch* sw = swtch({2, 6}, {-SWITCH_BIG_OFFSET, 0}, false);
		w = wireStart(sw, false, -CELL_SIZE + SWITCH_BIG_OFFSET);
			wire(w, add, true);

		add = adder({2, 6}, {-SWITCH_BIG_OFFSET, off});
		wireStart(sw, add, true);

		w = wireStart(swtch({2, 6}, {SWITCH_BIG_OFFSET, 0}, false), true, off);
			wire(w, add, false);
			w = wire(add, false, SWITCH_BIG_OFFSET - CELL_SIZE);
			w = wire(w, true, CELL_SIZE - off);
			wire(w, door({1, 7}, WEST, false), false);

		add = adder({4, 7}, {0, WIRE_MARGIN});
		w = wireStart(swtch({2, 8}, {SWITCH_SMALL_OFFSET, 0}, false), false, 2*WIRE_MARGIN - 2*SWITCH_SMALL_OFFSET);
			w = wire(w, true, WIRE_MARGIN - CELL_SIZE);
			wire(w, add, false);
			wire(add, door({4, 7}, NORTH, false), true);


		Adder* add2 = adder({5, 8}, {2*WIRE_MARGIN, 0});
		w = wireStart(swtch({5, 8}, {-SWITCH_BIG_OFFSET + SWITCH_SIZE, SWITCH_BIG_OFFSET}, false), true, -SWITCH_BIG_OFFSET);
			w = wire(w, false, SWITCH_BIG_OFFSET - SWITCH_SIZE - 2*WIRE_MARGIN);

			sgl::Vector temp = cursor;
			wire(w, add2, false);
			cursor = temp;
				w = wire(w, true, WIRE_MARGIN - CELL_SIZE);
				wire(w, add, false);

		w = wireStart(swtch({5, 8}, {SWITCH_BIG_OFFSET - SWITCH_SIZE, SWITCH_BIG_OFFSET}, true), true, -SWITCH_BIG_OFFSET);
			wire(w, add2, false);
			w = wire(add2, true, WIRE_MARGIN - CELL_SIZE);
			w = wire(w, false, CELL_SIZE - 2*WIRE_MARGIN);
			wire(w, door({6, 7}, NORTH, false), true);

		add = adder({2, 9}, {-SWITCH_SMALL_OFFSET, 0});
		wireStart(swtch({2, 9}, {SWITCH_SMALL_OFFSET, 0}, false), add, false);

		w = wireStart(swtch({0, 10}, {-SWITCH_SMALL_OFFSET, 0}, true), false, 2*CELL_SIZE);
			wire(w, add, true);
			w = wire(add, true, -2*CELL_SIZE - WIRE_MARGIN);
			w = wire(w, false, CELL_SIZE + SWITCH_SMALL_OFFSET);
			w = wire(w, true, WIRE_MARGIN - 2*CELL_SIZE);
			w = wire(w, false, 3*CELL_SIZE);
			wire(w, door({6, 5}, SOUTH, false), true);

		add = adder({8, 2}, {});
		w = wireStart(swtch({7, 3}, {0, -SWITCH_SMALL_OFFSET}, false), true, CELL_SIZE + SWITCH_SMALL_OFFSET);
			w = wire(w, false, 2*WIRE_MARGIN - CELL_SIZE);
			w = wire(w, true, CELL_SIZE);
			w = wire(w, false, 2*CELL_SIZE - 2*WIRE_MARGIN);
			wire(w, add, true);
			wire(add, door({9, 2}, WEST, false), false);


		w = wireStart(swtch({7, 1}, {-SWITCH_SMALL_OFFSET, 0}, false), false, CELL_SIZE + SWITCH_SMALL_OFFSET);
			wire(w, add, true);

		add = adder({8, 7}, {0, -SWITCH_BIG_OFFSET + SWITCH_SIZE});
		sw = swtch({8, 7}, {-SWITCH_BIG_OFFSET, 0}, true);
		w = wireStart(sw, false, SWITCH_BIG_OFFSET);
			wire(w, add, true);
			wire(add, door({8, 7}, SOUTH, true), true);
		sw->targ(true);

		sw = swtch({8, 7}, {SWITCH_BIG_OFFSET, -SWITCH_BIG_OFFSET + SWITCH_SIZE}, false);
		wireStart(sw, add, false);

		add = adder({8, 7}, {SWITCH_BIG_OFFSET, 0});
		wireStart(sw, add, true);
			w = wire(add, false, CELL_SIZE - SWITCH_BIG_OFFSET - 2*WIRE_MARGIN);
			wire(w, door({9, 7}, NORTH, false), true);

		wireStart(swtch({8, 7}, {SWITCH_BIG_OFFSET, SWITCH_BIG_OFFSET - SWITCH_SIZE}, false), add, true);

		w = wireStart(swtch({9, 9}, {0, SWITCH_SMALL_OFFSET}, true), true, -SWITCH_SMALL_OFFSET - 3*CELL_SIZE);
			w = wire(w, false, CELL_SIZE);
			wire(w, door({10, 8}, NORTH, false), true);
	}

	sgl::Lighting::Source* torch(sgl::Vector pos, float brightness) {
		auto t = new sgl::Lighting::Source(light, {brightness}, sgl::Data().position(pos*CELL_SIZE).color({0.65f, 0.5f, 0.3f}));
		t->setFragmentShader(lampShader);
		return t;
	}

	void collision(BoxObject* box) {
		for (BoxObject* b : objects)
			b->collision(box);
	}

};

#endif
