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

	// 初始化对应，传入数据库名
	SQLiteDB DB(std::string("sqlite\\test"));

	ItemList List;	// 保存数据库操作结果

	// 打开数据库
	while(DB.open())
	{
		// 输入数据
		boost::format formater("insert into test(name, age) values('%s', %d);");
		for(int i = 0; i < 10; ++i)
		{
			formater %((char)('a' + i)) %(i + 1);
			if(!DB.exec(formater.str())) break;
		}

		// 删除数据
		formater.parse("delete from test where name='%s';");
		for(int i = 0; i < 5; ++i)
		{
			formater %((char)('a' + i));
			if(!DB.exec(formater.str())) break;
		}

		// 修改数据
		formater.parse("update test set age=%d where name='%s';");
		for(int i = 5; i < 10; ++i)
		{
			formater %(2 * i) %((char)('a' + i));
			if(!DB.exec(formater.str())) break;
		}

		// 查找数据
		if(!DB.exec(std::string("select * from test;"), &List)) break;

		break;
	}

	
	// 关闭数据库
	DB.close();

	// 遍历数据
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
