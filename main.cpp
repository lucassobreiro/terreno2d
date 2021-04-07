//-- Gerador de Terreno 2D --
//By lucassobreiro
//Apr 2021

#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
using namespace sf;

#define RESX 1280
#define RESY 720

#define RECSIZE 16
#define LIMIT 80
#define WATERSIZE 256
#define SUNSIZE 64

RectangleShape rec[LIMIT];
RectangleShape recB[LIMIT];
RectangleShape treeWRec[LIMIT];
RectangleShape treeRec[LIMIT];

void newTerrain(){
	int height;
	int posX = 0;
	int posY = rand()%300 + 200;
	int treeDensity;
	int treeWSize;

	std::cout << "\nGerando um novo terreno...\n";
	for(int a=0; a<LIMIT; a++){
		treeWRec[a].setPosition(Vector2f(-256.0f, -256.0f));
		treeRec[a].setPosition(Vector2f(-256.0f, -256.0f));
		rec[a].setPosition(Vector2f(posX, posY));
		recB[a].setPosition(Vector2f(posX, posY + RECSIZE));
		rec[a].setSize(Vector2f(RECSIZE, RECSIZE));
		recB[a].setSize(Vector2f(RECSIZE, RESY - rec[a].getPosition().y));
		posX += RECSIZE;
		//Tree
		treeDensity = rand()%4;
		if(treeDensity == 0 && rec[a].getPosition().y < RESY - WATERSIZE - RECSIZE){
			treeWSize = rand()%4+2;
			treeWRec[a].setSize(Vector2f(RECSIZE, RECSIZE * treeWSize));
			treeWRec[a].setPosition(Vector2f(rec[a].getPosition().x, rec[a].getPosition().y - RECSIZE * treeWSize));
			treeRec[a].setPosition(Vector2f(treeWRec[a].getPosition().x-16, treeWRec[a].getPosition().y-48));
			treeRec[a].setSize(Vector2f(RECSIZE*3, RECSIZE*3));
		}
		//Height
		height = rand()%4;
		std::cout << height << " ";
		if(height == 0){
			posY -= RECSIZE;
		}
		else if(height == 3){
			posY += RECSIZE;
		}
	}
}

int main(){
	float bgPosX = 0;
	float waterPosX = 0;
	Clock clock;
	float deltaTime;

	srand(time(NULL));
	std::cout << "-- Gerador de Terreno 2D --\nBy lucassobreiro\nApr 2021\n";
	RenderWindow window(VideoMode(RESX, RESY), "Gerador de terreno 2D", Style::Close);
	window.setKeyRepeatEnabled(false);

	//----------------------------
	//Textures
	//----------------------------
	Texture bgTex;
	if(!bgTex.loadFromFile("images/background.png"))return -1;
	Sprite bgSpr;
	bgSpr.setTexture(bgTex);

	Texture cloudsTex;
	cloudsTex.setRepeated(true);
	if(!cloudsTex.loadFromFile("images/clouds.png"))return -1;
	Sprite cloudsSpr;
	cloudsSpr.setColor(Color(255, 255, 255, 100));
	cloudsSpr.setTexture(cloudsTex);

	Texture tileTex;
	tileTex.setRepeated(true);
	if(!tileTex.loadFromFile("images/tile.png"))return -1;

	Texture treeTex;
	if(!treeTex.loadFromFile("images/tree.png"))return -1;

	Texture waterTex;
	waterTex.setRepeated(true);
	if(!waterTex.loadFromFile("images/water.png"))return -1;

	//Water
	RectangleShape waterRec(Vector2f(RESX, WATERSIZE));
	waterRec.setPosition(0.0f, RESY - WATERSIZE);
	waterRec.setTexture(&waterTex);
	waterRec.setTextureRect(IntRect(0, 0, waterRec.getSize().x, waterRec.getSize().y));

	//Sun
	RectangleShape sunRec(Vector2f(SUNSIZE, SUNSIZE));
	sunRec.setPosition(Vector2f(256, 64));
	sunRec.setFillColor(Color::Yellow);

	newTerrain();
	std::cout << "\n\nAperte SPACE para gerar um novo terreno\nAperte ESC para sair do programa\n";
	//----------------------------
	//Update
	//----------------------------
	while(window.isOpen()){
		deltaTime = clock.restart().asSeconds() * 60;
		Event evt;
		while(window.pollEvent(evt)){
			if(evt.type == Event::Closed){
				window.close();
			}
			if(evt.type == Event::KeyPressed){
				if(evt.key.code == Keyboard::Escape){
					window.close();
				}
				if(evt.key.code == Keyboard::Space){
					newTerrain();
				}
			}
		}
		bgPosX += 0.4 * deltaTime;
		cloudsSpr.setTextureRect(IntRect(bgPosX, 0, RESX, 360));
		waterPosX -= 0.25 * deltaTime;
		waterRec.setTextureRect(IntRect(waterPosX, 0, RESX, WATERSIZE));
		for(int a=0; a<LIMIT; a++){
			rec[a].setTexture(&tileTex);
			if(rec[a].getPosition().y < RESY - WATERSIZE - RECSIZE){
				rec[a].setTextureRect(IntRect(16, 0, 16, 16));
			}
			else{
				rec[a].setTextureRect(IntRect(32, 0, 16, 16));
			}
			recB[a].setTexture(&tileTex);
			recB[a].setTextureRect(IntRect(0, 0, RECSIZE, recB[a].getSize().y));
			treeWRec[a].setTexture(&tileTex);
			treeWRec[a].setTextureRect(IntRect(48, 0, RECSIZE, treeWRec[a].getSize().y));
			treeRec[a].setTexture(&treeTex);
		}
		//----------------------------
		//Draw
		//----------------------------
		window.draw(bgSpr);
		window.draw(sunRec);
		window.draw(cloudsSpr);
		window.draw(waterRec);
		for(int a=0; a<LIMIT; a++){
			window.draw(rec[a]);
			window.draw(recB[a]);
			window.draw(treeRec[a]);
			window.draw(treeWRec[a]);
		}
		window.display();
	}
	return 0;
}