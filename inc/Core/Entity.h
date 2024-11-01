#ifndef ENTITY_H
#define ENTITY_H

#include "Type.h"

template<class T>
class Entity : public Type {
public:
  Entity(const T& Entity, const T& ShortEntity, const T& LongEntity);
  ~Entity();
private:
  T m_Entity;
  T m_ShortEntity;
  T m_LongEntity;
};

#endif