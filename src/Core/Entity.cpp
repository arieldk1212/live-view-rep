#include "../inc/Core/Entity.h"

template <class T>
Entity<T>::Entity(const std::string &ShortEntity, const std::string &LongEntity)
    : m_ShortEntity(ShortEntity), m_LongEntity(LongEntity) {

  }

template <class T>
Entity<T>::Entity(int ShortEntity, int LongEntity)
    : m_ShortEntity(ShortEntity), m_LongEntity(LongEntity) {

  }