#include "Brainiac.h"

BOOL GameInitialize(HINSTANCE hinstance)
{
	g_pGame = new GameEngine(hinstance, "Brainiac", "Brainiac", ID_ICON1, ID_ICON1, 616, 659);
	if(g_pGame == NULL)
	{
		return FALSE;
	}

	g_pGame -> SetFramRate(60);

	g_hInstance = hinstance;

	return TRUE;
}

void GameStart(HWND hWindow)
{
	srand(GetTickCount());

	g_hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
	g_hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow), g_pGame -> GetWidth(), g_pGame -> GetHeight());
	SelectObject(g_hOffscreenDC, g_hOffscreenBitmap);

	HDC hDC = GetDC(hWindow);
	
	g_pGalaxyBitmap = new Bitmap(hDC, ID_BACKGROUND, g_hInstance);
	g_pPlanetBitmap[0] = new Bitmap(hDC, ID_IMAGE09, g_hInstance);
	g_pPlanetBitmap[1] = new Bitmap(hDC, ID_IMAGE02, g_hInstance);
	g_pPlanetBitmap[2] = new Bitmap(hDC, ID_IMAGE03, g_hInstance);

	RECT rcBounds;
	GetClientRect(hWindow, &rcBounds);

	Sprite * pSprite;
	pSprite = new Sprite(g_pPlanetBitmap[0], rcBounds, BA_BOUNCE);
	pSprite -> SetVelocity(6, 4);
	pSprite -> SetNumFrames(1);
	pSprite -> SetFrameDelay(1);
	g_pGame -> AddSprite(pSprite);
	pSprite = new Sprite(g_pPlanetBitmap[1], rcBounds, BA_BOUNCE);
	pSprite -> SetVelocity(8, 2);
	g_pGame -> AddSprite(pSprite);
	pSprite = new Sprite(g_pPlanetBitmap[2], rcBounds, BA_BOUNCE);
	pSprite -> SetVelocity(-8, 4);
	g_pGame -> AddSprite(pSprite);
	pSprite = new Sprite(g_pPlanetBitmap[2], rcBounds, BA_BOUNCE);
	pSprite -> SetVelocity(14, -6);
	g_pGame -> AddSprite(pSprite);

	g_pDragSprite = NULL;

	g_pGame -> PlayMIDISong("D:\\Work\\C++\\testPJ\\SlideShow\\Res\\BGM.mid");
/*	g_pTiles[0] = new Bitmap(hDC, ID_IMAGE00, g_hInstance);
	g_pTiles[1] = new Bitmap(hDC, ID_IMAGE01, g_hInstance);
	g_pTiles[2] = new Bitmap(hDC, ID_IMAGE02, g_hInstance);
	g_pTiles[3] = new Bitmap(hDC, ID_IMAGE03, g_hInstance);
	g_pTiles[4] = new Bitmap(hDC, ID_IMAGE04, g_hInstance);
	g_pTiles[5] = new Bitmap(hDC, ID_IMAGE05, g_hInstance);
	g_pTiles[6] = new Bitmap(hDC, ID_IMAGE06, g_hInstance);
	g_pTiles[7] = new Bitmap(hDC, ID_IMAGE07, g_hInstance);
	g_pTiles[8] = new Bitmap(hDC, ID_IMAGE08, g_hInstance);

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			g_bTileStates[i][j] = FALSE;
			g_iTiles[i][j] = 0;
		}
	}

	for(int i = 0; i < 2; i++)
	{
		for(int j = 1; j < 9; j++)
		{
			int x = rand() % 4;
			int y = rand() % 4;
			while(g_iTiles[x][y] != 0)
			{
				x = rand() % 4;
				y = rand() % 4;
			}
			g_iTiles[x][y] = j;
		}
	}

	g_ptTile1.x = g_ptTile1.y = -1;
	g_ptTile2.x = g_ptTile2.y = -1;
	g_iMatches = g_iTries = 0;	*/
}

void GameEnd()
{
	DeleteObject(g_hOffscreenBitmap);
	DeleteDC(g_hOffscreenDC);
	
	delete g_pGalaxyBitmap;
	for(int i = 0; i < 3; ++i)
	{
		delete g_pPlanetBitmap[i];
	}
	
	g_pGame -> CleanupSprites();
//	for(int i = 0; i < 9; i++)
//	{
//		delete g_pTiles[i];
//	}
	delete g_pGame;
}

void GameActivate(HWND hWindow)
{
	g_pGame -> PlayMIDISong("", FALSE);
//	HDC hDC;
//	RECT rect;

//	GetClientRect(hWindow, &rect);
//	hDC = GetDC(hWindow);
	
//	DrawText(hDC, "Start", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
//	ReleaseDC(hWindow, hDC);
}

