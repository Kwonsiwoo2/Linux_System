#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student {
	int num;
	char * name;
	//char name[10];
};

typedef struct {
	int num;
	char * name;
	//char name[10];
}ST;
struct student test = {
	.num = 1,
	.name = "test"
};

typedef struct student Student;

int main()
{
	char temp[80];
	printf("num : %d, name : %s\n",test.num, test.name);

	//struct student st = {1, "ksh"};
	Student st = {1,"ksh"};
	ST St = {1,"ksh"};

	printf("num : %d, name : %s\n",st.num, st.name);

	st.num=2;
	st.name="ubuntu";
	
	printf("insert : ");
	scanf("%s",temp);
	printf("insert : %s\n", temp);

	st.name = (char*)malloc(strlen(temp)+1);

	st.num=3;
	strcpy(st.name, temp);

	printf("num : %d, name : %s\n",st.num, st.name);

	struct student sa[2] = {{1, "ksh"},{2,"aaa"}};
	printf("num : %d, name : %s\n",sa[0].num, sa[0].name);
	printf("num : %d, name : %s\n",sa[1].num, sa[1].name);

	struct student * pSt;
	pSt = &st;
	printf("num : %d, name : %s\n",pSt->num, pSt->name);
	printf("num : %d, name : %s\n",(*pSt).num, (*pSt).name);

	pSt = (struct student *)malloc(sizeof(struct student)*2);
	memcpy(pSt, sa, sizeof(struct student)*2);
	printf("num : %d, name : %s\n",pSt[0].num, pSt[0].name);
	printf("num : %d, name : %s\n",pSt[1].num, pSt[1].name);
}
