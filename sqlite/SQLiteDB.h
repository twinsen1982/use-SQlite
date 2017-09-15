#ifndef _SQLITEDB_H_
#define _SQLITEDB_H_

#include "sqlite3.h"

#include <list>
#include <vector>
#include <string>

typedef std::list<std::vector<std::string> *> ItemList;

class SQLiteDB
{
public:
	SQLiteDB(std::string &DBName);		// 传入数据库名
	virtual ~SQLiteDB();

	bool open();						// 操作数据库前必须打开数据库，且在关闭前只需打开一次
	bool close();						// 使用完数据库后关闭数据库，与打开数据库相对应

	bool isOpen() const;				// 是否已打开数据库

	std::string getErrorMessage() const;// 当执行数据库操作后返回错误时，用来返回错误信息

	bool exec(std::string &pstrSQL, ItemList *pItems = NULL);	// 执行SQL语句，参数1为SQL语句，参数2为执行结果，如查询结果数据

protected:
	std::string *m_pDBName;
	sqlite3 *m_pDB;
	char *m_cErrMsg;

	static int getList(void *pList, int argc, char **argv, char **azCol);
};

#endif // _SQLITEDB_H_