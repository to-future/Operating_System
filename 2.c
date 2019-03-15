#define FREE 0
#define READY 1
#define RUNNING 2
#define TS 2 /* time slice */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PCB {
    int pid;    
    int pstate;  
    char pname[10]; 
    int ptime;   
    struct PCB *pnext;
}pcb;

typedef struct PCBqueue
{
	int pnum;//number of pcb nodes
	pcb *front;
	pcb *rear;
}pcbQ;

pcbQ* init(){
	pcbQ *q;
	q = (pcbQ*)malloc(sizeof(pcbQ));
	q->front = q->rear = (pcb*)malloc(sizeof(pcb));
	q->front->pnext = NULL;
	q->pnum = 0;
	return q;
}
int enQueue(pcbQ *q, pcb p){//state:running, ready or free
	pcb *new;
	new = (pcb*)malloc(sizeof(pcb));
	if (!new) exit(0);
	//copy the informent...
	new->pid = p.pid;
	new->pstate = p.pstate;
	strcpy(new->pname,p.pname);
	new->ptime = p.ptime;
	new->pnext = NULL;
	//insert new pcb to the rear, and let it be the new rear
	q->rear->pnext = new;
	q->rear = new;
	return 1;
}

int deQueue(pcbQ *q, pcb *p){
	if (q->front == q->rear) return 0;
	//point front information
	pcb *temp = q->front->pnext;

	//copying that information...
	p->pid = temp->pid;
	p->pstate = temp->pstate;
	strcpy(p->pname,temp->pname);
	p->ptime = temp->ptime;
	p->pnext = NULL;
	
	//operating...
	q->front->pnext = temp->pnext;
	//incase temp is the onlyone in this queue
	if (q->rear == temp) q->rear = q->front;
	free(temp);
	return 1;
}

pcbQ* createFreeQueue(int m){
	pcbQ *q;
	q = (pcbQ*)malloc(sizeof(pcbQ));
	int i;
	char pname[10];
	pcb *front, *rear, *p;

	rear = (pcb*)malloc(sizeof(pcb));
	rear->pnext = NULL;
	front = rear;
	p = rear;
	for (i = 0; i < m; ++i)
	{
		front = (pcb*)malloc(sizeof(pcb));
		front->pstate = FREE;
		itoa(i, pname, 10);
		strcpy(front->pname, pname);
		front->ptime = 0;
		front->pnext = p;
		p = front;
	}
	q->front = front;
	q->rear = rear;
	q->pnum = m;
	return q;
}

int isEmpty(pcbQ *q){
	if (q->front==q->rear) return 1;
	else return 0;
}

int main(int argc, char const *argv[])
{
	int i,n,time;
	pcbQ* freeQueue;
	pcbQ* readyQueue;
	pcbQ* runningQueue;
	pcb temp;

	readyQueue = init();
	runningQueue = init();
	//create enough free-pcbs
	freeQueue = createFreeQueue(20);

	printf("Input number of ready-pcbs(less than 20):\n");
	scanf("%d", &n);
	printf("Input their running time:\n");
	for (i = 0; i < n; ++i)
	{
		scanf("%d", &time);
		deQueue(freeQueue, &temp);
		temp.ptime = time;
		enQueue(readyQueue, temp);
	}
	int get = 1;
	while(get){
		printf("----------------\n");
		printf("1. schedual once\n0. exit\n");
		printf("----------------\n");
		scanf("%d", &get);
		if(get) { 
			printf("Sched  : ");
			if (!isEmpty(runningQueue)){
				//if not empty
				deQueue(runningQueue, &temp);
				temp.ptime -= TS;
				//if run out time
				if (temp.ptime<=0)
				{
					temp.pstate = FREE;
					temp.ptime = 0;
					//recycle
					enQueue(freeQueue, temp);
				}else{
					//get ready
					temp.pstate = READY;
					enQueue(readyQueue, temp);
					printf("%s(Running -> Ready)",temp.pname);
				}
			}
			if (!isEmpty(readyQueue)){
				deQueue(readyQueue, &temp);
				//change to running
				temp.pstate = RUNNING;
				enQueue(runningQueue, temp);
				printf("%s(Ready -> Running)\n", temp.pname);
				printf("Running: %s\n", temp.pname);
				printf("Ready  : ");
				pcb *pb = readyQueue->front->pnext;
				while(pb){
					printf("%s", pb->pname);
					printf("<=");
					pb = pb->pnext;

				}
				printf("[-]\n");
			}else{
				printf("Finished!\n");
			}
		}//if
		else exit(0);
	}//while
	return 0;
}