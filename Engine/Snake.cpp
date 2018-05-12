#include "Snake.h"

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location & delta_loc) //Move snake by delta location
{
	for (int i = nSegments - 1; i > 0; i--) //Go from the tail backwards and move every segment to its corosponding space except the head
	{
		segments[i].Follow(segments[i - 1]); //set current segment loc to loc of segment - 1
	}
	segments[0].MoveBy(delta_loc); // add delta loc to heads location 
}

Location Snake::getNextHeadLocation(const Location & delta_loc) const //Get the next head location by adding the current loc to the delta_loc
{
	Location l(segments[0].GetLocation()); //Get head loc
	l.Add(delta_loc); // Add head loc by delta
	return l;
}

void Snake::Grow() //Grow snake by one tile
{
	if (nSegments < nSegmentsMax)
	{
		segments[nSegments].InitBody();
		++nSegments;
	}
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; ++i)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::isInTile(const Location & target) const
{
	for (int i = 0; i < nSegments -1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody()
{
	c = Snake::bodyColor;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1); // Can only move in one direction 
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
