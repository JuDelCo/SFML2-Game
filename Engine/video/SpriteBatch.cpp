// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

#include "SpriteBatch.hpp"

SpriteBatch::SpriteBatch()
{
	m_sprites.reserve(100);
	m_vertices.reserve(400);
	m_texture = nullptr;
}

Sprite& SpriteBatch::operator[] (unsigned int index)
{
	return m_sprites[index];
}

Sprite& SpriteBatch::newSprite(Sprite&& sprite)
{
	m_sprites.emplace_back(sprite);

	const sf::Vertex* spriteVertex = m_sprites.back().getUpdate();

	m_vertices.emplace_back(*(spriteVertex));
	m_vertices.emplace_back(*(spriteVertex + 1));
	m_vertices.emplace_back(*(spriteVertex + 2));
	m_vertices.emplace_back(*(spriteVertex + 3));

	if(m_sprites.size() > m_sprites.capacity())
	{
		m_sprites.reserve(m_sprites.capacity() + 100);
		m_vertices.reserve(m_vertices.capacity() + (100 * 4));
	}

	return m_sprites.back();
}

bool SpriteBatch::deleteSprite(Sprite& sprite)
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		if (&*it == &sprite)
		{
			m_sprites.erase(it);

			unsigned int vertexIndex = (&*it - &m_sprites[0]) * 4;

			m_vertices.erase(m_vertices.begin() + vertexIndex, m_vertices.begin() + vertexIndex + 3);

			return true;
		}
	}

	return false;
}

void SpriteBatch::bindTexture(TexturePtr texture)
{
	m_texture = texture;
}

void SpriteBatch::update()
{
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		if(it->isUpdated())
		{
			unsigned int vertexIndex = (&*it - &m_sprites[0]) * 4;

			const sf::Vertex* spriteVertex = it->getUpdate();

			m_vertices[vertexIndex] = *(spriteVertex);
			m_vertices[vertexIndex + 1] = *(spriteVertex + 1);
			m_vertices[vertexIndex + 2] = *(spriteVertex + 2);
			m_vertices[vertexIndex + 3] = *(spriteVertex + 3);
		}
	}
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_texture != nullptr)
	{
		states.texture = m_texture.get();
	}

	states.transform *= getTransform();

	target.draw(&m_vertices[0], m_vertices.size(), sf::Quads, states);
}
