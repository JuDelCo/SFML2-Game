// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include <SFML\Graphics.hpp>

class TileMap : public sf::Drawable
{
	public:
		TileMap(const std::string tileSetPath, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height);
		~TileMap();

		void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
		void update();
		int getTile(sf::Vector2u position);
		void setTile(sf::Vector2u position, int tileValue);
		sf::Vector2u getTilePos(sf::Vector2u position);

	private:
		sf::VertexArray m_vertices;
		sf::Texture m_texture;
		int* m_tiles;
		unsigned int m_width;
		unsigned int m_height;
		sf::Vector2u m_tileSize;
};

#endif // TILE_MAP_HPP