void GameDeactivate(HWND hWindow)
{
	g_pGame -> PauseMIDISong();
//	HDC hDC;
//	RECT rect;

//	GetClientRect(hWindow, &rect);
//	hDC = GetDC(hWindow);

//	DrawText(hDC, "Pause", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	
//	ReleaseDC(hWindow, hDC);
}

void GamePaint(HDC hDC)
{
	g_pGalaxyBitmap -> Draw(hDC, 0, 0);
	
	g_pGame -> DrawSprites(hDC);
/*	int iTileWidth = g_pTiles[0] -> GetWidth();
	int iTileHeight = g_pTiles[0] -> GetHeight();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(g_bTileStates[i][j] || ((g_ptTile1.x == i) && (g_ptTile1.y == j)) || ((g_ptTile2.x == i) && (g_ptTile2.y == j)))
			{
				g_pTiles[g_iTiles[i][j]] -> Draw(hDC, i * iTileWidth, j * iTileHeight);
			}
			else
			{
				g_pTiles[0] -> Draw(hDC, i * iTileWidth, j * iTileHeight);
			}
		}
	}	*/
}

void GameCycle()
{
	g_pGame -> UpdateSprites();

	HWND hWindow = g_pGame -> GetWindow();
	HDC hDC = GetDC(hWindow);

	GamePaint(g_hOffscreenDC);

	BitBlt(hDC, 0, 0, g_pGame -> GetWidth(), g_pGame -> GetHeight(), g_hOffscreenDC, 0, 0, SRCCOPY);

	ReleaseDC(hWindow, hDC);
}

BOOL SpriteCollision(Sprite * pSpriteHitter, Sprite * pSpriteHittee)
{
	POINT ptSwapVelocity = pSpriteHitter -> GetVelocity();
	pSpriteHitter -> SetVelocity(pSpriteHittee -> GetVelocity());
	pSpriteHittee -> SetVelocity(ptSwapVelocity);
	return TRUE;
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{	
	if(bLeft && (g_pDragSprite == NULL))
	{
		if((g_pDragSprite = g_pGame -> IsPointInSprite(x, y)) != NULL)
		{
			PlaySound(MAKEINTRESOURCE(ID_WAVE02), NULL, SND_ASYNC | SND_RESOURCE);
			SetCapture(g_pGame -> GetWindow());
			MouseMove(x, y);
		}
	}
/*	int iTileX = x / g_pTiles[0] -> GetWidth();
	int iTileY = y / g_pTiles[0] -> GetHeight();

	if(!g_bTileStates[iTileX][iTileY])
	{
		if(g_ptTile1.x == -1)
		{
			g_ptTile1.x = iTileX;
			g_ptTile1.y = iTileY;
		}
		else if((g_ptTile1.x != iTileX) || (g_ptTile1.y != iTileY))
		{
			if(g_ptTile2.x == -1)
			{
				g_iTries++;
				g_ptTile2.x = iTileX;
				g_ptTile2.y = iTileY;

				if(g_iTiles[g_ptTile1.x][g_ptTile1.y] == g_iTiles[g_ptTile2.x][g_ptTile2.y])
				{
					g_bTileStates[g_ptTile1.x][g_ptTile1.y] = TRUE;
					g_bTileStates[g_ptTile2.x][g_ptTile2.y] = TRUE;

					g_ptTile1.x = g_ptTile1.y = g_ptTile2.x = g_ptTile2.y = -1;
					g_iMatches++;

					if(g_iMatches == 8)
					{
						TCHAR szText[25];
						wsprintf(szText, "You won in %d tries", g_iTries);
						if(MessageBox(g_pGame -> GetWindow(), szText, "YOU WIN!", MB_OK) == IDOK)
						{
							PostMessage(g_pGame -> GetWindow(), WM_DESTROY, 0, 0);
						}
					}
				}		
			}
			else
			{
				g_ptTile1.x = g_ptTile1.y = g_ptTile2.x = g_ptTile2.y = -1;
			}
		}
	InvalidateRect(g_pGame -> GetWindow(), NULL, FALSE);
	}	*/
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
	ReleaseCapture();
	g_pDragSprite = NULL;
}

void MouseMove(int x, int y)
{
	if(g_pDragSprite != NULL)
	{
		g_pDragSprite -> SetPosition(x - (g_pDragSprite -> GetWidth() / 2), y - (g_pDragSprite -> GetHeight() / 2));
		InvalidateRect(g_pGame -> GetWindow(), NULL, FALSE);
	}
}