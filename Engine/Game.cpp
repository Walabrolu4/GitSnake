/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rndNumber(std::random_device()()),
	snake({2,2}),
	goal(rndNumber,brd,snake)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if(!gameIsOver) //If game isnt over, play it
	{
		//Keboard Input begin
		if (wnd.kbd.KeyIsPressed(VK_UP)) 
		{
			delta_loc = { 0,-1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			delta_loc = { 0,1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			delta_loc = { -1,0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			delta_loc = { 1,0 };
		}										
		// Keyboard input end

		++snakeMoveCounter; // increment with update
		if (snakeMoveCounter >= snakeMovePeriod) // period is reached
		{
		
			snakeMoveCounter = 0;
			const Location next = snake.getNextHeadLocation(delta_loc); //Get the location of the next head
			if (!brd.isInsideBoard(next)|| snake.isInTile(next)) // if snake is deading
			{
				gameIsOver = true;
			}
			else
			{
				bool eating = next == goal.GetLocation(); // Is the next head position == the goal?
				if (eating)
				{
					snake.Grow(); //IF YES grow
				}
				snake.MoveBy(delta_loc); // Move snake
				if (eating)
				{
					goal.Respawn(rndNumber, brd, snake); // IF YES Respawn goal (done after movement)
				}
			}
		
		}
	}
	
}

void Game::ComposeFrame()
{
	brd.DrawBorder();
	goal.Draw(brd); //Draw the goal to the board
	snake.Draw(brd); // Draw snake to the board
	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(200, 200, gfx);
	}
}
