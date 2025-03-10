﻿#pragma once
#ifdef WITH_PNG_OUTPUT


#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <stack>



#include "shapes/line.h"
#include "shapes/circle.h"
#include "shapes/arc.h"
#include "shapes/bezier.h"
#include "shapes/tile.h"
#include "shapes/ribbon.h"
#include "shapes/rectangle.h"
#include "shapes/line_text.h"
#include "shapes/annulus.h"
#include "shapes/region.h"
#include "shapes/arc_text.h"

#include "freetype_wrapper.h"



namespace spiritsaway::shape_drawer
{
	using std::vector;
	using std::string;
	//这里png的坐标系同svg的坐标系 左上方为0，0 向右是x正向，向下时y正向
	class PngImage
	{
	public:
		int height;
		int width;
		const int radius;
		Color background_color;
		int _compression_level;
		vector<Color> _buffer;//这个是真正的存储区域 存储了所有的color信息
		vector<Color*> _image;//这个是png的行指针，只能存行，因为libpng规定了这个

		vector<uint8_t> flood_buffer;
		vector<uint8_t*> flood_map;//这个按照png里的惯例 ，也弄成行指针吧

		freetype_wrapper ft_wrapper;
		string file_name;
		int bit_depth = 8;
		const string author = "Author:spiritsaway";
		const string description = "Mail:spiritsaway@outlook.com";
		const string software = "shape_drawer implemented in c++";
		const string title = "shape_drawer.png";
		std::unordered_map<int, vector<Point>> circle_cache;

		PngImage(const std::unordered_map<std::string, std::pair<std::string, std::string>>& in_font_info,string in_file_name, int in_radius, Color back_color, int compress=8);
		const vector<unsigned char>& get_font_mem(const std::string& font_name);
		void plot(Colorbasic_point input, float opacity = 1.0);
		void plot(Point pos, Color color,float opacity = 1.0);
		void plot(int x, int y, Color color, float opacity=1.0);
		Color read(Point pos);
		void draw_path(const vector<Point>& path, Color color, int stroke = 1, float opacity = 1.0);
		~PngImage();
		
		bool on_boundary(Point current) const; // 判断一个点是否在边界上
		//判断一个点是否可以将他的相邻点加入洪范列表
		//这里为了保险起见才加了这个判断函数
		//只要有一个处于边界就停止，避免可能的边界没有完全闭合的情况
		bool can_flood(Point current);
		// flood_flag 2代表边界，1代表已经着色，0 代表还未访问
		std::uint8_t get_flood_flag(Point current) const;
		void set_flood_flag(Point current, std::uint8_t flag);
		//要求interior一定在boundary里面
		void flood(const vector<vector<Point>>& boundary, vector<Point> interiors, Color fill_color, float opacity =1.0);
			
		//这里要处理一下utf8
		void draw_text(const Line& base_line, std::vector<std::uint32_t> text, const std::string& font_name, int font_size, Color color, float alpha);


		void draw_grey_map(const std::vector<std::pair<std::pair<std::int32_t, std::int32_t>, std::uint8_t>>& grey_bitmap, Color color, float alpha);
		// 获得某一点相对于某条线的对称点

		vector<Point> path(const Line& line) const;
		PngImage& operator<<( const Line& line);

		PngImage& operator<<(const LineText& line_text);
		vector<Point> path(const Arc& arc) const;
		PngImage& operator<<(const Arc& arc);

		vector<Point> path(const Bezier& bezier) const;
		PngImage& operator<<(const Bezier& bezier);
		PngImage& operator<<(const Rectangle& rect);
		vector<Point> path(const Circle& circle) const;
		PngImage& operator<<(const Circle& circle);
		PngImage& operator<<(const Tile& tile);
		PngImage& operator<<(const Ribbon& ribbon);
		PngImage& operator<<(const Annulus& annulus);
		PngImage& operator<<(const Region& region);
		PngImage& operator<<(const ArcText& arc_text);

		template <typename T>
		PngImage& add_shape(const T& in_shape)
		{
			in_shape.draw_png(*this);
			return *this;
		}
	};
}
#endif