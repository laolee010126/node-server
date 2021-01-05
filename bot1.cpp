#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <time.h> 
#include <queue>

using namespace std;

int board[9][9],xzy;

bool dfs_air_visit[9][9];
const int cx[]={-1,0,1,0};
const int cy[]={0,-1,0,1};
//true: has air
bool dfs_air(int fx, int fy)
{
	dfs_air_visit[fx][fy] = true;
	bool flag=false;
	for (int dir = 0; dir < 4; dir++)
	{
		int dx=fx+cx[dir], dy=fy+cy[dir];
		if (dx<0||dx>8||dy<0||dy>8) continue;
		if (board[dx][dy] == 0)	flag=true;
		if (board[dx][dy] == board[fx][fy] && !dfs_air_visit[dx][dy])
			if (dfs_air(dx, dy)) flag=true;
	}
	return flag;
}

//true: available
bool judgeAvailable(int fx, int fy, int col)
{
	//1.������ 
	if (board[fx][fy]) return false;
	//2.����ȥ���Լ������� 
	board[fx][fy] = col;
	memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
	if (!dfs_air(fx, fy))
	{
		board[fx][fy] = 0;
		return false; 
	}
	//3.����ȥ��ѱ���Χס�� 
	for (int dir = 0; dir < 4; dir++)
	{
		int dx=fx+cx[dir], dy=fy+cy[dir];
		if (dx<0||dx>8||dy<0||dy>8) continue;
		if (board[dx][dy] && !dfs_air_visit[dx][dy])
			if (!dfs_air(dx, dy))
			{
				board[fx][fy]  = 0;
				return false;
			}
	}
	board[fx][fy]  = 0;
	return true;
}

int First_Decide(int x)
{
	vector<int> available_list; //�Ϸ�λ�ñ� 
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
			if (judgeAvailable(i,j,-1))
				available_list.push_back(i*9+j);
	return available_list[rand()%available_list.size()];
}
int Work()
{
 
//Part 2 ���о���
	//ע�����㣺1.����xy����ͬ������
	//2.�Լ���-1��������1 
	int res=0,result; 
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(board[i][j]==0) res++;
	result=First_Decide(-1);
	return result;
}

int main()
{
	freopen("bot.in","r",stdin);
	freopen("bot.out","w",stdout);
	
	int x,cnt1=0,cnt2=0;
	for(cin>>x;x;cin>>x)
	{
		int i=x/10,j=x%10;
		board[i-1][j-1]=-1;cnt1++;//black 
	}
	for(cin>>x;x;cin>>x)
	{
		int i=x/10,j=x%10;
		board[i-1][j-1]=1;cnt2++;//white		
	}
	if(cnt2<cnt2)//�Լ��ǰ��ӣ�������ת
		for(int i=0;i<9;i++)
			for(int j=0;j<9;j++)
				board[i][j]=-board[i][j];
	int result=Work();
	int decidex=result/9,decidey=result%9;
	cout<<decidex+1<<" "<<decidey+1;
}
