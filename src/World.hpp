#ifndef WORLD_HPP
#define WORLD_HPP

#include "Grid.hpp"
#include "Cell.hpp"

class World : public sf::Drawable
{
public:
	World()
		: m_Grid(), m_VertexBuffer(36), m_NextVertexOffset(), m_CellMap(), m_NewCells() {}
	
	~World() {}

	Grid &GetGrid() { return m_Grid; };

	void UpdateGrid(sf::View &view);
	void UpdateCells();

	void CheckVertexBufferSize();
	void AddNeighbourCells(int OffsetX, int OffsetY);
	void AddCell(int OffsetX, int OffsetY);

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
		target.draw(m_Grid, states);
		target.draw(&m_VertexBuffer[0], m_VertexBuffer.size(), sf::PrimitiveType::Quads);
	}

private:
	Grid m_Grid;

	std::vector<sf::Vertex> m_VertexBuffer;
	VertexOffset_type m_NextVertexOffset;

	std::map<std::pair<int, int>, Cell> m_CellMap;
	std::vector<std::pair<int, int>> m_NewCells;

};

#endif // !WORLD_HPP
