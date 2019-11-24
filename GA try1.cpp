#include <bits/stdc++.h>
#define pb push_back
#define population_size 500
#define N 8
using namespace std;
int rand_range(int start,int end)
{
	int range=end-start+1;
	int r=rand()%range;
	return start+r;
	
}
 
class Individual
{
	public:
	int fitness_score=0;
	int arr[N]={0};
	int cal_fitness();
	Individual(int a[])
	{
		for(int i=0;i<N;i++)	
			arr[i]=a[i];
			
		fitness_score = cal_fitness();
	}
};

Individual mate(Individual parent1,Individual parent2)
{
	int a[N];
	for (int i=0;i<N;i++)
	{
		int p=rand_range(0,100)/100;
		if(p<0.6)
		{
			a[i]=parent1.arr[i];
			
		}
		else if(p<0.9)
		{
			a[i]=parent2.arr[i];
		}
		else
		{
			//mutation
			a[i]=rand_range(0,N-1);
		}
		
	}
	Individual offspring(a);
	return offspring;
	
}
int Individual::cal_fitness() 
{
	int v[N],count=0;
	for(int i=0;i<N;i++)
	{
		v[i]=arr[i];
	}
	sort(v,v+N);
	for(int i=0;i<N;i++)
	{
		auto it2=upper_bound(v,v+N,v[i]);
		auto it1=lower_bound(v,v+N,v[i]);
		count+=it2-it1-1;
	}
	count=count/2;
	
	int t1,t2=0;
	int size=N;
	//int c[8]={3,0,4,7,1,6,2,5};
	int f1[N],f2[N];
	for (int i=0;i<size;i++)
	{
		f1[i]=arr[i]-i;
		f2[i]=1+size-arr[i]-i;
	}
	sort(f1,f1+size);
	sort(f2,f2+size);
	for (int i=1;i<size;i++)
	{
		if(f1[i] == f1[i-1])
			t1++;
		if (f2[i] == f2[i-1])	
		{
			t2++;
		}
	}
	return t1+t2+count;	
}

Individual create_gnome()
{
	int arr[N]={0};
	for (int i=0;i<N;i++)
	{
		//generate random  num between 0 -8
		arr[i]=rand_range(0,N-1);
	}
	Individual offspring(arr);// =  Individual(arr);
	return offspring;
}

bool operator<(const Individual &ind1, const Individual &ind2) 
{ 
	return ind1.fitness_score < ind2.fitness_score; 
} 

int main()
{
	srand(time(0));
	//8-Queens using GA
	//step 1 ..representation of population using class
	//step2 .. Generate initial population
	vector <Individual> population;
	int gen=0;
	bool found=0;
		//let population size be 100
	for(int i=0;i<population_size;i++)
	{
		population.pb(create_gnome());
	}
	
	
	while (!found)
	{
		
		sort (population.begin(),population.end());
		if (population[0].fitness_score <=0)
		{
			found =true;
			break;
		}
		
		//otherwise generate new offsprings
		vector <Individual> new_gen ;
		//perform ellitism 10% of fittest goto next generation
		int s= 10*population_size/100;
		for (int i=0;i<s;i++)
		{
			new_gen.pb(population[i]);
		}
		//now fill 90% of population by 50% fittest population
		s=90*population_size/100;
		
		for (int i=0;i<s;i++)
		{
			//each time select a random individual from 0 to 50 and mate them to get a offspring
			//select two parents randomly
			//!!!!!!!!change it to Roullette wheel or any else selection mechanisms
			int r1=rand_range(0,50);
			int r2=rand_range(0,50);
			Individual parent1=population[r1];
			Individual parent2 = population[r2];
			Individual offspring = mate(parent1,parent2);
			new_gen.pb(offspring);
			
		}
		population = new_gen;
		cout << "Generation number :"<<gen;
		cout << "    Fittness score :"<<population[0].fitness_score<<"\n";
	gen++;		
	}
	cout << "--------------------------------------\n";
	cout <<"Generation number :"<<gen<<"\n";
	cout << "Fittness Score:"	<<population[0].fitness_score<<"\n";
	for (int i=0;i<N;i++)
	{
		cout << population[0].arr[i];
	}
	return 0;
}

