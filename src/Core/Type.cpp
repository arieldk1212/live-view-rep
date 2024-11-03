#include "../inc/Core/Type.h"

Type::Type(StringVector Type) : m_Type(std::move(Type)) {}

const StringVector &Type::GetTypeVector() const { return m_Type; }

size_t Type::GetTypeVectorLength() const { return m_Type.size(); }

void Type::SetTypeVector(StringVector Type) { m_Type = std::move(Type); }

void Type::AddType(const std::string &Type) { m_Type.push_back(Type); }

void Type::DeleteType(const std::string &Type) {
  std::vector<auto>::iterator position =
      std::remove(m_Type.begin(), m_Type.end(), Type);
  if (position != m_Type.end()) {
    m_Type.erase(position);
  } else {
    APP_ERROR(Type + " NOT IN TYPES");
  }
}

Type &Type::operator=(const Type &other) {
  if (this->m_Type.size() == other.m_Type.size()) {
    this->m_Type.clear();
    for (const auto &i : other.m_Type) {
      this->m_Type.push_back(i);
    }
  }
  this->m_Type = other.m_Type;
  return *this;
}

Type &Type::operator=(Type &&) noexcept { return *this; }