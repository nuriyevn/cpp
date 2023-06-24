#include "Rectangle.h"

Rectangle::Rectangle()
{
}

Rectangle::Rectangle(Point bl, Point tr)
{
	bottom_left = bl;
	top_right = tr;
}

void Rectangle::move(int dx, int dy)
{
	bottom_left.move(dx, dy);
	top_right.move(dx, dy);
}

Point Rectangle::get_bottom_left() const
{
	return bottom_left;
}

Point Rectangle::get_top_right() const
{	
	return top_right;
}

int Rectangle::width() const
{
	return top_right.get_x() - bottom_left.get_x();
}

int Rectangle::height() const
{
	return top_right.get_y() - bottom_left.get_y();
}

int Rectangle::area() const
{
	return abs(width() * height());
}



