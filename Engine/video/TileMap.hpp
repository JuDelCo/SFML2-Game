#pragma once
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP


#include <SFML\Graphics.hpp>


class TileMap : public sf::Drawable
{
	public:
		TileMap(const std::string tileSetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
		~TileMap();
        void draw(sf::RenderTarget& rt, sf::RenderStates states) const;

	private:

        sf::VertexArray m_vertices;
        sf::Texture m_texture;
};


#endif // TILE_MAP_HPP
