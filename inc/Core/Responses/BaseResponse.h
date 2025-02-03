#ifndef BASE_RESPONSE_H
#define BASE_RESPONSE_H

// INFO: this class is all about the response classes from different classes
// across the project. meaning -> from db model a model returns a certain
// reponse from the db, due to that we will create a class that will handle
// different reponse cases and return the right response, i.e: virtual
// DBResponse WriteToDB(); -> it will hold data, codes, general info about the
// response.

// Entity
// TODO: add logic for the data separation from the full address to entity
// block. INFO: when i get the address from the Address Class, it will be passed
// down to Entity and the logic of the address separation to entities will be
// dealt here, meaning i probably want to change the Entity Ctor to the address
// itself, and the separate to Entities ( Data Structures ). INFO: the address
// class will inherit from entity due to the need use of the private entity
// members and their functionality.


/**
 * @brief valid can try and figure out a generic form of responses from
 * different application sections.
 *
 */

class BaseResponse {
public:
  BaseResponse();
  ~BaseResponse();

  void ToString();

  void TimeBenchmark();
private:

};

#endif