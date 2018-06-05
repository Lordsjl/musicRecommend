#pragma once
#ifndef LIBRARY
#define LIBRARY value

#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*²Ù×÷Êý*/
enum RANK
{listener,admin,vip

};
typedef bool Status;

class User
{
public:

	User() {}
	~User() {}

	/*virtual Status Comment(string music_name, string comment);
	virtual Status DownloadLyric(string music_name);
	virtual Status Passwd(string new_password);*/
	Status Search(string music);      //    Search from all the tables
	Status SetUserName(string);
	Status SetPasswd(string);
	Status SetUserId(string);
	string GetUserName();
	string GetPasswd();
	string GetUserId();

protected:
	string user_name_;
	string passwd_;
	string user_id_;
	RANK rank_;
};
class MusicDatabase {
public:

	MusicDatabase() {};
	MusicDatabase(string,string,string,string,string);
	MusicDatabase(const MusicDatabase &m) {};
	~MusicDatabase(){}

	Status InsertUser(string user_id, string name, RANK rank, string password);
	Status DeleteUser(string user_id);
	Status UpdatePassword(string uer_id, string new_password);
	Status InsertMusic(string musicName, string Singer, string id, string lyrics);
	Status DeleteMusic(string music_id);
	Status InsertComment(string music_id, string user_id, string comment, int num);
	Status DeleteComment(string music_id, string user_id, int num);
	Status Login(string user_id, string passwd,User &x);
	Status GetUser(string user_id);
	Status GetMusic(string music_id);
	string GetPasswd(string user_id);
	string GetRank(string user_id);
	string GetName(string user_id);
	string GetComment(string music_id);
	string GetMusicId(string music_name);
	int countComment(string user_id);

	string MusicName2Id(string music_name);
	string UserName2Id(string user_name);
	leveldb::DB* Getdb_passwd() {
		return  db_passwd;
	}
	leveldb::DB* Getdb_name() {
		return  db_username;
	}	
	leveldb::DB* Getdb_rank() {
		return  db_rank;
	}
private:
	leveldb::DB* db_passwd;
	leveldb::DB* db_username;
	leveldb::DB* db_rank;
	leveldb::DB* db_musicname;
	leveldb::DB* db_comment;
};

class Recommand {

public:

	Recommand();
	~Recommand();

	vector<int> Word2Vec(string word);
	string GetMusic(vector<int> vec);

};






class Admin : public User {

public:

	Admin();
	~Admin();
	Status Comment(string music_name, string comment);
	Status DownloadLyric(string music_name);
	Status passwd(string new_password);
	Status DeleteComment(string music_name, string comment);
	Status DeleteMusic(string music_name);


};

class Listener :public User {

public:

	Listener() {}
	~Listener() {}

	Status Comment(MusicDatabase &,string music_name, string comment);
	Status DownloadLyric(string music_name);
	Status passwd(string new_password);

};


class Vip :public User {

public:

	Vip();
	~Vip();
	Status Comment(string music_name, string comment);
	Status DownloadLyric(string music_name);
	Status passwd(string new_password);
	Status RewriteComment(string music_id, string new_comment, int num);

};



class Music {

public:

	Music();
	~Music();

private:

	string name_;
	string singer_;
	int id_;
	string lyric_;

};


class Comment {

public:

	Comment();
	Comment(string commnet_, string username_, string music_, int num_);
	~Comment();

private:

	string comment_;
	string username_;
	string music_;
	int num_;

};



#endif