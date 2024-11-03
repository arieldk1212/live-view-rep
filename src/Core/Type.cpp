#include "../inc/Core/Type.h"

Type::Type(StringVector Type) : m_Type(std::move(Type)) {}

const StringVector &Type::GetTypeVector() const { return m_Type; }

size_t Type::GetTypeVectorLength() const { return m_Type.size(); }

void Type::SetTypeVector(StringVector Type) { m_Type = std::move(Type); }

void Type::AddType(const std::string &Type) { m_Type.push_back(Type); }

void Type::DeleteType(const std::string &Type) {
  const auto position = std::remove(m_Type.begin(), m_Type.end(), Type);
  // m_Type.erase(std::remove(m_Type.begin(), m_Type.end(), Type),
  // m_Type.end());
  if (position != m_Type.end()) {
    m_Type.erase(position);
  } else {
    APP_ERROR(Type + " NOT IN TYPES");
  }
}