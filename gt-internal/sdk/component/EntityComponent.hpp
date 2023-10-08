#pragma once
#include <string>
#include "../proton/Boost.hpp"
#include "../variant/VariantDB.hpp"

class Entity;

#pragma pack(push, 1)
class EntityComponent
{
public:
	virtual ~EntityComponent();
	virtual void OnAdd(Entity* entity);
	virtual void OnRemove();

	BoostTrackableSignal m_signal;
	std::string* m_name;
	Entity* m_parent;
	VariantDB m_shared_db;

	Variant* GetVariant(const std::string& name)
	{
		return m_shared_db.GetVariant(name);
	}

	FunctionObject* GetFunction(const std::string& name)
	{
		return m_shared_db.GetFunction(name);
	}
};
#pragma pack(pop)