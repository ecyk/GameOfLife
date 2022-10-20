#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>

class Grid : public sf::Drawable {
 public:
  Grid(float CellSize = 50.0f);
  ~Grid();

  void Update(sf::View &View);

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
      target.draw(m_Grid, states);
  }

  const float GetCellSize() const { return m_CellSize; };

 private:
     sf::VertexArray m_Grid;

     const float m_CellSize;
};

#endif  // !GRID_HPP
