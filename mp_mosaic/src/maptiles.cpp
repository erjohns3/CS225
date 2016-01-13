/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

mosaic_canvas map_tiles(const source_image& source,
                        const std::vector<tile_image>& tiles)
{
	/**
	* @todo Implement this function!
	*/
	mosaic_canvas canvas {source.rows(), source.columns()};

	std::vector<point<3>> tiles_colors;
	std::map<point<3>, tile_image> tiles_map;

	for(size_t i=0; i<tiles.size(); i++){
		point<3> tmp {tiles[i].average_color().red, tiles[i].average_color().green, tiles[i].average_color().blue};
		tiles_colors.push_back(tmp);
		tiles_map[tmp] = tiles[i];
	}

	kd_tree<3> tiles_tree {tiles_colors};

	for(size_t x=0; x<canvas.rows(); x++){
		for(size_t y=0; y<canvas.columns(); y++){
			point<3> tmp {source.region_color(x,y).red, source.region_color(x,y).green, source.region_color(x,y).blue};
			canvas.set_tile(x, y, tiles_map[tiles_tree.find_nearest_neighbor(tmp)]);
		}
	}
	return canvas;
}


