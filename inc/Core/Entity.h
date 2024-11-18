#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"

// TODO: add logic for the data separation from the full address to entity
// block. INFO: when i get the address from the Address Class, it will be passed
// down to Entity and the logic of the address separation to entities will be
// dealt here, meaning i probably want to change the Entity Ctor to the address
// itself, and the separate to Entities ( Data Structures ). INFO: the address
// class will inherit from entity due to the need use of the private entity
// members and their functionality.

class AbstractEntity {
public:
	virtual ~AbstractEntity() = 0;

	virtual void AddressSeparationToEntities() = 0;
	virtual void AddressEntityRemoval() = 0;
};

template <typename EntityParam> class Entity : public AbstractEntity {
public:
	Entity(EntityParam &&ShortEntity, EntityParam &&LongEntity,
				 Type &&EntityType);
	// Entity(Address Address);
	~Entity() override;

private:
	EntityParam m_ShortEntity;
	EntityParam m_LongEntity;
	Type m_EntityType;
};

#endif