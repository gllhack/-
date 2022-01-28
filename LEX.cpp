#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fstream>

using namespace std;

struct symbol
{
	char* str;
	int  coding;
};

char * keyword_list[35] = { "void", "char","int","float","double","short","long", 
		"signed","unsigned","struct","union","enum","typedef","sizeof","auto","static", 
		"register","extern","const","volatile","return","continue","break","goto","if", 
		"else","switch","case","default","for","do","while","scanf","scanf","printf" };
char* operator_list[44] = { "{", "}","[", "]", "(", ")", ".", "->", "~", "++", "--", 
		"!","&","*","/","%","+","-","<<",">>",">",">=","<","<=","==","! =","^","|","&&",
		"||","?","=","/=","*=,","%=","+=","-=","&=","^=","|=",",","#",";",":" };

char ch;//读入字符
char strToken[20] = "";//存放构成单词符号的字符串
int eof_flag = 0;
int num = 1;//编码数字)(递增)
int row = 1;
struct symbol keywords[35];
struct symbol identifiers[44];
FILE* fp = NULL;
FILE* fw = NULL;
ofstream out;

//给单词符号设定种别码
void initialization() {
	//给关键字设定种别码
	for (int i=0;i<35;i++)
	{
		keywords[i].str = keyword_list[i];
		keywords[i].coding = num;
		num++;
	}
	//给运算符和边界符设定种别码
	for (int i = 0; i < 44; i++)
	{
		identifiers[i].str = operator_list[i];
		identifiers[i].coding = num;
		num++;
	}//数字79,标识符80
}
//把下一个字符读入ch中
void getNextChar(FILE* ffp) {
	if ((ch=getc(ffp))==EOF)
	{
		eof_flag = 1;
	}
	if (ch=='\n')
	{
		row++;
	}
}
//检查ch字符是否为  空白符,回车或者制表符  若是则反复调用getNextChar(),直至ch中读入非上述符号
void getbc(FILE* ffp)
{
	while (ch==' '||ch=='\n'||ch=='\t')
	{
		getNextChar(ffp);
	}
}
//判断ch是否为字母
bool isLetter(char ch)
{
	return isalpha(ch);
}
//判断ch是否为字母
bool isDigit(char ch)
{
	return isdigit(ch);
}
//判断ch是否为下划线
bool isUnderline(char ch)
{
	if (ch == '_')	return 1;
	else			return 0;
}
//将输入的字符ch连接srtToken
void concat() {
	char* tmp = &ch;
	strcat(strToken, tmp);
}
//把搜索指针回调一个字符位置
void retract(FILE* ffp) {
	fseek(ffp, -1, SEEK_CUR);
	ch = ' ';
}
//对于strToken中的字符串判断它是否为保留字,若是则给出它的种别码.否则返回0
int reserve_string(char* str) {
	for (int i=0;i<35;i++)
	{
		if ((strcmp(str,keywords[i].str))==0)
		{
			return keywords[i].coding;
		}
	}
	return 0;
}
//返回strToken中所识别出的运算符和边界符
int reserve_operator(char* ch) {
	for (int i=0;i<44;i++)
	{
		if ((strcmp(ch, identifiers[i].str)) == 0)
		{
			return identifiers[i].coding;
		}
	}
	return 0;
}
//出错处理
void error() {
	printf("\n *********************ERROR*****************************\n");
	printf("row %d Invaild symbol !!!", row);
	printf("\n *********************ERROR*****************************\n");
	exit(0);
}
//词法分析
void LexiscalAnalyzer()
{
	int num = 0, val = 0, code = 0;
	strcpy(strToken, "");
	getNextChar(fp);
	getbc(fp);
	switch (ch)
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':	
	case 'j':	
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_':
		while (isLetter(ch) || isDigit(ch) || isUnderline(ch))
		{
			concat();
			getNextChar(fp);
		}
		retract(fp);
		code = reserve_string(strToken);
			if (code==0)
			{
				printf("(%d , %s)\n", 79, strToken);
			}
			else
			{
				printf("(%d , %s)\n", code, strToken);
			}
			break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		while (isdigit(ch))
		{
			concat();
			getNextChar(fp);
		}
		retract(fp);
		printf("(%d , %s)\n", 80, strToken);
		break;

	case '{':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '}':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '[':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case ']':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '(':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case ')':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '.':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '-':
		concat();
		getNextChar(fp);
		if (ch=='>')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if(ch=='-')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if(ch=='=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '~':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '+':
		concat();
		getNextChar(fp);
		if (ch == '+')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '*':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '&':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if(ch=='&')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '!':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '%':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '<':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if(ch=='<')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '>':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if (ch == '>')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '=':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '^':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '|':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if (ch == '|')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case '?':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '/':
		concat();
		getNextChar(fp);
		if (ch == '=')
		{
			concat();
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		else if (ch == '/')//跳过注释
		{
			getNextChar(fp);
			while (ch!='\n')
			{
				getNextChar(fp);
			}
			break;
		}
		else if (ch=='*')//跳过注释
		{
			getNextChar(fp);
			while (ch != '*')
			{
				getNextChar(fp);
			}
			getNextChar(fp);
			if (ch == '/');
			break;
		}
		else
		{
			retract(fp);
			code = reserve_operator(strToken);
			printf("(%d , %s)\n", code, strToken);
		}
		break;
	case ',':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case '#':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case ':':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	case ':':
		concat();
		code = reserve_operator(strToken);
		printf("(%d , %s)\n", code, strToken);
		break;
	default:
		if (ch==EOF)
		{
			eof_flag = 1;
			break;
		}
		error();
	}
}
int main() {
	initialization();
	char name[1024];
	cout << "从文件读入: ";
	cin >> name;
	fp = fopen(name, "r");
	out.open("result.txt");
	while (!feof(fp))
	{
		if (eof_flag==1)
		{
			exit(1);
		}
		LexiscalAnalyzer();
	}
	fclose(fp);
	out.close();
	return 0;
}
