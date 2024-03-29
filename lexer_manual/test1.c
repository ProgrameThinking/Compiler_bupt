//const int MaxLength = 500;
//const int MaxId = 300;

char cache[MaxLength];
char* curCh = cache;
int cacheL = 0;//'\0' excluded

3.5
-3
3e-3
3e-3e
2.3.4
".asdasd
'asdasd
'

//reserves total=34
const int resCount = 34;
char *key0[]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","_Complex","_Imaginary","union","unsigned","void","volatile","while"};

//segs, total = 9
const int segCount = 9;
char *key1[]={"(",")","[","]","{","}",",",";","'"};

//op, total = 32
const int opCount = 32;
char *key2[]={"+","-","*","/","%","<",">","==",">=","<=",
	"!=","!","&&","||","<<",">>","~","|","^","&","=","?",":","->","++","--",".","+=","-=","*=","/=","%="};

/*Note that ? and : * are separate/
/**/

//identifier max = 500;
char id[MaxId][MaxLength] = {""};
int idCount=0;

//string constant max = 500
char str[MaxId][MaxLength] = {""};
int strCount=0;

//char constant max = 500
char charie[MaxId][MaxLength] = {""};
int charieCount=0;

//integer constant max = 500
char intie[MaxId][MaxLength] = {""};
int intieCount=0;

//float constant max = 500
char floatie[MaxId][MaxLength] = {""};
int floatieCount=0;

void StoreCur()
{
	StoreCh(cur);
}

void StoreCh(char ch)
{
	if(cacheL>=MaxLength-1)
	{
		log("[ERROR]Overflow: an identifier can have at most 499 chars. Program will quit.");
		exit(-1);
	}


	*curCh = ch;
	curCh++;//move pointer

	cacheL++;//record size;

	*curCh='\0';//create tail.
}

void RetractCache()
{
	if(cacheL<=0)
	{
		log("[ERROR]Cannot retract cache at while it's empty Program will quit.");
		exit(-1);
	}

	curCh--;//move pointer

	cacheL--;//update size;

	*curCh='\0';//create tail.
}

void ClearCache()
{
	curCh = cache;
	*cache = '\0';

	cacheL = 0;//record size;
}

//private
int FindInList(char arrayHead[][MaxLength],int size)
{
	for(int i = 0; i < size; i++)
	{
		if(!strcmp(arrayHead[i],cache))//same
		{
			return i;
		}
	}

	//not find, return -1;
	return -1;
}

//private
void StoreInList(char arrayHead[][MaxLength],int& size,const char* hint)
{
	if(size >= MaxId)
	{
		log("[ERROR]Overflow:A list has overflowed. Program will quit.\n");
		log("[ERROR]The list returned info: ");
		log(hint);
		exit(-1);
	}
	//else: enough space;

	strncpy(arrayHead[size],cache,MaxLength);
	size++;
}

//for ending.cpp
void PrintList(FILE* fp,char arrayHead[][MaxLength],int count)
{
	for(int i = 0; i < count; i++)
	{
		fprintf(fp,"%d\t%s\n",i,arrayHead[i]);
	}
}


int CheckId()
{
	return FindInList(id,idCount);
}

void StoreId()
{
	StoreInList(id,idCount,"Identifier");
}

//str
int CheckStr()
{
	log("A string is loaded:");
	log(cache);
	return FindInList(str,strCount);
}

void StoreStr()
{
	StoreInList(str,strCount,"String");
}

//char
int CheckChar()
{
	return FindInList(charie,charieCount);
}

void StoreChar()
{
	StoreInList(charie,charieCount,"Char Constant");
}
//integer
int CheckInt()
{
	return FindInList(intie,intieCount);
}
void StoreInt()
{

	StoreInList(intie,intieCount,"Integer Constant");
}
//float
int CheckFloat()
{
	return FindInList(intie,intieCount);
}
void StoreFloat()
{
	StoreInList(floatie,floatieCount,"Float Constant");
}


int CheckRes()
{
	for(int i = 0; i < resCount; i++)
	{
		if(!strcmp(key0[i],cache))//same
		{
			return i;
		}
	}

	//not find, return -1;
	return -1;
}

int CheckSeg()
{
	for(int i = 0; i < segCount; i++)
	{
		if(!strcmp(key1[i],cache))//same
		{
			return i;
		}
	}

	//not find, return -1;
	return -1;
}

int CheckOp()
{
	for(int i = 0; i < opCount; i++)
	{
		if(!strcmp(key2[i],cache))//same
		{
			return i;
		}
	}

	//not find, return -1;
	return -1;
}

void ErrorChar()
{
	fprintf(LOG,"[Error]:Unexpected char '%c'(%d) at Line %d Col %d.",cur,cur,lineCount,colPos);
	//GetChar();
}