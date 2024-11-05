#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"
#include "Sector.h"

// TODO: add logic for the data separation from the full address to entity block.

template <typename EntityParam> class Entity final {
public:
  Entity(EntityParam &&ShortEntity, EntityParam &&LongEntity, Type &&EntityType);
  ~Entity();

private:
  EntityParam m_ShortEntity;
  EntityParam m_LongEntity;
  Type m_EntityType;
};

#endif

/*
* class Address {
  std::vector<std::map<Entity entity, Type type>> ConstructedEntity;
};
 */