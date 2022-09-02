#include<stdio.h>

typedef struct process
{
int pid,at,bt,ct,wt,tt,rt;
}pro;
int temp[10];

void sortat(pro p[], int n)
{
    for (int j = 0; j < n - 1; j++)
    {
        for (int i = 0; i < n - j - 1; i++)
        {
            if (p[i].at > p[i + 1].at)
            {
                pro t = p[j];
                p[j] = p[j + 1];
                p[j + 1] = t;
               
                int temporary=temp[i];
                temp[i]=temp[i+1];
                temp[i+1]=temporary;
            }
        }
    }
}

void waittime(pro p[],int n){
	int i;
	for(i=0;i<n;i++){
		p[i].wt=p[i].tt-temp[i];
	}	
}


void turnaroundtime(pro p[],int n){
	int i;
	for(i=0;i<n;i++)
		p[i].tt=p[i].ct-p[i].at;
}

void schedule(pro p[],int n){

	int m=0,min=0,time=p[0].at,j,completed=0;
	int pid[n],ctime[n],k=0,len=0;
    pid[0]=0;
	while(completed!=n){
		m=999;
	
		for(j=0;j<n;j++){						///important loop 
			if((p[j].at>time)||(p[j].bt==0))	// it checks wheather the process has not arived
				continue;						// if not arrived continue i.e check on with next process
			
			if(m>p[j].bt){						//it checks which is shortest job
				min=j;
				m=p[min].bt;
			}
		}
		
		if (p[min].rt == -1)
            p[min].rt = time - p[min].at;
	
		time++;
		p[min].bt--;
		p[min].ct=time;
		
		if (p[min].pid != pid[k])
        {
            k++;
            len++;
        }
        pid[k] = p[min].pid;
        ctime[k] = time;
	
		if(p[min].bt==0)
			completed++;						//process has completed its execution
	}
	
	printf("\n=============GANTTCHART=============\n");
	
    for (int i = 1; i <= len; i++)
        printf(" ----");
    printf("\n|");
    for (int i = 1; i <= len; i++)
        printf(" P%d |", pid[i]);
    printf("\n");
    for (int i = 1; i <= len; i++)
        printf(" ----");
    printf("\n");
    printf("%d", p[0].at);
    for (int i = 1; i <= len; i++)
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


int main(){
	pro p[10];
	int n,i;
	printf("Enter the number of processes\n");
	scanf("%d",&n);\

	for(i=0;i<n;i++){
		printf("Enter pid, arrival time and burst time of process %d:\n",(i+1));
		scanf("%d %d %d",&p[i].pid,&p[i].at,&p[i].bt);
		temp[i]=p[i].bt;
		p[i].rt=-1;
	}

	sortat(p,n);
	avgtime(p,n);
}
