#include <board_generator.hpp>
#include <vector>

struct Ship {
  std::vector<Cell> shipCells;
  void GenerateShip(int size, std::vector<Cell>& cells);
  bool isPartOfAShip(int posX, int posY);
  void shoot(int posX, int posY);
};

void GenerateEnemyShips(Board& board);