#include "SQLiteDB.h"

//#include "../setDebugNew.h"

SQLiteDB::SQLiteDB(std::string &DBName) : 
m_pDBName(new std::string(DBName)), 
m_pDB(NULL), 
m_cErrMsg(NULL)
{

}

SQLiteDB::~SQLiteDB()
{
	close();
	delete m_pDBName;
}

std::string SQLiteDB::getErrorMessage() const
{
	return std::string(m_cErrMsg);
}


bool SQLiteDB::open()
{
	if(isOpen() || !m_pDBName) return false;

	bool bRetVal = (sqlite3_open(m_pDBName->c_str(), &m_pDB) == SQLITE_OK);
	if(!bRetVal) close();

	return bRetVal;
}

bool SQLiteDB::close()
{
	if(!isOpen()) return false;

	bool bRetVal = (sqlite3_close(m_pDB) == SQLITE_OK);
	m_pDB = NULL;

	return bRetVal;
}

bool SQLiteDB::isOpen() const
{
	return m_pDB;
}

bool SQLiteDB::exec(std::string &pstrSQL, ItemList *pItems)
{
	if(!isOpen()) return false;

	return sqlite3_exec(m_pDB, pstrSQL.c_str(), getList, pItems, &m_cErrMsg) == SQLITE_OK;
}

int SQLiteDB::getList(void *pList, int argc, char **argv, char **azCol)
{
	if(!pList) return 0;

	ItemList *pRetVal = static_cast<ItemList *>(pList);
	
	std::vector<std::string> *pItem = new std::vector<std::string>;
	for(int i = 0; i < argc; ++i)
	{
		pItem->push_back(argv[i] ? argv[i] : "NULL");
	}
	pRetVal->push_back(pItem);

	return 0;
}
