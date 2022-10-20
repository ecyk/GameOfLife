#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

using VertexOffset_type = std::vector<sf::Vertex>::size_type;

class Cell
{
public:
	VertexOffset_type m_VertexOffset;

	enum State : bool {
		Dead = false, Live = true
	};

	State m_State;
	State m_NextState;

	Cell(VertexOffset_type VertexOffset, Cell::State State, Cell::State NextState)
		: m_VertexOffset(VertexOffset), m_State(State), m_NextState(NextState) { }

	~Cell() { }

	static std::pair<int, int> GetNeighbourCoordinatesByOffset(int cell_x, int cell_y, int offset);
	void Die(std::vector<sf::Vertex> &VertexBuffer);
	void Survive(std::vector<sf::Vertex> &VertexBuffer);

	State GetCurrentState() { return m_State; };

	void UpdateState();

public:


	
};

#endif // !CELL_HPP


/*
x-1, y-1
x, y-1
x+1, y-1
x+1, y
x+1, y+1
x, y+1
x-1, y+1
x-1, y
*/


/*
-------------
| 0 | 1 | 2 |
-------------
| 7 | C | 3 |
-------------
| 6 | 5 | 4 |
-------------
*/
// assert offset