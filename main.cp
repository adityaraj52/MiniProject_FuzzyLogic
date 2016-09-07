#include<stdio.h>
#include<iostream>
#include "math.h"
int reach[20];
int visited[10]={0},stack[10],top=-1, m=0;

using namespace std;

// Defining structures
struct data
{
    float x=0;
    float y=0;
    float z=0;
    int flag=0;
}a[10][10];

data path[10];

struct nu
{
    float val;
    int degree;
};


//Defining Functions to alculate minimum of the array upto desired length value
data calc_min(data a[], int n)
{
    data small;
    small.x=999;small.y=999;small.z=999;
    for(int i=0;i<n;i++)
    {
        //cout<<"\n\n"<<i+1<<"\t\t"<<a[i].x<<"\t"<<a[i].y<<"\t"<<a[i].z<<"\n";
        if (a[i].x)
        {
            if(a[i].x<small.x)
                small.x=a[i].x;
            if(a[i].y<small.y)
                small.y=a[i].y;
            if(a[i].z<small.z)
                small.z=a[i].z;
        }
    }
    return small;
}

// Calculate Minimum of two numbers
float cal_min(float a, float b)
{
    if(a<=b)return a;
    else return b;
}

// Calculate Maximum of two numbers
float cal_max(float a, float b)
{
    if(a>=b)return a;
    else return b;
}

//Computation for calculating similarity degree
data compute(data a, data b)
{
    data c;
    c.x=cal_min(a.x, b.x);
    c.z=cal_min(cal_min(a.z, b.z), cal_max(a.y, b.y));
    if(cal_min(a.y, b.y)<=cal_max(a.x, b.x))
        c.y=cal_min(a.y, b.y);
    else
        c.y=(((a.y*b.y)-(a.x*b.x))/((a.y+b.y)-(a.x+b.x)));
    return c;
}

//DFS Search
void dfs(int v)
{
    int i;
    reach[v]=1;
    for(i=1;i<=6;i++)
        if(a[v][i].flag && !reach[i])
        {
            printf("\n %d->%d",v,i);
            dfs(i);
        }
}

//
int find(int a1,int b1,int size)
{
    if(size>1)
    {
        cout<<endl<<"Paths Available are: "<<endl;
        int i=a1,j;
        visited[i]=1;
        stack[++top]=a1;
        for(j=1;j<=size+1;++j)
        {
            if(a[i][j].flag==1 && visited[j]==0)
            {
                visited[j]=1;
                stack[++top]=j;
                i=j;
                j=1;
            }
            if(stack[top]==b1)
            {
                cout<<"Path "<<m+1<<": ";
                for(int x=0;x<=top;++x)
                {
                    cout<<stack[x]<<" ";
                    if (x<top) {
                        path[m].x+=a[stack[x]][stack[x+1]].x;
                        path[m].y+=a[stack[x]][stack[x+1]].y;
                        path[m].z+=a[stack[x]][stack[x+1]].z;
                    }
                }
                cout<<endl;
                ++m;
                j=stack[top];
                visited[j]=0;
                i=stack[--top];
            }
            if(j>=size)
            {
                j=stack[top];
                visited[j]=0;
                i=stack[--top];
            }
            if(top==-1)
                break;
        }
        return 1;
    }
    else
        return 0;
}

