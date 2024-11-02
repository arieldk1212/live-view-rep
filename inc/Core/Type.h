#ifndef TYPE_H
#define TYPE_H

#include "../Config/Logger.h"

#include <string>
#include <vector>
#include <algorithm>

typedef std::vector<std::string> StringVector;

class Type {
public:
  
  explicit Type(const StringVector &Type);

  StringVector GetTypeVector() const;
  int GetVectorLength() const;
  void SetTypeVector(StringVector Type);

  void AddType(const std::string &Type);

  void DeleteType(const std::string &Type);

  Type &operator=(const Type &other);
  Type &operator=(Type &&);

private:
  StringVector m_Type;
};

#endif