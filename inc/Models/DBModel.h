#ifndef DB_MODEL_H
#define DB_MODEL_H

#include "../Config/DB.h"

class DBModel {
public:
	virtual ~DBModel() = 0;

	virtual void QueryWrite(DB::DBConnection &DBInstance); // INFO: DBInstance->Write
};

#endif