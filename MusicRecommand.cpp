#include "stdafx.h"
#include "leveldb/db.h"
#include "MusicRecommand.h"
#include <string>
#include <iostream>
using namespace std;

MusicDatabase::MusicDatabase(string path1,string path2,string path3,string path4,string path5) {
	leveldb::Options options_passwd;
	options_passwd.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options_passwd, path1, &db_passwd);
	assert(status.ok());
	leveldb::Options options_name;
	options_name.create_if_missing = true;
	leveldb::Status status2=leveldb::DB::Open(options_name, path2, &db_username);
	assert(status2.ok());
	leveldb::Options options_rank;
	options_rank.create_if_missing = true;
	leveldb::Status status3=leveldb::DB::Open(options_rank, path3, &db_rank);
	assert(status3.ok());
	leveldb::Options options_music_name;
	options_music_name.create_if_missing = true;
	leveldb::Status status4 = leveldb::DB::Open(options_music_name, path4, &db_musicname);
	assert(status4.ok());
	leveldb::Options options_comment;
	options_comment.create_if_missing = true;
	leveldb::Status status5 = leveldb::DB::Open(options_comment, path5, &db_comment);
	assert(status5.ok());
}
Status MusicDatabase::InsertMusic(string name, string singer, string id, string lyrics) {
	db_musicname->Put(leveldb::WriteOptions(), id,name );
	//to be continued;
	return 1;
}
Status MusicDatabase::InsertComment(string music_id, string user_id, string comment, int num) {
	db_comment->Put(leveldb::WriteOptions(), music_id, comment);
	//to be continued;
	return 1;
}
Status MusicDatabase::Login(string user_id, string user_passwd,User &user) {
	string temp;
	temp = GetPasswd(user_id);
	if (temp != user_passwd) { cout << "Wrong password!" << endl; return 0; }
	else
	{
		user.SetUserId(user_id);
		user.SetPasswd(user_passwd);
		user.SetUserName(GetName(user_id));
		//user.SetRank(GetRank);
		return 1;
	}
}
Status MusicDatabase::DeleteUser(string user_id) {
	db_passwd->Delete(leveldb::WriteOptions(), user_id);
	db_username->Delete(leveldb::WriteOptions(), user_id);
	db_rank->Delete(leveldb::WriteOptions(), user_id);
	return 1;
}
string MusicDatabase::GetComment(string id) {
	string temp;
	db_comment->Get(leveldb::ReadOptions(), id, &temp);
	return temp;
}
string MusicDatabase::GetName(string user_id) {
	string temp;
	db_username->Get(leveldb::ReadOptions(), user_id, &temp);
	return temp;
}
string MusicDatabase::GetPasswd(string user_id) {
	string temp;
	db_passwd->Get(leveldb::ReadOptions(), user_id, &temp);
	return temp;
}
string MusicDatabase::GetRank(string user_id) {
	string temp;
	db_rank->Get(leveldb::ReadOptions(), user_id, &temp);
	return temp;
}
Status MusicDatabase::UpdatePassword(string user_id, string new_password){
	string temp_rank;
	RANK rank2;
	string temp_name;
	temp_name = GetName(user_id);
	temp_rank = GetRank(user_id);
	if (temp_rank == "listener") rank2 = listener;
	if (temp_rank == "admin") rank2 = admin;
	if (temp_rank == "vip") rank2 = vip;
	DeleteUser(user_id);
	InsertUser(user_id, temp_name, rank2, new_password);
	return 1;
}
string MusicDatabase::GetMusicId(string name) {
	return "2";//id特点未知
}
Status Listener::Comment(MusicDatabase & musdb, string name, string comment) {
	string id;
	id = musdb.GetMusicId(name);
	musdb.InsertComment(id, user_id_, comment, 1);//num作用暂时不明确
	return 1;
}
Status User::SetPasswd(string passwd) {
	passwd_ = passwd;
	return 1;
}
Status User::SetUserName(string passwd) {
	user_name_ = passwd;
	return 1;
}
Status User::SetUserId(string passwd) {
	user_id_ = passwd;
	return 1;
}
string User::GetPasswd() {
	return passwd_;
}
string User::GetUserId() {
	return user_id_;
}
string User::GetUserName() {
	return user_name_;
}
Status MusicDatabase::InsertUser(string user_id, string name, RANK rank, string passwd) {
	
	string temp;
	if (rank == listener) temp = "listener";
	if (rank == admin) temp = "admin";
	if (rank == vip) temp = "vip";
	db_passwd->Put(leveldb::WriteOptions(), user_id, passwd);
	db_username->Put(leveldb::WriteOptions(), user_id, name);
	db_rank->Put(leveldb::WriteOptions(), user_id, temp);
/*	string value;
	string value2;
	string value3;
	db_passwd->Get(leveldb::ReadOptions(), user_id, &value);
	db_username->Get(leveldb::ReadOptions(), user_id, &value2);
	db_rank->Get(leveldb::ReadOptions(), user_id, &value3);
	cout <<value<<endl<< value2 <<endl<<value3  << endl;  */         //test
	return 1;
}

