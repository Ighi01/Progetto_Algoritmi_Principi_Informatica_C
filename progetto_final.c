#include<stdio.h>
#include<stdlib.h>
#define MAX 4294967295

typedef enum{
    false,true
}bool;


void max_heapify(unsigned int* heap_peso,unsigned int* heap_key,unsigned int n,unsigned int i)
{
    unsigned int posmin,right,left,temp2;
    unsigned int temp1;

    left=2*i+1;
    right=2*i+2;
    posmin=i;

    if(left<n && heap_peso[left]>heap_peso[i])
    {
        posmin=left;
    }
    if(right<n && heap_peso[right]>heap_peso[posmin])
    {
        posmin=right;
    }
    if(posmin!=i)
    {
        temp1=heap_peso[posmin];
        temp2=heap_key[posmin];
        heap_peso[posmin]=heap_peso[i];
        heap_key[posmin]=heap_key[i];
        heap_key[i]=temp2;
        heap_peso[i]=temp1;
        max_heapify(heap_peso,heap_key,n,posmin);
    }
}


void costruisci_maxheap(unsigned int* A,unsigned int *B,unsigned int n)
{
    unsigned int med,i;
    med=n/2;
    for(i=med+1;i>0;i--)
    {
        unsigned int j=i-1;
        max_heapify(A,B,n,j);
    }
}


void write_end(unsigned int n)
{
    unsigned int x,k=n/10;
    if(k!=0)
    {
        write_end((unsigned int) n/10);
        x=n%10;
        char d=x+'0';
        putchar_unlocked(d);
    }
    else
    {
        x=n%10;
        char d=x+'0';
        putchar_unlocked(d);
    }
}


unsigned int read()
{
    unsigned int n=0;
    char x='a';
    x=getchar_unlocked();
    while(x>='0' && x<='9')
    {
        n=n*10;
        n=n+(x-'0');
        x=getchar_unlocked();
    }
    return n;
}


void stampa_classifica(unsigned int* V,unsigned int n)
{
    if(n==0)
    {
        putchar_unlocked('\n');
    }
    else
    {

        for(unsigned int i=0;i<n;i++)
        {
            if(i+1==n)
            {   
                write_end(V[i]);
                putchar_unlocked('\n');
            }
            else
            {
                write_end(V[i]);
                putchar_unlocked(' ');
            }
        }
    }
}

unsigned int mindist(unsigned int *distanza, bool *visitato,unsigned int dim)   
{
    unsigned int min=MAX,v,nodo=0;
  
    for (v=0;v<dim;v++)
        if (visitato[v]==false && distanza[v]<=min)
        {
            min=distanza[v];
            nodo=v;
        }
  
    return nodo;
}

unsigned int dijkstra_naif(unsigned int zero,unsigned int **matrice,unsigned int n)
{
    unsigned int distanze_minime[n-1]; 
    unsigned int sum=0,i,j,nodo_min;
    bool visitato[n-1];

    for (i=0;i<n-1;i++)
    {
        if(matrice[0][i+1]!=0)
        {
            distanze_minime[i]=matrice[0][i+1];
        }
        else
        {
            distanze_minime[i]=MAX;
        }

        visitato[i]=false;
    }
  
    for (j=0;j<n-1;j++) 
    {
      
        nodo_min=mindist(distanze_minime,visitato,n-1);
        visitato[nodo_min]=true;
        
        for (i=0;i<n-1;i++)
        {
            if(i!=nodo_min)
            {   
                if (visitato[i]==false && matrice[nodo_min+1][i+1]!=0 && distanze_minime[nodo_min]!= MAX && distanze_minime[nodo_min]+matrice[nodo_min+1][i+1]<distanze_minime[i])
                {   
                    distanze_minime[i] = distanze_minime[nodo_min] + matrice[nodo_min+1][i+1];
                }
            }
        }
    }

    for (i=0;i<n-1;i++)
    {
        if(distanze_minime[i]!=MAX) 
        {
            sum=sum+distanze_minime[i];
        }
    }
    return sum;
}





int main()
{
    unsigned int n,x,i=0,j=0,indice=0,input,sum_nodi_da_0=0;
    char *comand=malloc(15*sizeof(char));
    bool check;

    n=read(); 
    x=read(); 

    unsigned int** M = (unsigned int**)malloc(n * sizeof(unsigned int*));
    unsigned int* classifica_pesi=malloc(10*sizeof(unsigned int));
    unsigned int* classifica_valori=malloc(10*sizeof(unsigned int));
    unsigned int eseguito=1;

    for(unsigned int i=0;i<n;i++)
    {
        M[i] = (unsigned int*)malloc(n * sizeof(unsigned int));
    }

    while(fgets(comand, 15 , stdin) != NULL)
    {

        if(comand[0] == 'A') 
        {
            if(indice<x && indice==eseguito*10-1)
            {
                eseguito++;
                classifica_pesi=realloc(classifica_pesi,10*eseguito*sizeof(unsigned int));
                classifica_valori=realloc(classifica_valori,10*eseguito*sizeof(unsigned int));
            }

            check=true;

            i=0;
            while(i<n)
            {
                j=0;
                while(j<n)
                {
                    input=read();
                   
                    if(i==0 || check==false)
                    {
                        M[i][j]=input;
                      

                        if(check==true && i==0 && j>1)
                        {
                            if(M[i][j]!=M[i][j-1])
                            {
                                check=false;
                            }
                        }
                    }
                j++;
                }
            i++;
            }
            
            if(check==false)
            {
                sum_nodi_da_0= dijkstra_naif(0,M,n); 

                if(indice<x)
                {
                    classifica_pesi[indice]=sum_nodi_da_0;
                    classifica_valori[indice]=indice;
                }
                
                if(indice==x)
                {
                    costruisci_maxheap(classifica_pesi,classifica_valori,x);
                }
                if(indice>x && sum_nodi_da_0<classifica_pesi[0])
                {
                    classifica_pesi[0]=sum_nodi_da_0;
                    classifica_valori[0]=indice;
                    max_heapify(classifica_pesi,classifica_valori,x,0);
                }
               
            }
            else
            {
                unsigned int T=M[0][1]*(n-1);

                if(indice<x)
                {
                    classifica_pesi[indice]=T;
                    classifica_valori[indice]=indice;
                }
                
                if(indice==x)
                {
                    costruisci_maxheap(classifica_pesi,classifica_valori,x);
                }
                if(indice>x && T<classifica_pesi[0])
                {
                    classifica_pesi[0]=T;
                    classifica_valori[0]=indice;
                    max_heapify(classifica_pesi,classifica_valori,x,0);
                }
            }
            indice++;
        }

        else if(comand[0]=='T')
        {
            if(indice<x)
            {
                stampa_classifica(classifica_valori,indice);
            }
            else
            {
                stampa_classifica(classifica_valori,x);
            } 
            
        }
    }
}