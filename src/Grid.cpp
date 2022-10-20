#include "Grid.hpp"

Grid::Grid(float CellSize) : 
    m_Grid(sf::VertexArray(sf::PrimitiveType::Lines)), m_CellSize(CellSize) { }

Grid::~Grid() { }

void Grid::Update(sf::View &View) {
    m_Grid.clear();

    const sf::Vector2f &ViewCenter = View.getCenter();
    const sf::Vector2f &ViewSize = View.getSize();

    int CellCountX = static_cast<int>(ViewSize.x / 50) + 1;
    int CellCountY = static_cast<int>(ViewSize.y / 50) + 1;

    float CellPositionX = static_cast<int>((ViewCenter.x - ViewSize.x / 2) / 50) * m_CellSize;
    float CellPositionY = static_cast<int>((ViewCenter.y - ViewSize.y / 2) / 50) * m_CellSize;

    for (int i = 0; i <= CellCountX; ++i) {
        m_Grid.append(sf::Vertex(sf::Vector2f(CellPositionX + m_CellSize * i, ViewCenter.y - ViewSize.y / 2), sf::Color(sf::Color::White)));
        m_Grid.append(sf::Vertex(sf::Vector2f(CellPositionX + m_CellSize * i, ViewCenter.y + ViewSize.y / 2 ), sf::Color(sf::Color::White)));
    }

    for (int i = 0; i <= CellCountY; ++i) {
        m_Grid.append(sf::Vertex(sf::Vector2f(ViewCenter.x - ViewSize.x / 2, CellPositionY + m_CellSize * i), sf::Color(sf::Color::White)));
        m_Grid.append(sf::Vertex(sf::Vector2f(ViewCenter.x + ViewSize.x / 2, CellPositionY + m_CellSize * i), sf::Color(sf::Color::White)));
    }
}
