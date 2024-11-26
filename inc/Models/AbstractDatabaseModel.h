#ifndef ABSTRACT_DATABASE_MODEL_H
#define ABSTRACT_DATABASE_MODEL_H

#include "../Core/UUID.h"
#include "Config/DatabaseManager.h"

class AbstractDatabaseModel {
public:
	virtual ~AbstractDatabaseModel() = 0;
	// TODO: maybe add in id field
	virtual void GenerateUUID();
	
};

#endif