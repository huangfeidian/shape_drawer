#pragma once
#include <cmath>
#include "basics/point.h"
#include "basics/color.h"
namespace spiritsaway::shape_drawer
{
	struct Rectangle
	{
		Point left;
		Point right;
		std::uint16_t height;
		Color color;
		float opacity;
		bool fill;
		std::uint16_t stroke_width = 1;
		Color stroke_color;
		Rectangle()
			:left(), right(), color(), opacity(1), stroke_width(1)
		{
		
		}
		Rectangle(Point in_left, Point in_right, Color in_color, std::uint16_t in_height, bool in_fill = false, float in_opacity =1.0)
			: left(in_left)
			, right(in_right)
			, color(in_color)
			, height(in_height)
			, fill(in_fill)
			, opacity(in_opacity)
			, stroke_color(in_color)
			, stroke_width(1)
		{
			
		}
		Rectangle(Point in_min_xy, Point aabb_xy_len, Color in_color, bool in_fill = false, float in_opacity = 1.0)
			: left(in_min_xy)
			, right(in_min_xy + Point(aabb_xy_len.x, 0))
			, height(aabb_xy_len.y)
			, color(in_color)
			, fill(in_fill)
			, opacity(in_opacity)
			, stroke_color(in_color)
			, stroke_width(1)
		{

		}
	};
}
