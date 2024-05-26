#include <vector>
#include <memory>
#include "../entities/entity/Store.h"
#include "entity/Road.h"
#include "entity/Wall.h"

class Board
{
public:
	Board(int width, int height) : width(width), height(height)
	{
		map.resize(height, std::vector<std::shared_ptr<Entity>>(width, nullptr));

		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				std::shared_ptr<Road> entity(new Road({j, i}));
				map[i][j] = entity;
			}
		}

		addEntity(std::make_shared<Wall>(Position{ 136, 47 }));
		addEntity(std::make_shared<Wall>(Position{ 136, 48 }));
		addEntity(std::make_shared<Wall>(Position{ 136, 49 }));
		addEntity(std::make_shared<Wall>(Position{ 137, 47 }));
		addEntity(std::make_shared<Wall>(Position{ 138, 47 }));
		addEntity(std::make_shared<Wall>(Position{ 139, 47 }));
		addEntity(std::make_shared<Store>(Position{ 139, 47 }));
		addEntity(std::make_shared<RandomEvent>(Position{ 138, 48 }));

	}

	void addEntity(std::shared_ptr<Entity> entity)
	{
		Position pos = entity->getPosition();
		int x = pos.x;
		int y = pos.y;
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			map[y][x] = entity;
		}
	}

	void removeEntity(const Position& pos)
	{
		int x = pos.x;
		int y = pos.y;
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			map[y][x] = nullptr;
		}
	}

	bool isPassable(int x, int y) const
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			if (map[y][x])
			{
				return map[y][x]->isPassable();
			}
			return true; // if no entity, it's passable
		}
		return false; // out of bounds
	}

	bool canTeleport(int x, int y) const
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			if (map[y][x])
			{
				return map[y][x]->canTeleport();
			}
			return true;
		}
		return false;
	}


	std::shared_ptr<Entity> getEntity(int x, int y) const
	{
		if (x >= 0 && x < width && y >= 0 && y < height)
		{
			return map[y][x];
		}
		return nullptr;
	}

	std::vector<std::vector<std::shared_ptr<Entity>>> getMap() const
	{
		return this->map;
	}

private:
	int width;
	int height;
	std::vector<std::vector<std::shared_ptr<Entity>>> map;
};
