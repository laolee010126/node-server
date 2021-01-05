#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <time.h> 
#include <queue>

using namespace std;

int board[9][9],xzy;

bool dfs_air_visit[9][9];
const int cx[]={-1,0,1,0};
const int cy[]={0,-1,0,1};

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
	//1.有棋子 
	if (board[fx][fy]) return false;
	//2.下上去后自己气断了 
	board[fx][fy] = col;
	memset(dfs_air_visit, 0, sizeof(dfs_air_visit));
	if (!dfs_air(fx, fy))
	{
		board[fx][fy] = 0;
		return false; 
	}
	//3.下上去后把别人围住了 
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
int main() 
{
	freopen("shengfu.in","r",stdin);
	freopen("shengfu.out","w",stdout);

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
	int col=cnt1==cnt2?-1:1;
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			if(judgeAvailable(i,j,col)) {cout<<0;return 0;}
	cout<<(col==-1?2:1);
}
