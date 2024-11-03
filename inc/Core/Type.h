#ifndef TYPE_H
#define TYPE_H

#include "../Config/Logger.h"

#include <algorithm>
#include <string>
#include <vector>

typedef std::vector<std::string> StringVector;

class Type {
public:
  explicit Type(StringVector Type);

  [[nodiscard("returns: type object")]] const StringVector& GetTypeVector() const;
  [[nodiscard("returns: number of elements")]] size_t GetTypeVectorLength() const;
  void SetTypeVector(StringVector Type);

  void AddType(const std::string &Type);

  void DeleteType(const std::string &Type);

  Type &operator=(const Type &other);
  Type &operator=(Type &&) noexcept;

private:
  StringVector m_Type;
};

#endif