# use-SQlite
use SQlite

-----------------------------------------------------------------------------------------------------------------------

介绍：


SQlite是一个小型数据库。本项目目的是为大家快速简单使用SQlite提供帮助。
项目以C++对SQlite进行了简单的封装，使用了STL标准库。且无其它依赖。
在需要快速使用简单数据库时，本项目将会给予你帮助。即配置简单，使用简单，功能简单。

-----------------------------------------------------------------------------------------------------------------------

配置方法：


将sqlite目录拷贝到所需项目中，并将sqlite3.dll动态库拷贝到生成文件相应目录中即可。

-----------------------------------------------------------------------------------------------------------------------

使用方法：


main.cpp中给出了对数据库增删改查的用法，并使用了以下相关库以提高开发效率（在单独使用SQLiteDB时并不需要）
boost::format		用于构造SQL语句（替换内容用）
BOOST_FOREACH		简化对象遍历
VS内存泄露检查

-----------------------------------------------------------------------------------------------------------------------

接口说明：


SQLiteDB(std::string &DBName);
通过构造函数传入数据库名，按一个对象一个数据库原则来使用。

bool open();					
bool close();
配对使用，并只有在open与close之间才能对数据库进行访问。
返回值为true时成功,false时失败，
在open失败时，调用close将作无效处理

bool isOpen() const;
用于判断当前数据库是否为打开状态。
返回值：true为打开，false为未打开

bool exec(std::string &pstrSQL, ItemList *pItems = NULL);
执行SQL语句，并返回结果。
通过参数1传入所需要执行的SQL语句，如果需要得到执行结果，可通过参数2传入一个ItemList对象，如select查询结果。

-----------------------------------------------------------------------------------------------------------------------

数据库建立：


可通过SQLiteStudio工具进行数据库建立。
当然，通过SQLite也可以建立数据库。

-----------------------------------------------------------------------------------------------------------------------

其它相关问题

* 直接使用SQLite
使用Visual Studio直接使用SQLite时，需要用def文件从dll库中导出lib文件，方法如下：
lib /def:sqlite3.def /machine:ix86
对于dll，lib，def，exp文件之间的关系，在此不再说明。
.h文件需要到SQLite的源文件中拷贝，当前也有方法可根据def文件从dll中导出。

* 更专业的SQLite面向对象封装
cppSQLite
更全面的封装。
easySQLite
更面向对象的封装。