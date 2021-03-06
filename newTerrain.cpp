#include "base.hpp"
#include "terrainRec.hpp"

extern terrainRec t_Rec[LIMIT];

void newTerrain(int treeD, int treeH_min, int treeH_max, int freq)
{
	int height;
	int posX = 0;
	int posY = rand()%300 + 200;
	int treeDensity;
	int treeWSize;

	for(int a=0; a<LIMIT; a++)
	{
		t_Rec[a].treeWRec.setPosition(Vector2f(-256.0f, -256.0f));
		t_Rec[a].treeRec.setPosition(Vector2f(-256.0f, -256.0f));
		t_Rec[a].rec.setPosition(Vector2f(posX, posY));
		t_Rec[a].recB.setPosition(Vector2f(posX, posY + RECSIZE));
		t_Rec[a].rec.setSize(Vector2f(RECSIZE, RECSIZE));
		t_Rec[a].recB.setSize(Vector2f(RECSIZE, RESY - t_Rec[a].rec.getPosition().y));
		posX += RECSIZE;

		//tree
		treeDensity = rand()%treeD;
		if(treeDensity == 0 && t_Rec[a].rec.getPosition().y < RESY - WATERSIZE - RECSIZE)
		{
			treeWSize = rand()%treeH_max+treeH_min;
			t_Rec[a].treeWRec.setSize(Vector2f(RECSIZE, RECSIZE * treeWSize));
			t_Rec[a].treeWRec.setPosition(Vector2f(t_Rec[a].rec.getPosition().x, t_Rec[a].rec.getPosition().y - RECSIZE * treeWSize));
			t_Rec[a].treeRec.setPosition(Vector2f(t_Rec[a].treeWRec.getPosition().x-16, t_Rec[a].treeWRec.getPosition().y-48));
			t_Rec[a].treeRec.setSize(Vector2f(RECSIZE*3, RECSIZE*3));
		}

		//height
		height = rand()%freq;
		if(height == 0) posY -= RECSIZE;
		else if(height == freq - 1) posY += RECSIZE;
	}
}
