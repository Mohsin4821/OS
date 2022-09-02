#include<stdio.h>
#include<stdlib.h>

typedef struct process{
	int pid,at,bt,ct,wt,tt,rt,flag;
}pro;
int temp[10];

void sort(pro p[],int n){
	pro t;
	int i,j;
	for(j=0;j<n;j++){
		for(i=0;i<n-j-1;i++){
			if(p[i].at>p[i+1].at){
				t=p[i];
				p[i]=p[i+1];
				p[i+1]=t;
				
				int a=temp[i];
				temp[i]=temp[i+1];
				temp[i+1]=a;
			}
		}	
	}
}

void ttavg(pro p[],int n){
	int i;
	for(i=0;i<n;i++){
		p[i].tt=p[i].ct-p[i].at;
	}
}

void wtavg(pro p[],int n){
	int i;
	for(i=0;i<n;i++){
		p[i].wt=p[i].tt-temp[i];
	}
}

void schedule(pro p[],int n,int tq){
	int i,completed=0,rqueue[10],f=0,r=-1,pid[10],ctime[10],k=0,len=0,cur,time=p[0].at;
	
	r=(r+1)%n;
	rqueue[r]=0;
	pid[0]=0;
	
	while(completed!=n){
		cur=rqueue[f];
		f=(f+1)%n;
		
		if(p[cur].rt==-1){
			p[cur].rt=time-p[cur].at;
		}
		
		if(tq>=p[cur].bt){
			time+=p[cur].bt;
			p[cur].bt=0;
		}
		else{
			time+=tq;
			p[cur].bt-=tq;
		}
		p[cur].flag=1;
		p[cur].ct=time;
		
		if(pid[k]!=p[cur].pid){
			k++;
			len++;
		}
		pid[k]=p[cur].pid;
		ctime[k]=p[cur].ct;
		
		for(i=0;i<n;i++){
			if(p[i].at>time||p[i].bt==0||p[i].flag==1)continue;
			r=(r+1)%n;
			rqueue[r]=i;
			p[i].flag=1;
		}
		
		if(p[cur].bt==0)completed++;
		else{
			r=(r+1)%n;
			rqueue[r]=cur;
		}
	}
	
	printf("======GANTTCHART=====\n");
	
	printf("| ");
	for(i=1;i<=len;i++){
		printf("p%d |",pid[i]);
	}
	printf("\n");
	for(i=1;i<=len;i++){
		printf(" %2d",ctime[i]);
	}
	printf("\n");
}

void calavg(pro p[],int n,int tq){
	sort(p,n);
	schedule(p,n,tq);
	ttavg(p,n);
	wtavg(p,n);
	
	int i,tott=0,totwt=0;
	
	printf("\nPID\tAT\tBT\tCT\tWT\tTT\tRT\n");
	for(i=0;i<n;i++){
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,temp[i],p[i].ct,p[i].wt,p[i].tt,p[i].rt);
		tott +=p[i].tt;
		totwt +=p[i].wt;
	}
	
	printf("Average tt=%f\n",(float)tott/(float)n);
	printf("Average wt=%f\n",(float)totwt/(float)n);
}

void main(){
	int n,tq;
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	pro p[n];
	printf("Enter the time quantum\n");
	scanf("%d",&tq);
	
	int i;
	for(i=0;i<n;i++){
		printf("Enter AT and BT for p%d:",i+1);
		scanf("%d%d",&p[i].at,&p[i].bt);
		p[i].pid=i+1;
		temp[i]=p[i].bt;
	}
	
	for(i=0;i<n;i++){
		p[i].flag=0;
		p[i].rt=-1;
	}
	
	calavg(p,n,tq);
}
