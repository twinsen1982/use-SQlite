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
	SQLiteDB(std::string &DBName);		// �������ݿ���
	virtual ~SQLiteDB();

	bool open();						// �������ݿ�ǰ��������ݿ⣬���ڹر�ǰֻ���һ��
	bool close();						// ʹ�������ݿ��ر����ݿ⣬������ݿ����Ӧ

	bool isOpen() const;				// �Ƿ��Ѵ����ݿ�

	std::string getErrorMessage() const;// ��ִ�����ݿ�����󷵻ش���ʱ���������ش�����Ϣ

	bool exec(std::string &pstrSQL, ItemList *pItems = NULL);	// ִ��SQL��䣬����1ΪSQL��䣬����2Ϊִ�н�������ѯ�������

protected:
	std::string *m_pDBName;
	sqlite3 *m_pDB;
	char *m_cErrMsg;

	static int getList(void *pList, int argc, char **argv, char **azCol);
};

#endif // _SQLITEDB_H_