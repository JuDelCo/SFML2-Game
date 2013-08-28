#include "TileMap.hpp"


TileMap::TileMap(const std::string tileSetPath, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    m_texture.loadFromFile(tileSetPath);

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    for (unsigned int counterX = 0; counterX < width; ++counterX)
    {
        for (unsigned int counterY = 0; counterY < height; ++counterY)
        {
            sf::Vertex* quad = &m_vertices[(counterX + counterY * width) * 4];

            // Position
            quad[0].position = sf::Vector2f(counterX * tileSize.x, counterY * tileSize.y);
            quad[1].position = sf::Vector2f((counterX + 1) * tileSize.x, counterY * tileSize.y);
            quad[2].position = sf::Vector2f((counterX + 1) * tileSize.x, (counterY + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(counterX * tileSize.x, (counterY + 1) * tileSize.y);

            int tileNumber = tiles[counterX + counterY * width];
            int texturePosX = tileNumber % (m_texture.getSize().x / tileSize.x);
            int texturePosY = tileNumber / (m_texture.getSize().x / tileSize.x);

            // Texture coordinates
            quad[0].texCoords = sf::Vector2f(texturePosX * tileSize.x, texturePosY * tileSize.y);
            quad[1].texCoords = sf::Vector2f((texturePosX + 1) * tileSize.x, texturePosY * tileSize.y);
            quad[2].texCoords = sf::Vector2f((texturePosX + 1) * tileSize.x, (texturePosY + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(texturePosX * tileSize.x, (texturePosY + 1) * tileSize.y);
        }
    }
}


TileMap::~TileMap()
{

}


void TileMap::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderState) const
{
    renderState.texture = &m_texture;
    renderTarget.draw(m_vertices, renderState);
}

