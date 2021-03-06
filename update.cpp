#include "base.hpp"
#include "update.hpp"

void update(void)
{
	deltaTime = cl.restart().asSeconds() * 60;
	Event evt;
	while(window.pollEvent(evt))
	{
		//input
		if(evt.type == Event::Closed)
			window.close();
		if(evt.type == Event::KeyPressed)
		{
			if(evt.key.code == Keyboard::Escape)
				window.close();

			//terrain custom
			custom(evt);

			//screenshot
			if(evt.key.code == Keyboard::P)
			{
				std::cout << "screenshot: ";
				std::cin >> ss_fileName;
				window.capture().saveToFile("screenshot/" + ss_fileName + ".png");
			}

			//vsync
			if(evt.key.code == Keyboard::O)
			{
				window.setVerticalSyncEnabled(true);
				std::cout << "vsync: on" << std::endl;
			}
			else if(evt.key.code == Keyboard::I)
			{
				window.setVerticalSyncEnabled(false);
				std::cout << "vsync: off" << std::endl;
			}
		}
	}
	bgPosX += 0.4 * deltaTime;
	cloudsSpr.setTextureRect(IntRect(bgPosX, 0, RESX, 360));
	waterPosX -= 0.25 * deltaTime;
	waterRec.setTextureRect(IntRect(waterPosX, 0, RESX, WATERSIZE));
	for(int a=0; a<LIMIT; a++)
	{
		t_Rec[a].rec.setTexture(&tileTex);
		if(t_Rec[a].rec.getPosition().y < RESY - WATERSIZE - RECSIZE)
			t_Rec[a].rec.setTextureRect(IntRect(16, 0, 16, 16));
		else
			t_Rec[a].rec.setTextureRect(IntRect(32, 0, 16, 16));

		t_Rec[a].recB.setTexture(&tileTex);
		t_Rec[a].recB.setTextureRect(IntRect(0, 0, RECSIZE, t_Rec[a].recB.getSize().y));
		t_Rec[a].treeWRec.setTexture(&tileTex);
		t_Rec[a].treeWRec.setTextureRect(IntRect(48, 0, RECSIZE, t_Rec[a].treeWRec.getSize().y));
		t_Rec[a].treeRec.setTexture(&treeTex);
	}
}
