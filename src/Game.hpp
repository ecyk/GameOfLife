#ifndef GAME_HPP
#define GAME_HPP

#include "World.hpp"

class Game {
public:
	Game();
	~Game();

	void Run();

private:
	void ProcessEvents();
	void Update(sf::Time &ElapsedTime);
	void Render();

private:
	sf::RenderWindow m_Window;

	sf::RectangleShape m_CellSelector;
	sf::Vector2i m_SelectedCell;

	sf::Vector2i m_MouseLeftHoldPosition;
	bool m_MouseLeftHold;

	sf::View m_View;
	float m_ZoomFactor;

	World m_World;

	bool m_UpdateWorld;
	unsigned int m_Generation;

	sf::Time m_UpdateTime;


};

#endif // !GAME_HPP
