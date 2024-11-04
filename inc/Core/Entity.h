#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"
#include "Sector.h"

template <class EntityParam> class Entity final : public Sector {
public:
  Entity(EntityParam &&ShortEntity, EntityParam &&LongEntity, Type &&EntityType);
  ~Entity();

private:
  EntityParam m_ShortEntity;
  EntityParam m_LongEntity;
  Type m_EntityType;
};

#endif