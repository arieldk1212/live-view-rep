#include "../inc/Core/Entity.h"

template <class EntityParam>
Entity<EntityParam>::Entity(EntityParam &&ShortEntity, EntityParam &&LongEntity, Type &&EntityType)
    : m_ShortEntity(std::forward<EntityParam>(ShortEntity)),
      m_LongEntity(std::forward<EntityParam>(LongEntity)),
      m_EntityType(std::move(EntityType)) {

}
