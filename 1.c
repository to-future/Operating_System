#define OK 1
#define ERROR 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
	int sno;
	int age;
	char sname[10];
	int sclass;
	struct node *next;
}node;

int clear(node* head){
	free(head);
	return OK;
}

node* build(){
	int num, i;
	node *head = (node*)malloc(sizeof(node));
	head->next=NULL;

	node *p;
	printf("Number of students:");
	scanf("%d", &num);
	printf("type the information of them:\n(please follow this format: number age name class)\n");
	//building...
	for (i = 0; i < num; ++i)
	{
		scanf("%d%d%s%d", &head->sno, &head->age, &head->sname, &head->sclass);
		p = (node*)malloc(sizeof(node));
		p->next = head;
		head = p;
	}
	printf("DONE!\n");
	return head;
}

node* add(node* head){
	printf("type the information of them:\n(please follow this format: number age name class)\n");
	//adding...
	scanf("%d%d%s%d", &head->sno, &head->age, &head->sname, &head->sclass);
	node *p = (node*)malloc(sizeof(node));
	p->next = head;
	head = p;
	printf("DONE!\n");
	return head;
}

int find(node* head){
	int sno;
	printf("please type the school number of that student:\n");
	scanf("%d", &sno);
	node *p;
	p = head->next;
	if (p==NULL)
	{
		printf("This list is empty!\n");
		return OK;
	}
	while(p!=NULL){
		if(p->sno==sno){
			printf("sno:%d age:%d name:%s class:%d\n", p->sno, p->age, p->sname, p->sclass);
			break;
		}
		p = p->next;
	}
	if (p==NULL)
	{
		printf("We cannot find him!\n");
	}
	return OK;
}

int delete(node* head){
	if (head==NULL)
	{
		printf("This list is empty!\n");
		return OK;
	}

	int sno;
	char cc;
	node *p, *q;
	p = head->next;
	q = head;

	printf("please type the school number of that student:\n");
	scanf("%d", &sno);
	while(p!=NULL){
		if(p->sno==sno){
			printf("Do you want to delete this one:\n(sno:%d age:%d name:%s class:%d)\nY/n\n", p->sno, p->age, p->sname, p->sclass);
			getchar();
			scanf("%c", &cc);
			if (cc=='Y')
			{
				q->next = p->next;
				free(p);
				printf("DONE!\n");
				break;
			}else{
				printf("got it!\n");
				return OK;
			}
		}
		q = p;
		p = p->next;
	}
	if (p==NULL)
	{
		printf("We cannot find him!\n");
	}
	return OK;

}

int change(node* head){
	if (head==NULL)
	{
		printf("This list is empty!\n");
		return OK;
	}

	int sno;
	char cc;
	node *p;
	p = head->next;

	printf("please type the school number of that student:\n");
	scanf("%d", &sno);
	while(p!=NULL){
		if(p->sno==sno){
			printf("Do you want to change his information:(sno:%d age:%d name:%s class:%d)\nY/n\n", p->sno, p->age, p->sname, p->sclass);
			getchar();
			scanf("%c", &cc);
			if (cc=='Y')
			{
				printf("type the information of him:\n(please follow this format: number age name class)\n");
				scanf("%d%d%s%d", &p->sno, &p->age, &p->sname, &p->sclass);
				printf("DONE!\n");
				break;
			}else{
				printf("got it!\n");
				return OK;
			}
		}
		p = p->next;
	}
	if (p==NULL)
	{
		printf("We cannot find him!\n");
	}
	return OK;
}

int sort(node *head){
	node *p,*q,*r;
	node temp;
	int w1,w2,w4;
	char w3[10];
	q = p = head->next;
	while(p)
	{
		r = q = p;
		while(q){
			if (q->sno < r->sno)//min
			{
				r = q;
			}
			q = q->next;
		}
		//swap
		w1 = p->sno; w2 = p->age; strcpy(w3, p->sname); w4 = p->sclass;
		p->sno = r->sno; p->age = r->age; strcpy(p->sname, r->sname); p->sclass = r->sclass;
		r->sno = w1; r->age = w2; strcpy(r->sname, w3); r->sclass = w4;
		p = p->next;
	}
	printf("DONE!---------------------------\n");
	head = head->next;
	while(head){
		printf("(sno:%d age:%d name:%s class:%d)\n", head->sno, head->age, head->sname, head->sclass);
		head = head->next;
	}
	return OK;
}

int show(node* head){
	node *p;
	p = head->next;
	if (p==NULL)
	{
		printf("This list is empty!\n");
		return OK;
	}
	while(p){
		printf("(sno:%d age:%d name:%s class:%d)\n", p->sno, p->age, p->sname, p->sclass);
		p = p->next;
	}
	return OK;
}
void hint(){
	printf("========================\n");
	printf("Input a number to get started!\n");
	printf("1. build a student list\n");
	printf("2. show all the students\n");
	printf("3. find a typical student\n");
	printf("4. change the information of a student\n");
	printf("5. add a student\n");
	printf("6. delete a student\n");
	printf("7. sort list by school number\n");
	printf("0. exit\n");
	printf("========================\n");
	printf("your choice:");
}

int main(){
	node *stu;
	int get=1;
	while(get!=0){
		hint();
		scanf("%d", &get);

		switch (get) {
			case 1:stu = build(); break;
			case 2:show(stu);break;
			case 3:find(stu);break;
			case 4:change(stu);break;
			case 5:stu = add(stu);break;
			case 6:delete(stu);break;
			case 7:sort(stu);break;
			case 0:clear(stu); exit(0);
		}

	}
	return 0;
}