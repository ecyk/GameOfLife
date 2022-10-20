#include "Cell.hpp"

const sf::Color CellLiveColor = sf::Color::Red;
const sf::Color CellDeadColor = sf::Color::Transparent;

std::pair<int, int> Cell::GetNeighbourCoordinatesByOffset(int cell_x, int cell_y, int offset) {
	switch (offset) {
	case 0: cell_x += -1; cell_y += -1; break;
	case 1: cell_x += 0; cell_y += -1; break;
	case 2: cell_x += 1; cell_y += -1; break;
	case 3: cell_x += 1; cell_y += 0; break;
	case 4: cell_x += 1; cell_y += 1; break;
	case 5: cell_x += 0; cell_y += 1; break;
	case 6: cell_x += -1; cell_y += 1; break;
	case 7: cell_x += -1; cell_y += 0; break;
	}

	return std::make_pair(cell_x, cell_y);
}

void Cell::Die(std::vector<sf::Vertex> &VertexBuffer) {
	VertexBuffer[m_VertexOffset + 0].color = sf::Color(CellDeadColor);
	VertexBuffer[m_VertexOffset + 1].color = sf::Color(CellDeadColor);
	VertexBuffer[m_VertexOffset + 2].color = sf::Color(CellDeadColor);
	VertexBuffer[m_VertexOffset + 3].color = sf::Color(CellDeadColor);
}

void Cell::Survive(std::vector<sf::Vertex> &VertexBuffer) {
	VertexBuffer[m_VertexOffset + 0].color = sf::Color(CellLiveColor);
	VertexBuffer[m_VertexOffset + 1].color = sf::Color(CellLiveColor);
	VertexBuffer[m_VertexOffset + 2].color = sf::Color(CellLiveColor);
	VertexBuffer[m_VertexOffset + 3].color = sf::Color(CellLiveColor);
}

void Cell::UpdateState() {
	m_State = m_NextState;
}