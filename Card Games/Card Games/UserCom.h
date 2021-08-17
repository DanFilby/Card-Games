#pragma once
#include<string>
using namespace std;

const string yesAnswers[] = { "YES","Yes","yes","Y","y","yeah","Yep","yep" };	//overkill :D
const string noAnswers[] = { "NO","No","no","N","n","Nah","nah" };

class UserCom
{
public:
	//TODO: can turn this into generic
	static string GetString(string preface);
	static int GetNumber(string preface);
	static bool YesNo(string preface);

};

