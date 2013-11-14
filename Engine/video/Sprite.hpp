// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#pragma once
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

typedef std::shared_ptr<sf::Texture> TexturePtr;

class Sprite : public sf::Drawable, public sf::Transformable
{
	public:
		typedef std::shared_ptr<Sprite> Ptr;

		Sprite();
		Sprite(TexturePtr texture);
		Sprite(TexturePtr texture, sf::IntRect textureRect);
		~Sprite() {}

		bool isUpdated();
		const sf::Vertex* getUpdate();
		void setSize(sf::Vector2i spriteSize);
		sf::Vector2i getSize();
		void setTextureRect(sf::IntRect textureRect);
		void setFrame(unsigned int frameNumber);
		void flipHorizontal(bool flipHorizontal);
		void flipVertical(bool flipVertical);
		void setColor(const sf::Color& color);
		void setColor(const sf::Color& color1, const sf::Color& color2, const sf::Color& color3, const sf::Color& color4);
		void bindTexture(TexturePtr texture);
		void setPosition(float x, float y);
		void setPosition(const sf::Vector2f &position);
		void setRotation(float angle);
		void setScale(float factorX, float factorY);
		void setScale(const sf::Vector2f &factors);
		void move(float offsetX, float offsetY);
		void move(const sf::Vector2f &offset);
		void rotate(float angle);
		void scale(float factorX, float factorY);
		void scale(const sf::Vector2f &factor);

	private:
		void updateVertex();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		std::vector<sf::Vertex> m_vertices;
		sf::Vector2i m_size;
		sf::IntRect m_textureRect;
		TexturePtr m_texture;
		bool m_flipHorizontal;
		bool m_flipVertical;
		bool m_updated;
};

#endif // SPRITE_HPP
