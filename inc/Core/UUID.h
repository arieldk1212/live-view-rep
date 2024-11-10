#ifndef UUID_H
#define UUID_H

#include <cstdint>
#include <random>

class UUID {
public:
  UUID();
  explicit UUID(uint64_t UUID);
  ~UUID() = default;

private:
  uint64_t m_UUID;
};

#endif