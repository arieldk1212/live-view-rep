#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"
#include "Sector.h"

// TODO: add logic for the data separation from the full address to entity block.
// INFO: when i get the address from the Address Class, it will be passed down to Entity and
// the logic of the address separation to entities will be dealt here, meaning i probably
// want to change the Entity Ctor to the address itself, and the separate to Entities ( Data
// Structures ).

class AbstractEntity {
public:
  virtual ~AbstractEntity();

  virtual void SeparateEntity();
};

template <typename EntityParam> class Entity final : public AbstractEntity {
public:
  Entity(EntityParam &&ShortEntity, EntityParam &&LongEntity, Type &&EntityType);
  ~Entity() override;

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