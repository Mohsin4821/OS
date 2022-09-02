#include<stdio.h>

typedef struct process{
	int pid,at,bt,ct,tt,wt,rt;
}pro;

void sort(pro p[],int n){
	pro temp,*p1,*p2;
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(p[i].at>p[i+1].at){
				p1=&p[i];
				p2=&p[i+1];
				
				temp=*p1;
				*p1=*p2;
				*p2=temp;
			}
		}
	}
}

void turnaround(pro p[],int n){
	int i;
	p[0].ct=p[0].at+p[0].bt;
	p[0].tt=p[0].ct;
	for(i=1;i<n;i++){
		p[i].ct=p[i-1].ct+p[i].bt;
		p[i].tt=p[i].ct-p[i].at;
	}
}

void waiting(pro p[],int n){
	int i;
	for(i=0;i<n;i++){
		p[i].wt=p[i].tt-p[i].bt;
		p[i].rt=p[i].wt;
	}
}
void avgtime(pro p[],int n){
	int i;
	turnaround(p,n);
	waiting(p,n);
	
	int tott=0;
	int totwt=0;
	printf("PID\tAT\tBT\tCT\tTT\tWT\tRT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt,p[i].rt);
		tott+=p[i].tt;
		totwt+=p[i].wt;
	}
	printf("Average tt=%f\n",(float)tott/(float)n);
	printf("Average wt=%f\n",(float)totwt/(float)n);
}

void gant(pro p[],int n){
int i;
	printf("%d|",p[0].at);
	for(i=0;i<n;i++){
		printf("|p%d||%d",i+1,p[i].ct);
	}
}

void main(){
	pro p[10];
	int i,n;
	
	printf("Enter the number of process\n");
	scanf("%d",&n);
	
	for(i=0;i<n;i++){
		printf("Enter pid,at,bt of process %d:",i+1);
		scanf("%d %d %d",&p[i].pid,&p[i].at,&p[i].bt);
	}
	
	sort(p,n);
	avgtime(p,n);
	gant(p,n);
}
