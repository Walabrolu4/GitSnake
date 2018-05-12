#include "Board.h"

Board::Board(Graphics & gfx): gfx(gfx)
{
	
}

void Board::DrawCell(const Location & loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.y < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimension, loc.y * dimension, dimension, dimension, c);
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::isInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width&& loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
	for (int i = 0; i < width; ++i)
	{
		Location l = { i,0};
		DrawCell(l, Colors::Blue);
	}
	for (int i = 0; i < width; ++i)
	{
		Location l = { i,19 };
		DrawCell(l, Colors::Blue);
	}
	for (int i = 0; i < height; ++i)
	{
		Location l = { 0,i};
		DrawCell(l, Colors::Blue);
	}
	for (int i = 0; i < height; ++i)
	{
		Location l = { 19,i };
		DrawCell(l, Colors::Blue);
	}
}
