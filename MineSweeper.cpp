#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class box
{
	public:
		bool visited;
		bool bug;
		int count;
		
		box()	:	visited(false), bug(false), count(0)	{}
		void state()
		{
			if(!visited) cout<<"   ";
			else if(bug) cout<<"@@@";
			else if(count > 0) cout<<'<'<<count<<'>';
			else cout<<"// ";
		}
};

box mat[9][9];
int remaining = 72;

void display()
{
	system("cls"); cout<<"\n\n\n";
	cout<<"\t\t    ";
	for(int i=0; i<9; i++)	cout<<" "<<i+1<<"  ";
	cout<<"\n\t\t    "; 
	for(int i=0; i<9; i++)	cout<<"___ ";
	cout<<'\n';
	for(int i=0; i<9; i++)
	{
		cout<<"\t\t   |";
		for(int j=0; j<9; j++)	cout<<"   |";
		cout<<"\n\t\t "<<i+1<<" |";
		for(int j=0; j<9; j++)
		{
			mat[i][j].state(); cout<<'|';
		}
		cout<<"\n\t\t   |";
		for(int j=0; j<9; j++)	cout<<"___|";
		cout<<'\n';
	}
	cout<<"\n\n\n\t\t";
}

void changeCell(int i, int j)
{
	if(i<0 || i>8 || j<0 || j>8) return;
	if(mat[i][j].visited) return;
	
	mat[i][j].visited = true;
	remaining--;
	if(mat[i][j].count > 0) return;
	
	changeCell(i-1,j-1); changeCell(i-1,j); changeCell(i-1,j+1);
	changeCell(i,j-1); changeCell(i,j+1);
	changeCell(i+1,j-1); changeCell(i+1,j); changeCell(i+1,j+1);
}

bool clickCell(int i, int j)
{
	if(i<0 || i>8 || j<0 || j>8) return true;
	if(mat[i][j].visited) return true;
	if(mat[i][j].bug) return false;
	changeCell(i,j);
	return true;
}

int tellVal(int i, int j)
{
	if(i<0 || i>8 || j<0 || j>8) return 0;
	if(mat[i][j].bug) return 1;
}

void setCount(int i, int j)
{
	int cnt;
	if(mat[i][j].bug) return;
	cnt = tellVal(i-1,j-1)+tellVal(i-1,j)+tellVal(i-1,j+1);
	cnt+= tellVal(i,j-1)+tellVal(i,j+1);
	cnt+= tellVal(i+1,j-1)+tellVal(i+1,j)+tellVal(i+1,j+1);
	mat[i][j].count = cnt;
}


int main()
{
	int a,b,c;
	char temp;
	bool win;
	srand(time(NULL));
	for(int i=0; i<9; i++)
	{
		do
		{
			a = rand()%9;
			b = rand()%9;
		}while(mat[a][b].bug);
		mat[a][b].bug = true;
	}
	for(int i=0; i<9; i++)
	for(int j=0; j<9; j++) setCount(i,j);
	display();
	while(1)
	{
		cout<<"Enter your choice --   ";
		cin>>c;
		a = c/10;
		b = c%10;
		if(clickCell(a-1,b-1))
		{
			if(!remaining)
			{
				win = true;
				break;
			}
			display();
		}
		else
		{
			win = false;
			break;
		}
	}
	
	for(int i=0; i<9; i++)
	for(int j=0; j<9; j++) mat[i][j].visited = true;
	display();
	
	if(win)		cout<<"******** YOU WON !! **************\n\n\n\n";
	else 		cout<<"\a*********  YOU LOST !  **************\n\n\n\n";
	cout<<"Enter anything to exit .. ";
	cin>>temp;
	return 0;
}
