#include <iostream>
#include <typeinfo>
#include "mysql_connection.h"
#include "mysql_driver.h"
#include "mysql_error.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"
#include "cppconn/metadata.h"
#include <memory>

class sql_connector
{
    public:
        sql_connector();
        ~sql_connector();
        int sql_init();
        int sql_select(const std::string &);
        int sql_insert(const std::string &);
        int begin_connect();
        int  close_connect();
        sql::ResultSet *resultSet;
    private:
        sql::mysql::MySQL_Driver *driver;
        sql::Connection *conn;
        sql::Statement *stmt;
        sql::PreparedStatement *prep_stmt;
};
