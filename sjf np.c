#include<stdio.h>

typedef struct process
{
int pid,at,bt,ct,wt,tt,rt;
}pro;
int temp[10];

void sortat(pro p[], int n)
{
    pro t, *p1, *p2;
    int i,j;
    for (j = 0; j < n - 1; j++)
    {
        for (i = 0; i < n - j - 1; i++)
        {
            if (p[i].at > p[i + 1].at)
            {
                p1 = &p[i];
                p2 = &p[i + 1];
                t = *p1;
                *p1 = *p2;
                *p2 = t;
              
                int temporary=temp[i];
                temp[i]=temp[i+1];
                temp[i+1]=temporary;
            }
        }
    }
}

void waittime(pro p[],int n){
	int i;
	for(i=0;i<n;i++)
	{
		p[i].wt=p[i].tt-temp[i];
		p[i].rt=p[i].wt;
	}
}


void turnaroundtime(pro p[],int n){
	int i;
	for(i=0;i<n;i++)
		p[i].tt=p[i].ct-p[i].at;
}

void schedule(pro p[],int n){
	int m=0,min=0,time=p[0].at,i,j;
	int pid[n],ctime[n],k=0;
	for(i=0;i<n;i++)
	{
		m=999;
		for(j=0;j<n;j++)
		{
			if((p[j].at>time)||(p[j].bt==0))
			continue;
			
			if(m>p[j].bt){
				min=j;
				m=p[min].bt;
			}
		}

		time+=p[min].bt;
		p[min].bt=0;
		p[min].ct=time;
		
		pid[k]=p[min].pid;
		ctime[k]=p[min].ct;
		k++;
	}
	
 	printf("\n=============GANTTCHART=============\n");
    
    printf("|");
    for (i = 0; i < n; i++)
        printf(" P%d |", pid[i]);
    printf("\n");
    
    printf("%d", p[0].at);
    for (i = 0; i < n; i++)
        printf("   %2d", ctime[i]);
    printf("\n");
}

void avgtime(pro p[],int n){
	int totalwt=0,totaltat=0,i;
	
	schedule(p,n);
	turnaroundtime(p,n);
	waittime(p,n);
	
	printf("pid\tAT\tBT\tCT\tWT\tTT\n");
	for(i=0;i<n;i++){
		totalwt+=p[i].wt;
		totaltat+=p[i].tt;
		
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,temp[i],p[i].ct,p[i].wt,p[i].tt);
	}
	
	printf("Avg WT = %f\n",(float)totalwt/(float)n);
	printf("Avg TT = %f\n",(float)totaltat/(float)n);
}


void main(){
	pro p[10];
	int n,i;
	printf("Enter the number of processes\n");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("Enter  arrival time and burst time of process %d:\n",(i+1));
		scanf("%d %d",&p[i].at,&p[i].bt);
		p[i].pid=i+1;
		temp[i]=p[i].bt;
	}
	sortat(p,n);
	avgtime(p,n);
}
