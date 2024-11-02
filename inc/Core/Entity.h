#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"

template <class T> class Entity {
public:
  Entity(const std::string &ShortEntity, const std::string &LongEntity);
  Entity(int ShortEntity, int LongEntity);
  ~Entity();

private:
  T m_ShortEntity;
  T m_LongEntity;
  Type m_EntityType;
};

#endif