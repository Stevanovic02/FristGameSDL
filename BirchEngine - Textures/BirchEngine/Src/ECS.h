#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

using namespace std;

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr size_t MAX_COMPONENTS = 64;

using ComponentBitSet = bitset<MAX_COMPONENTS>;
using ComponentArray = array<Component*, MAX_COMPONENTS>;

class Component
{
public:
	Entity* entity;
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual ~Component();

};

class Entity
{
public:
	void update();
	void draw();
	bool isActive() const;
	void destroy();

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentID<T>];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(forward<TArgs>(mArgs)...));
		c->entity = this;
		unique_ptr<Component> uPtr{ c };
		component.emplace_back(move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}

	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		if (ptr == nullptr)
		{
			throw runtime_error("Component not found");
		}
		return *static_cast<T*>(ptr);
	}


private:
	bool active = true;
	vector<unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};


void Entity::update()
{
	for (auto& c : components) c->update();
	for (auto& c : components) c->draw();
}

bool Entity::isActive() const
{
	return active;
}

void Entity::destroy()
{
	active = false;
}

class Manager
{
public:
	void upade();
	void draw();
	void refresh();

	Entity& addEntity()
	{
		Entity* e = new Entity();
		unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(move(uPtr));
		return *e;
	}

private:

	vector<unique_ptr<Entity>> entities;

};

void Manager::upade()
{
	for (auto& e : entities) e->update();
}

void Manager::draw()
{
	for (auto& e : entities) e->draw();
}

void Manager::refresh()
{
	entities.erase(remove_if(entities.begin(), entities.end(),
		[](const unique_ptr<Entity>& mEntity) { return !mEntity->isActive(); }), entities.end());
}