int main()
{
    int node_count, total_count=0;
    cout<<"Enter Number of nodes for the graph ";
    do{
        cin>>node_count;
        if(node_count<2)
            cout<<"\nCount of nodes should be atleast 2\nEnter number of nodes again ";
    }
    while (node_count<2);
    cout<<"Enter node to node arc values(a, b,c) in the form of adjacency matrix: "<<endl;
    for (int i=1; i<=node_count; ++i)
        for (int j=i+1; j<=node_count; ++j) {
            int flag;
            if(i!=j)
            {
                cout<<endl<<"Current Node is "<<i<<" to "<<j;
                cout<<endl<<"Enter '1' if node Exists else enter '0' ";
                cin>>flag;
                
                if(flag){
                    total_count++;
                    a[i][j].flag=a[j][i].flag=1;
                    cin>>a[i][j].x;
                    cin>>a[i][j].y;
                    cin>>a[i][j].z;
                    a[j][i].x=a[i][j].x;
                    a[j][i].y=a[i][j].y;
                    a[j][i].z=a[i][j].z;
                    continue;
                }
                else
                    a[i][j].flag=0;
                continue;
            }
        }
    int start_node, dest_node;
    
    do
    {
        cout<<endl<<"Enter starting node ";
        cin>>start_node;
        
        cout<<"Enter destination node ";
        cin>>dest_node;
        
        if(start_node<1 || dest_node>node_count)
            cout<<"\nOut Of bounds Check Start and end node\n ";
    }while (start_node<1 || dest_node>node_count);
    
    find(start_node, dest_node, node_count);
    data min[2];
    min[0]=calc_min(path,m);
    
    cout<<"\n";
    cout<<"Path Cost: ";
    for(int i=0;i<m;++i)
        cout<<"\n"<<"PATH "<<i+1<<":\t"<<path[i].x<<" "<<path[i].y<<" "<<path[i].z;
    
    cout<<"\n\nCalculating Lmin (a, b, c)";
    cout<<"\na"<<"\tb"<<"\tc";
    cout<<"\n\n"<<min[0].x<<"\t"<<min[0].y<<"\t"<<min[0].z;
    
    cout<<"\n\nComputing (a,b,c)";
    cout<<"\nIterations"<<"\ta"<<"\tb"<<"\tc";
    
    data cz[2];
    int i=1;
    cz[0]=path[0];
    
    while(i<m){
        cz[1]=compute(cz[0],path[i]);
        //cout<<"\n\n"<<i-1<<"\t\t"<<cz[1].x<<"\t"<<cz[1].y<<"\t"<<cz[1].z<<"\n";
        if(i==1)
            cz[0]=cz[1];
        cz[0]=calc_min(cz, 2);
        i++;
        cout<<"\n"<<i-1<<"\t\t\t"<<cz[0].x<<"\t"<<cz[0].y<<"\t"<<cz[0].z;
        
    }
    
    cout<<"\n\nAccepted Val"<<"\n"<<cz[0].x<<"\t\t"<<cz[0].y<<"\t"<<cz[0].z<<"\n";
    data Lmin=cz[0];
    
    
    cout<<"\n\nCalculating Similarity degree By finding Euclidean distance \n";
    nu s[m];
    
    for(int i=0;i<m;++i)
    {
        s[i].val=pow((pow((path[i].x-Lmin.x), 2)+pow((path[i].y-Lmin.y), 2)+pow((path[i].z-Lmin.z), 2)), 0.5);
        s[i].degree=i+1;
        cout<<"\nPATH "<<s[i].degree<<"\t"<<s[i].val;
    }
    
    
    cout<<"\n\nRank\t"<<"Optimum Path"<<"\t"<<"Similarity Degree\n";
    
    for(int i=0;i<m;i++)
        for(int j=i+1;j<m;j++)
            if(s[i].val>s[j].val)
            {
                nu temp=s[i];
                s[i]=s[j];
                s[j]=temp;
            }
    
    for(int i=0;i<m;++i)
        cout<<i+1<<"\t\tPATH "<<s[i].degree<<"\t\t\t\t"<<s[i].val<<"\n";
}

/* Defining node values
 a[1][2].x=1;
 a[1][2].y=3;
 a[1][2].z=4;
 
 a[1][3].x=2;
 a[1][3].y=4;
 a[1][3].z=5;
 
 a[2][4].x=1;
 a[2][4].y=2;
 a[2][4].z=3;
 
 a[2][5].x=2;
 a[2][5].y=4;
 a[2][5].z=6;
 
 a[3][5].x=2;
 a[3][5].y=5;
 a[3][5].z=6;
 
 a[4][6].x=2;
 a[4][6].y=3;
 a[4][6].z=8;
 
 a[5][6].x=3;
 a[5][6].y=5;
 a[5][6].z=7;
 */

/*{
 cout<<"\n\t\t\t"<<"1-------------------2-------------------4";
 cout<<"\n\t\t\t"<<"|     (1, 3, 4)     |       (1, 2, 3)   |";
 cout<<"\n\t\t\t"<<"|    "<<"               |"<<"                   |";
 cout<<"\n\t\t\t"<<"|    "<<"               |"<<"                   |";
 cout<<"\n\t"<<"       (2, 4, 5)|    "<<"      (2, 4, 6)|"<<"                   |"<<"(2, 3, 8)";
 cout<<"\n\t\t\t"<<"|    "<<"               |"<<"                   |";
 cout<<"\n\t\t\t"<<"|    "<<"               |"<<"                   |";
 cout<<"\n\t\t\t"<<"|    "<<"               |"<<"                   |";
 cout<<"\n\t\t\t"<<"3-------------------5-------------------6";
 cout<<"\n\t\t\t"<<"     (2, 5, 6)            (3, 5, 7)";
 cout<<"\n \nPossible Paths are \n\nPATH 1 \t 1-2-4-6 \nPATH 2 \t 1-2-5-6 \nPATH 3 \t 1-3-5-6";
 }*/

