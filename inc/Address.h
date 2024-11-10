#ifndef ADDRESS_H
#define ADDRESS_H

#include "Core/Entity.h"

template <typename EntityParam> class AbstractAddress : public Entity <EntityParam> {
public:
  AbstractAddress();

  virtual void SetUUID();
};

template <typename EntityParam> class Address : public AbstractAddress <EntityParam> {

};

#endif //ADDRESS_H
