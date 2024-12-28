#ifndef DATABASE_COMMANDS_H
#define DATABASE_COMMANDS_H

#include <optional>
#include <string>
#include <unordered_map>

/**
 * @file DatabaseCommands.h
 * @brief this file is responsible of collecting important database commands for
 * the ORM.
 */

enum class DatabaseFieldCommands {
  SerialPrimaryKeyField,
  IntField,
  CharField,
  VarChar100Field
};

const std::unordered_map<DatabaseFieldCommands, std::string>
    DatabaseFieldStrings = {
        {DatabaseFieldCommands::SerialPrimaryKeyField, "serial primary key"},
        {DatabaseFieldCommands::IntField, "int"},
        {DatabaseFieldCommands::CharField, "char"},
        {DatabaseFieldCommands::VarChar100Field, "varchar(100)"}};

enum class DatabaseQueryCommands {
  CreateTable,
  CreateTableIfNotExists,
  UpdateAdd,
  UpdateDropColumn,
  UpdateRenameColumn,
  DropDrop,
  DropTruncate,
};

const std::unordered_map<DatabaseQueryCommands, std::string>
    DatabaseQueryCommandsStrings = {
        {DatabaseQueryCommands::CreateTable, "create table"},
        {DatabaseQueryCommands::CreateTableIfNotExists,
         "create table if not exists"},
        {DatabaseQueryCommands::UpdateAdd, "add"},
        {DatabaseQueryCommands::UpdateDropColumn, "drop column"},
        {DatabaseQueryCommands::UpdateRenameColumn, "rename column"},
        {DatabaseQueryCommands::DropDrop, "drop table"},
        {DatabaseQueryCommands::DropTruncate, "truncate table"}};

template <typename DatabaseCommand>
inline std::string DatabaseCommandToString(DatabaseCommand Command) {
  try {
    return DatabaseQueryCommandsStrings.at(Command);
  } catch (const std::exception &e) {
    return "Command Not Found" + std::string(e.what());
  }
}

#endif