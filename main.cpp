// MusicRecommand.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "leveldb/db.h"
#include "MusicRecommand.h"
#include <string>
#include <iostream>
using namespace std;
int main(){

	MusicDatabase musicdb("/tmp/testdb", "/tmp/testdb2", "/tmp/testdb3", "/tmp/testdb4", "/tmp/testdb5");
	musicdb.InsertUser("我是id","我是昵称",listener,"我是密码");//注册功能已实现
	Listener new_user;
	musicdb.Login("我是id", "我是密码",new_user);//登录功能
	//cout << new_user.GetUserName() << endl;
	musicdb.InsertMusic("逐梦演艺圈2", "SNH48", "2", "逐梦逐梦逐梦演艺圈圈圈圈……");
	
	new_user.Comment(musicdb , "逐梦演艺圈2","i124q");//音乐只加了id
	cout << musicdb.GetComment("逐梦演艺圈2") << endl;
	system("pause");
	
	
	
	return 0;
}


