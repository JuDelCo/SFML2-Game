// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef SPRITE_BATCH_HPP
#define SPRITE_BATCH_HPP

#include "Sprite.hpp"

typedef std::shared_ptr<sf::Vertex> VertexPtr;

class SpriteBatch : public sf::Drawable, public sf::Transformable
{
	public:
		SpriteBatch();
		~SpriteBatch() {}

		Sprite& operator[] (unsigned int index);
		Sprite& newSprite(Sprite&& sprite);
		bool deleteSprite(Sprite& sprite);
		void bindTexture(TexturePtr texture);
		void update();

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::vector<Sprite> m_sprites;
		std::vector<sf::Vertex> m_vertices;
		TexturePtr m_texture;
};

#endif // SPRITE_BATCH_HPP
