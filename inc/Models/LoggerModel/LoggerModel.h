#ifndef LOGGER_MODEL_H
#define LOGGER_MODEL_H

#include "../DBModel.h"

class LoggerModel : public DBModel {
public:
private:
  std::string m_LogFile;
  std::string m_Timestamp;
  std::string m_Message;
};

#endif