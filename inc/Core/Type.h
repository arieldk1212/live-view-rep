#ifndef TYPE_H
#define TYPE_H

#include "../Config/Logger.h"

#include <string>
#include <vector>

using StringVector = std::vector<std::string>;

class Type {
public:
  explicit Type(StringVector Type);

  [[nodiscard("returns: type object")]] const StringVector &GetTypeVector() const;
  [[nodiscard("returns: number of elements")]] size_t GetTypeVectorLength() const;

  void SetTypeVector(StringVector &&Type);

  void AddType(const std::string &Type);

  void DeleteType(const std::string &Type);

  Type &operator=(const Type &other) = default;
  Type &operator=(Type &&other) noexcept = default;

private:
  StringVector m_Type;
};

#endif