#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "../AbstractDatabaseModel.h"

class LoggerModel : public Query<class T> {
public:
  ~LoggerModel() override;

private:
  UUID m_LoggerUUID;
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif