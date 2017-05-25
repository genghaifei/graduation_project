#include "my_sql.h"

sql_connector::sql_connector
{
    driver = NULL;
    conn = NULL;
    stmt = NULL;
    resultSet = NULL;
    prep_stmt = NULL;
}
sql_connector::~sql_connector
{

}

int sql_connector::begin_connect()
{
    driver = sql::mysql::get_driver_instance();
    if (driver == NULL)
    {
        std::cout<<"driver is NULL" <<std::endl;
        return -1;
    }
    conn = driver->connect("tcp://localhost:3306","root","123456");
    if (conn == NULL)
    {
        std::cout<<"conn is NULL" <<std::endl;
        return -2;
    }
    return 0;
}

int sql_connector::sql_init() 
{
    stmt = con->creatStatement();
    if (stmt == NULL)
    {
        std::cout<<"stmt is NULL" <<std::endl;
        return -3;
    }
    stmt->execute("SET CHARSET utf8");
    stmt->execute("USE GA");
}

int sql_connector::sql_select(const std::string &sql)
{
    char* str_sql = sql.c_str();
    resultSet = stmt->executeQuery(str_sql);
}

int sql_connector::sql_insert(const std::string &sql)
{
    char* str_sql = sql.c_str();
    prep_stmt = con->prepareStatement(str_sql);
    //(insert into city () VALUES ());
    //prep_stmt->setString(1,"London,UK");
    //int updatecount = 0;
    //updatecount = prep_stmt->executeUpdate();
}
int sql_connector::close_connect()
{
    delete resultSet;
    delete stmt;
    delete prep_stmt;
    conn->close();
    delete conn;
}
