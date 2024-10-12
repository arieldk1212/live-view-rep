#ifndef CONNECTION_H
#define CONNECTION_H

#include <libpq-fe.h>
#include <pqxx/pqxx>
#include <string>

#define CONNECTION_ERROR -1

const std::string db_connection_string = "postgresql://arielkeli@localhost/live-view";

int init_db_connection();

#endif