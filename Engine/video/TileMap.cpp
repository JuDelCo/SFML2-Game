#include "TileMap.hpp"


// Actualizar solo los quads modificados (no recalcular todos)
// Dibujar en pantalla solo lo visible (VertexArray.size == Screen.size)
//      (+ ResizeFnc para el onResize de la pantalla)
//      (+ MoveFnc para mover la cámara) "m_offset"


TileMap::TileMap(const std::string tileSetPath, sf::Vector2u tileSize, int* tiles, unsigned int width, unsigned int height)
{
    m_texture.loadFromFile(tileSetPath);
    m_tiles = tiles;
    m_width = width;
    m_height = height;
    m_tileSize = tileSize;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_width * m_height * 4);

    update();
}


TileMap::~TileMap()
{
    delete m_tiles;
}


void TileMap::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderState) const
{
    renderState.texture = &m_texture;
    renderTarget.draw(m_vertices, renderState);
}


void TileMap::update()
{
    for (unsigned int counterX = 0; counterX < m_width; ++counterX)
    {
        for (unsigned int counterY = 0; counterY < m_height; ++counterY)
        {
            sf::Vertex* quad = &m_vertices[(counterX + counterY * m_width) * 4];

            quad[0].position = sf::Vector2f(counterX * m_tileSize.x, counterY * m_tileSize.y);
            quad[1].position = sf::Vector2f((counterX + 1) * m_tileSize.x, counterY * m_tileSize.y);
            quad[2].position = sf::Vector2f((counterX + 1) * m_tileSize.x, (counterY + 1) * m_tileSize.y);
            quad[3].position = sf::Vector2f(counterX * m_tileSize.x, (counterY + 1) * m_tileSize.y);

            int tileNumber = m_tiles[counterX + counterY * m_width];
            int texturePosX = tileNumber % (m_texture.getSize().x / m_tileSize.x);
            int texturePosY = tileNumber / (m_texture.getSize().x / m_tileSize.x);

            quad[0].texCoords = sf::Vector2f(texturePosX * m_tileSize.x, texturePosY * m_tileSize.y);
            quad[1].texCoords = sf::Vector2f((texturePosX + 1) * m_tileSize.x, texturePosY * m_tileSize.y);
            quad[2].texCoords = sf::Vector2f((texturePosX + 1) * m_tileSize.x, (texturePosY + 1) * m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(texturePosX * m_tileSize.x, (texturePosY + 1) * m_tileSize.y);
        }
    }
}


int TileMap::getTile(sf::Vector2u position)
{
    return m_tiles[position.x + position.y * m_width];
}


void TileMap::setTile(sf::Vector2u position, int tileValue)
{
    m_tiles[position.x + position.y * m_width] = tileValue;
}


sf::Vector2u TileMap::getTilePos(sf::Vector2u position)
{
    return sf::Vector2u(position.x / m_tileSize.x, position.y / m_tileSize.y);
}
