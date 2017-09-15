#include "sqlite/SQLiteDB.h"

#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "setDebugNew.h"

int main(int argc, char *argv[])
{
#ifdef _DEBUG
//	_CrtSetBreakAlloc(150);
#endif

	// ��ʼ����Ӧ���������ݿ���
	SQLiteDB DB(std::string("sqlite\\test"));

	ItemList List;	// �������ݿ�������

	// �����ݿ�
	while(DB.open())
	{
		// ��������
		boost::format formater("insert into test(name, age) values('%s', %d);");
		for(int i = 0; i < 10; ++i)
		{
			formater %((char)('a' + i)) %(i + 1);
			if(!DB.exec(formater.str())) break;
		}

		// ɾ������
		formater.parse("delete from test where name='%s';");
		for(int i = 0; i < 5; ++i)
		{
			formater %((char)('a' + i));
			if(!DB.exec(formater.str())) break;
		}

		// �޸�����
		formater.parse("update test set age=%d where name='%s';");
		for(int i = 5; i < 10; ++i)
		{
			formater %(2 * i) %((char)('a' + i));
			if(!DB.exec(formater.str())) break;
		}

		// ��������
		if(!DB.exec(std::string("select * from test;"), &List)) break;

		break;
	}

	
	// �ر����ݿ�
	DB.close();

	// ��������
	BOOST_FOREACH(std::vector<std::string> *pItem, List)
	{
		BOOST_FOREACH(std::string col, *pItem)
		{
			std::cout << col << "\t";
		}

		pItem->clear();
		delete pItem;
		std::cout << std::endl;
	}

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
