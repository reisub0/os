#include "process_sch.h"

void order_at(process p[])
{	
	for(int i=0;i<5;i++)
		for(int j=0;j<4-i;j++)
			if( p[j].get_at() > p[j+1].get_at() )
				{
					process temp = p[j];
					p[j] = p[j+1];
					p[j+1] = temp;					
				}				
}

process pt_high(process p[],int n)
{	process temp;
	for(int i=0;i<n-1;i++)
		if(p[i].get_pt() > p[i+1].get_pt() )
		{	temp = p[i];
			p[i] = p[i+1];
			p[i+1] = temp;
		}
	return p[n-1];
}


void priority_npe(process p[])
{	
	order_at(p);
	
	int k=5;
	int sysclock = 1;

	for(int x=0;x<5;x++)
	{	int n=0;
		for(int i=0;i<k;i++)
			if( sysclock > p[i].get_at() )
				n++;
		if(n==0)
		{	sysclock++;
			x--;
			continue;	
		}

		process np=pt_high(p,n);
			
		int i;
		for(i=0;i<k;i++)
			if( np.get_pid() == p[i].get_pid() )
				break;
		
		p[i].assign_rest( sysclock+p[i].get_bt()-1 );		
		p[i].print_pt();
		sysclock += p[i].get_bt();
		
		for(int j=i;j<k-1;j++)
			p[j] = p[j+1];
		k--;
	}

}		
