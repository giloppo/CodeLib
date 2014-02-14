#include "GameInitialize.h"

void GameInitialize(int n, int m, int iMine)
{
//------
//地雷數超出地圖大小則退出，或者也可以在外部判斷，可刪除
//------
	if(n * m < iMine)
	{
		return;
	}
//------
//生成隨機數種子，或者也可以在外部執行，可刪除
//------
	srand(GetTickCount());
//------
//生成(n + 2) * (m + 2)大小的地圖，最外圍用來簡化算法，不使用，同時開銷也不大
//------
	struct strSpace
	{
		int iState;
		int iNumMines;
	};
	strSpace ** SpaceInfo = new strSpace * [n + 2];
	for(int i = 0; i < n + 2; ++i)
	{
		SpaceInfo[i] = new strSpace[m + 2];
	}
//------
//初始化賦值，-1表示無雷，iNumMines表示一個格子周圍的地雷數，全部初始化為0
//------
	for(int i = 0; i < n + 2; ++i)
	{
		for(int j = 0; j < m + 2; ++j)
		{
			SpaceInfo[i][j].iState = -1;
			SpaceInfo[i][j].iNumMines = 0;
		}
	}
//------
//遍歷地雷初始化地圖
//------	
	for(int i = 0; i < iMine; ++i)
	{
		//------
		//在隨機一個空格中設置地雷（不包括最外圍）
		//------
		int iX = rand() % n + 1;
		int iY = rand() % m + 1;
		if(SpaceInfo[iX][iY].iState == -1)
		{
			SpaceInfo[iX][iY].iState = 9;//9表示有雷
			//------
			//將該雷周圍的所有格子的地雷數加1（如果周圍格子有雷則跳過）
			//------
			for(int j = iX - 1; j <= iX + 1; ++j)
			{
				for(int k = iY - 1; k <= iY + 1; ++k)
				{
					if(SpaceInfo[j][k].iState == -1)
					{
						++SpaceInfo[j][k].iNumMines;
					}
				}
			}
		}
		else
		{
			--i;//如果兩次取到同一個格子則重新取值，防止跳過
		}
	}
//------
//測試函數運行情況，可刪除
//------
	for(int i = 0; i < n + 2; ++i)
	{
		for(int j = 0; j < m + 2; ++j)
		{
			if(SpaceInfo[i][j].iState == 9)
			{
				cout << SpaceInfo[i][j].iState << " ";
			}
			else
			{
				cout << SpaceInfo[i][j].iNumMines << " ";
			}
		}
		cout << endl;
	}
//------
//釋放二維結構數組，或者可以在外部釋放，可刪除
//------
	for(int i = 0; i < n + 2; ++i)
	{
		delete []SpaceInfo[i];
	}
	delete []SpaceInfo;
}