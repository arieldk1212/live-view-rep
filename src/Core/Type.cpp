#include "../inc/Core/Type.h"

Type::Type(const StringVector &Type) : m_Type(Type) {}

StringVector Type::GetTypeVector() const { return m_Type; }

int Type::GetVectorLength() const { return m_Type.size(); }

void Type::SetTypeVector(StringVector Type) { m_Type = std::move(Type); }

void Type::AddType(const std::string &Type) { m_Type.push_back(Type); }

void Type::DeleteType(const std::string &Type) {
  std::vector<std::string>::iterator position =
      std::remove(m_Type.begin(), m_Type.end(), Type);
  if (position != m_Type.end()) {
    m_Type.erase(position);
  } else {
    APP_ERROR(Type + " NOT IN TYPES");
  }
}

void Type::operator=(const Type &other) {
  if (this->m_Type.size() == other.m_Type.size()) {
    this->m_Type.clear();
    for (int i = 0; i < other.m_Type.size(); i++ ) {
      this->m_Type.push_back(other.m_Type[i]);
    }
  } this->m_Type = std::move(other.m_Type);
}

void Type::operator=(Type &&) {
  // TODO(): check how to implement it.
}