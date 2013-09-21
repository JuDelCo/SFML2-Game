#include "Sprite.hpp"


Sprite::Sprite()
{
	m_vertices.resize(4);
	m_flipHorizontal = false;
	m_flipVertical = false;
	m_updated = false;
}


Sprite::Sprite(TexturePtr texture) : Sprite()
{
	bindTexture(texture);
}


Sprite::Sprite(TexturePtr texture, sf::IntRect textureRect) : Sprite(texture)
{
	setTextureRect(textureRect);
}


bool Sprite::isUpdated()
{
	return m_updated;
}


const sf::Vertex* Sprite::getUpdate()
{
	m_updated = false;

	return &m_vertices[0];
}


void Sprite::setSize(sf::Vector2i spriteSize)
{
	m_size = spriteSize;

	m_vertices[0].position = sf::Vector2f(0, 0);
	m_vertices[1].position = sf::Vector2f(m_size.x, 0);
	m_vertices[2].position = sf::Vector2f(m_size.x, m_size.y);
	m_vertices[3].position = sf::Vector2f(0, m_size.y);

	setOrigin(sf::Vector2f(m_size.x / 2.0f, m_size.y / 2.0f));
}


sf::Vector2i Sprite::getSize()
{
	return m_size;
}


void Sprite::setTextureRect(sf::IntRect textureRect)
{
	m_textureRect = textureRect;

	m_vertices[0].texCoords = sf::Vector2f(
		(!m_flipHorizontal ? textureRect.left : textureRect.left + textureRect.width),
		(!m_flipVertical ? textureRect.top : textureRect.top + textureRect.height));
	m_vertices[1].texCoords = sf::Vector2f(
		(!m_flipHorizontal ? textureRect.left + textureRect.width : textureRect.left),
		(!m_flipVertical ? textureRect.top : textureRect.top + textureRect.height));
	m_vertices[2].texCoords = sf::Vector2f(
		(!m_flipHorizontal ? textureRect.left + textureRect.width : textureRect.left),
		(!m_flipVertical ? textureRect.top + textureRect.height : textureRect.top));
	m_vertices[3].texCoords = sf::Vector2f(
		(!m_flipHorizontal ? textureRect.left : textureRect.left + textureRect.width),
		(!m_flipVertical ? textureRect.top + textureRect.height : textureRect.top));

	m_updated = true;
}


void Sprite::setFrame(unsigned int frameNumber)
{
	setTextureRect(sf::IntRect(m_size.x * frameNumber, 0, m_size.x, m_size.y));
}


void Sprite::flipHorizontal(bool flipHorizontal)
{
	m_flipHorizontal = flipHorizontal;

	setTextureRect(m_textureRect);
}


void Sprite::flipVertical(bool flipVertical)
{
	m_flipVertical = flipVertical;

	setTextureRect(m_textureRect);
}


void Sprite::setColor(const sf::Color& color)
{
	m_vertices[0].color = color;
	m_vertices[1].color = color;
	m_vertices[2].color = color;
	m_vertices[3].color = color;

	m_updated = true;
}


void Sprite::setColor(const sf::Color& color1, const sf::Color& color2, const sf::Color& color3, const sf::Color& color4)
{
	m_vertices[0].color = color1;
	m_vertices[1].color = color2;
	m_vertices[2].color = color3;
	m_vertices[3].color = color4;

	m_updated = true;
}


void Sprite::bindTexture(TexturePtr texture)
{
	m_texture = texture;
}


void Sprite::setPosition(float x, float y)
{
	Transformable::setPosition(x, y);

	updateVertex();
}


void Sprite::setPosition(const sf::Vector2f &position)
{
	Transformable::setPosition(position);

	updateVertex();
}


void Sprite::setRotation(float angle)
{
	Transformable::setRotation(angle);

	updateVertex();
}


void Sprite::setScale(float factorX, float factorY)
{
	Transformable::setScale(factorX, factorY);

	updateVertex();
}


void Sprite::setScale(const sf::Vector2f &factors)
{
	Transformable::setScale(factors);

	updateVertex();
}


void Sprite::move(float offsetX, float offsetY)
{
	Transformable::move(offsetX, offsetY);

	updateVertex();
}


void Sprite::move(const sf::Vector2f &offset)
{
	Transformable::move(offset);

	updateVertex();
}


void Sprite::rotate(float angle)
{
	Transformable::rotate(angle);

	updateVertex();
}


void Sprite::scale(float factorX, float factorY)
{
	Transformable::scale(factorX, factorY);

	updateVertex();
}


void Sprite::scale(const sf::Vector2f &factor)
{
	Transformable::scale(factor);

	updateVertex();
}


void Sprite::updateVertex()
{
	sf::Transform transform = getTransform();

	m_vertices[0].position = transform.transformPoint(0, 0);
	m_vertices[1].position = transform.transformPoint(m_size.x, 0);
	m_vertices[2].position = transform.transformPoint(m_size.x, m_size.y);
	m_vertices[3].position = transform.transformPoint(0, m_size.y);

	m_updated = true;
}


void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_texture != nullptr)
	{
		states.texture = m_texture.get();
	}

	target.draw(&m_vertices[0], 4, sf::Quads, states);
}
