#pragma once

#include "resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include <windows.h>
#include <cstdlib>

HINSTANCE g_hInstance;
GameEngine * g_pGame;
HDC g_hOffscreenDC;
HBITMAP g_hOffscreenBitmap;
//Bitmap * g_pTiles[9];
//BOOL g_bTileStates[4][4];
//int g_iTiles[4][4], g_iMatches, g_iTries;
//POINT g_ptTile1, g_ptTile2;

Bitmap * g_pGalaxyBitmap;
Bitmap * g_pPlanetBitmap[3];
Sprite * g_pDragSprite;