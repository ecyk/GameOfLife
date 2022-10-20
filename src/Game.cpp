#include "Game.hpp"

#include <iostream>

using namespace std;

Game::Game()
    : m_Window(sf::VideoMode(800, 600), "Game of Life"),
    m_CellSelector(sf::Vector2f(50.0f, 50.0f)), // dhange magic
    m_SelectedCell(0, 0),
    m_MouseLeftHoldPosition(0, 0),
    m_MouseLeftHold(false),
    m_View(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(static_cast<float>(m_Window.getSize().x), static_cast<float>(m_Window.getSize().y))),
    m_ZoomFactor(1.0f),
    m_World(),
    m_UpdateWorld(false),
    m_Generation(0),
    m_UpdateTime()
{
    m_Window.setFramerateLimit(60);

    m_CellSelector.setFillColor(sf::Color(19, 19, 19, 255)); // sf::Color::Transparent
    m_CellSelector.setOutlineColor(sf::Color::Green);
    m_CellSelector.setOutlineThickness(3.0f);
}

Game::~Game() {

}

void Game::Run() {
    sf::Clock clock;
    while (m_Window.isOpen()) {
        sf::Time ElapsedTime = clock.restart();
        ProcessEvents();
        Update(ElapsedTime);
        Render();
    }
}

void Game::ProcessEvents() {
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed: m_Window.close(); break;
        case sf::Event::Resized: m_View.setSize(sf::Vector2f(static_cast<float>(event.size.width), static_cast<float>(event.size.height))); m_ZoomFactor = 1.0f; break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                m_MouseLeftHoldPosition = sf::Mouse::getPosition(m_Window);
                m_MouseLeftHold = true;

                m_World.AddCell(m_SelectedCell.x, m_SelectedCell.y);
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                m_MouseLeftHold = false;
            }
            break;
        case sf::Event::MouseMoved:
        {
            if (m_MouseLeftHold) {
                const sf::Vector2i MousePosition(event.mouseMove.x, event.mouseMove.y);
                const sf::Vector2i MousePositionDelta = m_MouseLeftHoldPosition - MousePosition;

                m_View.move(sf::Vector2f(static_cast<float>(MousePositionDelta.x * m_ZoomFactor), static_cast<float>(MousePositionDelta.y * m_ZoomFactor)));

                m_MouseLeftHoldPosition = MousePosition;
            }

            sf::Vector2f MousePostionWorld = m_Window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));

            /*
                GridCellSize always positive float

                when mouse pointer points value between x < -GridCellSize or y < -GridCellSize and GridCellSize = 50.0f
                then x / GridCellSize equals something like -0.654 casting this value to int drops floating part and sign and value becomes 0.
                when 0 <= x < GridCellSize then (x / GridCellSize) is also 0 so negative range collides with positive, to solve this problem we subtract
                GridCellSize from MousePositionWorld with this way MousePositionWorld is always greater than -50, so negative offsets start from -1.
            */

            const float GridCellSize = m_World.GetGrid().GetCellSize();

            if (MousePostionWorld.x < 0) MousePostionWorld.x -= GridCellSize;
            if (MousePostionWorld.y < 0) MousePostionWorld.y -= GridCellSize;

            m_SelectedCell.x = static_cast<int>(MousePostionWorld.x / GridCellSize);
            m_SelectedCell.y = static_cast<int>(MousePostionWorld.y / GridCellSize);

            m_CellSelector.setPosition(sf::Vector2f(m_SelectedCell.x * GridCellSize, m_SelectedCell.y * GridCellSize));
            break;
        }
        case sf::Event::MouseWheelScrolled:
            if (event.mouseWheelScroll.delta > 0) {
                m_View.zoom(0.9f);
                m_ZoomFactor *= 0.9f;
            }
            else {
                m_View.zoom(1.1f);
                m_ZoomFactor *= 1.1f;
            }
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space) {
                m_UpdateWorld = !m_UpdateWorld;
            }
            if (event.key.code == sf::Keyboard::Q) {
                m_View.setSize(m_View.getSize() * (1 / m_ZoomFactor));
                m_ZoomFactor = 1.0f;
            }
            break;
        default: break;
        }
    }
}

void Game::Update(sf::Time &ElapsedTime) {
    m_World.UpdateGrid(m_View);

    m_UpdateTime += ElapsedTime;

    if (m_UpdateWorld) {
        if (m_UpdateTime >= sf::seconds(1.0f)) {
            m_World.UpdateCells();

            m_Generation++;
            m_UpdateTime = sf::Time::Zero;
        }
    }
}

void Game::Render() {
    m_Window.clear();
    m_Window.setView(m_View);

    m_Window.draw(m_World);
    m_Window.draw(m_CellSelector);

    m_Window.display();
}
