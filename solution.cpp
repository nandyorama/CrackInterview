#include<iostream>
 #include <stdlib.h>
using namespace std;
#define NO_CHARS 26
 
struct list 
{
	int lineNumber;
	int wordNumber;
	struct list * next;
};
struct TNode
{
    bool isEnd;  // end of word
    struct TNode* child[NO_CHARS]; // From 'a' to 'z'
	int occurances;
	struct list * pos;
};
 
struct list* newPos(int index,int word)
{
    struct list* temp = new list;
    temp->lineNumber = index;
	temp->wordNumber = word;
    temp->next = NULL;
    return temp;
} 

struct TNode* create()
{
    struct TNode* temp = new TNode;
    temp->isEnd = 0;
	temp->occurances =0;
	temp->pos = NULL;
    for (int i = 0; i < NO_CHARS; ++i)
        temp->child[i] = NULL;
    return temp;
}

int compare(const void* a, const void* b)
{  return *(char*)a - *(char*)b; }
 

void insertUtil(struct TNode** root, char* word, int * lineNumber,int *wordPos)
{
	//Check for end of One line.
	if(*word == '.')
	{
		//Increment Line Number
		*lineNumber = *lineNumber+1;
		//Re-Initialize word Position on starting of New Line
		*wordPos = 0;
		return;
	}

    if (*root == NULL)
        *root = create();
 
    if (*word != '\0')
        insertUtil( &( (*root)->child[tolower(*word) - 'a'] ), word+1, lineNumber, wordPos);
    else  
	{
        if ((*root)->isEnd)
        {
			//If already Present, then increase the count
			(*root)->occurances += 1; 

			//Next Line Number and Word Pos
			struct list* cur = (*root)->pos;
            while( cur->next )
                cur = cur->next;
			//Check same line number entry
			//if(cur->lineNumber!=*lineNumber)
	            cur->next = newPos(*lineNumber,*wordPos);
        }
        else 
        {
            (*root)->isEnd = 1;
			
			//First Occurance
			(*root)->occurances = 1;
			
			//Line Number and Word Pos
			(*root)->pos = newPos(*lineNumber,*wordPos);
        }
    }
} 

bool present(struct TNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TNode *cur = root;
 
    for (level = 0; level < length; level++)
    {
		index = tolower(key[level]) - 'a';
        if (!cur->child[index])
            return false;
 
        cur = cur->child[index];
    }
 
    return (cur != NULL && cur->isEnd);
}

int occurances(struct TNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TNode *cur = root;
 
    for (level = 0; level < length; level++)
    {
		index = tolower(key[level]) - 'a';
        if (!cur->child[index])
            return 0;
 
        cur = cur->child[index];
    }
 
    return (cur->occurances);
}
struct list * getPos(struct TNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TNode *cur = root;
 
    for (level = 0; level < length; level++)
    {
		index = tolower(key[level]) - 'a';
        if (!cur->child[index])
            return false;
 
        cur = cur->child[index];
    }
    if((cur != NULL && cur->isEnd))
		return cur->pos;
}
int listCount(struct list * root)
{
	int count =0;
	while(root)
	{
		count++;
		root=root->next;
	}
	return count;
}
//void checkClosestPosition(struct TNode *root, const char *key1,const char * key2)
//{
//	struct list * key1P= getPos(root, key1);
//	struct list * key2P= getPos(root, key2);
//	
//	//int count1 = listCount(key1P);
//	//int count2 = listCount(key2P);
//
//	int minDiff = INT_MAX;
//	int resultPos_k1=0,resultPos_k2=0;
//	int line =0;
//	//struct list * K1P;
//	//struct list * K2P;
//
//	//Traverse list to get closest spaced
//	while(key1P && key2P)
//	{
//		//K1P = key1P; 
//		//K2P = key2P;
//		if(key1P->lineNumber==key2P->lineNumber)
//		{
//
//			int diff = abs(key1P->wordNumber - key2P->wordNumber); 
//			if(minDiff>diff)
//			{
//				minDiff = diff;
//				line = key1P->lineNumber;
//				resultPos_k1 = key1P->wordNumber;
//				resultPos_k2 = key2P->wordNumber;
//			}
//		}
//		key1P= key1P->next;
//		key2P= key2P->next;
//	}
//	if(line && resultPos_k1 && resultPos_k2)
//		cout<<endl<<endl<<"For word "<<key1 <<" and "<<key2<<", closet spaced position is on Line number "<<line <<" and word number is "<<resultPos_k1 <<" and "<<resultPos_k2;
//	else
//		cout<<endl<<endl<<"NO Such Pair"<<endl;
//}
void checkClosestPosition(struct TNode *root, const char *key1,const char * key2)
{
	struct list * key1P= getPos(root, key1);
	struct list * key2P= getPos(root, key2);
	
	//int count1 = listCount(key1P);
	//int count2 = listCount(key2P);

	int minDiff = INT_MAX;
	int resultPos_k1=0,resultPos_k2=0;
	int line =0;
	//struct list * key2P;
	struct list * K2P;

	//Traverse list to get closest spaced
	for(;key1P;key1P=key1P->next)
	{
		K2P = key2P;
		for(;K2P;K2P=K2P->next)
		{
			if(key1P->lineNumber==K2P->lineNumber)
			{
				int diff = abs(key1P->wordNumber - K2P->wordNumber); 
				if(minDiff>diff)
				{
					minDiff = diff;
					line = key1P->lineNumber;
					resultPos_k1 = key1P->wordNumber;
					resultPos_k2 = K2P->wordNumber;
				}
			}
		}
	}
	if(line && resultPos_k1 && resultPos_k2)
		cout<<endl<<endl<<"For word "<<key1 <<" and "<<key2<<", closet spaced position is on Line number "<<line <<" and word number is "<<resultPos_k1 <<" and "<<resultPos_k2;
	else
		cout<<endl<<endl<<"NO Such Pair"<<endl;
}
#define MAX_WORD_SIZE 15
void insertWords( FILE* fp )
{
	char buffer[MAX_WORD_SIZE];
	struct TNode* root = NULL;
	int lineNumber = 1;int wordPos =1;
	
	//Read and Insert Into data structure
	 while( fscanf( fp, "%s", buffer ) != EOF )
	 {
        //cout<<buffer<<" ";
	    insertUtil(&root,buffer,&lineNumber,&wordPos);
		wordPos +=1;
	 }

	 //Input to Search
	 char keys[][15] = {"Sachin", "centuries"};

	 //Check Present or not
	 for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
	 {
		 if(present(root, keys[i]))
			 cout<<endl<<endl<<keys[i]<<" is present";
		 else
			 cout<<endl<<endl<<keys[i]<<" is not present";
	 } 
	 
	 //Check Occurances
	 for (int i = 0; i < sizeof(keys)/sizeof(keys[0]); i++)
	 {
		 int num = occurances(root, keys[i]);
		 if(num)
			 cout<<endl<<endl<<keys[i]<<" has "<<num <<" occurances";
		 else
			 cout<<endl<<endl<<keys[i]<<" is not present";
	 }

	 //Check Closest Spaced 
	 checkClosestPosition(root,keys[0],keys[1]);
}

int main()
{
	 FILE *fp = fopen ("Test.txt", "r");
    if (fp == NULL)
        printf ("File doesn't exist ");
    else
        insertWords (fp);

	getchar();
    return 0;
}
