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

int in(int x,int y) {return x>=0&&x<=8&&y>=0&&y<=8;}
int wei(int x1,int y1,int x2,int y2,int x3,int y3,int player)
{
	int flag1=(!in(x1,y1))|(in(x1,y1)&&board[x1][y1]==player);
	int flag2=(!in(x2,y2))|(in(x2,y2)&&board[x2][y2]==player);
	int flag3=(!in(x3,y3))|(in(x3,y3)&&board[x3][y3]==player);
	int flag4=in(x1,y1)&&in(x2,y2)&&in(x3,y3);
	return flag1&&flag2&&flag3&&flag4; 
}
int CalcValue(int x,int y,int nowplayer)
{
	int val=0;
	if(in(x-1,y-1)) val+=board[x-1][y-1]==nowplayer;
	if(in(x-1,y+1)) val+=board[x-1][y+1]==nowplayer;
	if(in(x+1,y-1)) val+=board[x+1][y-1]==nowplayer;
	if(in(x+1,y+1)) val+=board[x+1][y+1]==nowplayer;
	if(wei(x-1,y-1,x-1,y+1,x-2,y,nowplayer)) val+=4;
	if(wei(x-1,y+1,x+1,y+1,x,y+2,nowplayer)) val+=4;
	if(wei(x+1,y+1,x+1,y-1,x+2,y,nowplayer)) val+=4;
	if(wei(x+1,y-1,x-1,y-1,x,y-2,nowplayer)) val+=4; 
	
	if(in(x-1,y)) val-=board[x-1][y]==nowplayer;
	if(in(x+1,y)) val-=board[x+1][y]==nowplayer;
	if(in(x,y-1)) val-=board[x][y-1]==nowplayer;
	if(in(x,y+1)) val-=board[x][y+1]==nowplayer;
	
	int hit=0;
	if(in(x-1,y)) hit+=board[x-1][y]==-nowplayer;
	if(in(x+1,y)) hit+=board[x+1][y]==-nowplayer;
	if(in(x,y-1)) hit+=board[x][y-1]==-nowplayer;
	if(in(x,y+1)) hit+=board[x][y+1]==-nowplayer;
	if(hit>=2) val+=hit;
	
	return val;
}

int First_Decide(int x)
{
	vector<int> available_list; //�Ϸ�λ�ñ� 
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
			if (judgeAvailable(i,j,-1))
				available_list.push_back(i*9+j);
	int num=available_list.size(); 
//	return available_list[rand()%available_list.size()];
	int ans=0,mxval=-1,val=0;
	for(int i=0;i<num;i++)
	{
		int x=available_list[i]/9;
		int y=available_list[i]%9;
		val=CalcValue(x,y,-1);
		
		if(val==mxval&&rand()&1) ans=x*9+y; 
		if(val>mxval) mxval=val,ans=x*9+y;  
//		if(val) printf("(%d,%d) val=%d\n",x,y,val); 
	} 
	return ans;
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
