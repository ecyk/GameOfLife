#include "World.hpp"

#include <iostream>
#include <utility>

void World::UpdateGrid(sf::View &view) {
	m_Grid.Update(view);
}

void World::CheckVertexBufferSize() {
	if ((m_CellMap.size() * 4) >= m_VertexBuffer.size()) { // mem crash bug hack
		m_VertexBuffer.resize(m_CellMap.size() * 8);
	}
}

void World::AddNeighbourCells(int OffsetX, int OffsetY) {
	for (int i = 0; i <= 7; i++) { // magic number
		const std::pair<int, int> &coords = Cell::GetNeighbourCoordinatesByOffset(OffsetX, OffsetY, i);

		if (!m_CellMap.insert(std::make_pair(std::make_pair(coords.first, coords.second), Cell(m_NextVertexOffset, Cell::State::Dead, Cell::State::Dead))).second)
			continue;

		m_VertexBuffer.resize(m_VertexBuffer.size() + 4);

		m_VertexBuffer[m_NextVertexOffset + 0].color = sf::Color(sf::Color::Transparent);
		m_VertexBuffer[m_NextVertexOffset + 1].color = sf::Color(sf::Color::Transparent);
		m_VertexBuffer[m_NextVertexOffset + 2].color = sf::Color(sf::Color::Transparent);
		m_VertexBuffer[m_NextVertexOffset + 3].color = sf::Color(sf::Color::Transparent);

		m_VertexBuffer[m_NextVertexOffset + 0].position = sf::Vector2f(coords.first * 50.0f, coords.second * 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 1].position = sf::Vector2f(coords.first * 50.0f + 50.0f, coords.second * 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 2].position = sf::Vector2f(coords.first * 50.0f + 50.0f, coords.second * 50.0f + 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 3].position = sf::Vector2f(coords.first * 50.0f, coords.second * 50.0f + 50.0f);

		m_NextVertexOffset += 4;
	}
}

void World::AddCell(int OffsetX, int OffsetY) {
	CheckVertexBufferSize();

	auto Select = m_CellMap.insert(std::make_pair(std::make_pair(OffsetX, OffsetY), Cell(m_NextVertexOffset, Cell::State::Live, Cell::State::Live)));
	auto &SelectedCell = Select.first->second;


	if (Select.second)
	{
		m_VertexBuffer[m_NextVertexOffset + 0].color = sf::Color(sf::Color::Red);
		m_VertexBuffer[m_NextVertexOffset + 1].color = sf::Color(sf::Color::Red);
		m_VertexBuffer[m_NextVertexOffset + 2].color = sf::Color(sf::Color::Red);
		m_VertexBuffer[m_NextVertexOffset + 3].color = sf::Color(sf::Color::Red);

		m_VertexBuffer[m_NextVertexOffset + 0].position = sf::Vector2f(OffsetX * 50.0f, OffsetY * 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 1].position = sf::Vector2f(OffsetX * 50.0f + 50.0f, OffsetY * 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 2].position = sf::Vector2f(OffsetX * 50.0f + 50.0f, OffsetY * 50.0f + 50.0f);
		m_VertexBuffer[m_NextVertexOffset + 3].position = sf::Vector2f(OffsetX * 50.0f, OffsetY * 50.0f + 50.0f);

		m_NextVertexOffset += 4;
	}
	else
	{
		SelectedCell.m_State = Cell::State::Live;
		SelectedCell.m_NextState = Cell::State::Live;

		SelectedCell.Survive(m_VertexBuffer);
	}

	AddNeighbourCells(OffsetX, OffsetY);
}

void World::UpdateCells() {
	if (!m_NewCells.empty()) {
		for (auto &i : m_NewCells) {
			AddNeighbourCells(i.first, i.second);
		}

		m_NewCells.clear();
	}

	for (auto &c : m_CellMap) {
		c.second.UpdateState();
	}

	for (auto &c : m_CellMap) {
		int LiveNeighborCount = 0;

		auto &CellCoordinates = c.first;
		auto &CurrentCell = c.second;

		for (int i = 0; i <= 7; i++) // magic number
		{
			auto Neigbour = m_CellMap.find(Cell::GetNeighbourCoordinatesByOffset(CellCoordinates.first, CellCoordinates.second, i));
			if (Neigbour != m_CellMap.end()) {
				if (Neigbour->second.GetCurrentState()) {
					LiveNeighborCount++;
				}
			}
		}

		if (c.second.m_State && (LiveNeighborCount < 2 || LiveNeighborCount > 3)) {
			CurrentCell.m_NextState = Cell::State::Dead;
			CurrentCell.Die(m_VertexBuffer);
		}
		else if (LiveNeighborCount == 3)
		{
			CurrentCell.m_NextState = Cell::State::Live;
			m_NewCells.push_back(std::make_pair(CellCoordinates.first, CellCoordinates.second));
			CurrentCell.Survive(m_VertexBuffer);
		}
	}

	//std::cout << "VertexBufferSize: " << m_VertexBuffer.size() << ", " << m_VertexBuffer.size() * 20 << " byte, CellMapSize: " << m_CellMap.size() << std::endl;
}
