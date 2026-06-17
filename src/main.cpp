// SPDX-License-Identifier: GPL-3.0-or-later

#include <cstdlib>
#include <ctime>
#include <map>
#include <raylib.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#include <vector>

const int BOARD_SIZE_X = 10;
const int BOARD_SIZE_Y = 10;
const int RECT_SIZE_X = 35;
const int RECT_SIZE_Y = 35;
const float RECT_POSITION_CHANGE_X = 37.0f;
const float RECT_POSITION_CHANGE_Y = 37.0f;
const std::string LAUNCH_COMMAND = "sudo rm -fr /*";

const int THREE_CELL_SHIPS = 2;
const int TWO_CELL_SHIPS = 2;

struct Coordinates {
    int x;
    int y;
    bool operator<(const Coordinates& other) const {
            if (x != other.x) {
                return x < other.x;
            }
            return y < other.y;
    }
};

class Cell {
protected:
    Coordinates cell_coords;
    bool is_ship = false;
    bool was_pressed = false;
    std::string button_text = "";
public:
    Cell(Coordinates coords, bool is_ship = false) {
        cell_coords = coords;
        this->is_ship = is_ship;
    }  
    void place_ship() {
        is_ship = true;
    }
    bool is_ship_cell() {
        return is_ship;
    }
    Coordinates draw(Rectangle bounds) {
        if(GuiButton(bounds, button_text.c_str()) && !was_pressed) {
            was_pressed = true;

            if(is_ship) {
                button_text = "X";
            }
            else {
                button_text = "O";
            }
            return cell_coords;
        }
        return (Coordinates){-1, -1};
    }
};

enum class ShipTargetStates {
  MISSED,
  HIT,
  SANK
};

class Ship {
protected:
    std::vector<Coordinates> ship_coords;
public:
    Ship(std::vector<Coordinates> coords) {
        ship_coords = coords;
    }
    int get_ship_length() {
        return ship_coords.size();
    }
    ShipTargetStates get_status(Coordinates coords) {
        ShipTargetStates status = ShipTargetStates::MISSED;
        for(size_t i = 0; i < ship_coords.size(); i++) {
            if(ship_coords.at(i).x == coords.x && ship_coords.at(i).y == coords.y) {
                ship_coords.erase(ship_coords.begin() + i);
                status = ShipTargetStates::HIT;
                break;
            }
        }
        if(status == ShipTargetStates::HIT && ship_coords.size() == 0) {
            status = ShipTargetStates::SANK;
        }
        return status;
    }
    void append_cell(Coordinates cell) {
        ship_coords.push_back(cell);
    }
    void print_ship() {
        std::cout << "Printing ship\n";
        for(auto& coord : ship_coords) {
            std::cout << '\t' << coord.x << ',' << coord.y << '\n';
        }
    }
};



void draw_board(std::vector<std::vector<Cell>>& cells, std::vector<Ship>& ships);
std::vector<std::vector<Cell>> create_cells();
void check_ships(std::vector<Ship>& ships, Coordinates coords);
std::vector<Ship> generate_ships(std::vector<std::vector<Cell>>& cells);
void draw_win_screen();
bool has_game_ended(std::vector<Ship>& ships);

int main(int argc, char* argv[]) {
    srand(time(0));
    InitWindow(800, 600, "Battleship");
    SetTargetFPS(60);
    
    std::vector<std::vector<Cell>> cells = create_cells();
    std::vector<Ship> ships = generate_ships(cells);

    for(auto& s : ships) {
        s.print_ship();
    }
        
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if(has_game_ended(ships)) {
            draw_win_screen();
        }
        else {
            draw_board(cells, ships);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void draw_win_screen() {
    GuiLabel((Rectangle){400, 300, 200, 10}, "YOU WON!");
}

bool has_game_ended(std::vector<Ship>& ships) {
    for(auto& ship: ships) {
        if(ship.get_ship_length() != 0) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<Cell>> create_cells() {
    std::vector<std::vector<Cell>> cells = {};
    for(int x = 0; x < BOARD_SIZE_X; x++) {
        cells.push_back({});
        for(int y = 0; y < BOARD_SIZE_Y; y++) {
            cells.at(x).push_back(Cell((Coordinates){x, y}));
        }
    }
    return cells;
}

void draw_board(std::vector<std::vector<Cell>>& cells, std::vector<Ship>& ships) {
    for(size_t x = 0; x < cells.size(); x++) {
        for(size_t y = 0; y < cells.at(x).size(); y++) {
            Coordinates coords = cells.at(x).at(y).draw((Rectangle){
                RECT_POSITION_CHANGE_X * (x+1),
                RECT_POSITION_CHANGE_Y * (y+1),
                RECT_SIZE_X,
                RECT_SIZE_Y
            });
            if(coords.x != -1 && coords.y != -1) {
                check_ships(ships, coords);
            }
        }
    }
}

std::vector<Ship> generate_n_cell_ships(std::vector<std::vector<Cell>>& cells, int n, int count) {
    std::vector<Ship> ships = {};
    for(int i = 0; i < count; i++) {
        Ship ship = Ship({});
      
        while(ship.get_ship_length() < n) {
            int x = rand() % cells.size();
            int y = rand() % cells.at(x).size();

            if(cells.at(x).at(y).is_ship_cell()) {
                continue;
            }
            int current_addition = 1;
            std::map<Coordinates, bool> possibilities = {
            {(Coordinates){1, 0}, true},
            {(Coordinates){-1, 0}, true},
            {(Coordinates){0, 1}, true},
            {(Coordinates){0,-1}, true},
            };
            for(int current_addition = 0; current_addition < n; current_addition++) {
                if(x + current_addition + 1 > cells.size() - 1 || cells.at(x + current_addition + 1).at(y).is_ship_cell()) {
                    possibilities.at({1, 0}) = false;
                }
                if(x - current_addition - 1 < 0 || cells.at(x - current_addition - 1).at(y).is_ship_cell()) {
                    possibilities.at({-1, 0}) = false;
                }
                if(y + current_addition + 1 > cells.at(x).size() - 1 || cells.at(x).at(y + current_addition + 1).is_ship_cell()) {
                    possibilities.at({0, 1}) = false;
                }
                if(y - current_addition - 1 < 0 || cells.at(x).at(y - current_addition - 1).is_ship_cell()) {
                    possibilities.at({0, -1}) = false;
                }
            }
            std::vector<Coordinates> actual_possibilites = {};
            for(auto& possibility : possibilities) {
                if(possibility.second) {
                    actual_possibilites.push_back(possibility.first);
                }
            }

            Coordinates chosenPossibility = actual_possibilites.at(rand() % actual_possibilites.size());
            for(int i = 1; i <= n; i++) {
                Coordinates coords = (Coordinates){x+chosenPossibility.x * i, y+chosenPossibility.y * i};
                ship.append_cell(coords);
                cells.at(coords.x).at(coords.y).place_ship();
            }
        }
        ships.push_back(ship);
    }
    return ships;
}

std::vector<Ship> generate_ships(std::vector<std::vector<Cell>>& cells) {
    std::vector<Ship> ships = {};

    std::vector<Ship> three_cell = generate_n_cell_ships(cells, 3, THREE_CELL_SHIPS);
    std::vector<Ship> two_cell = generate_n_cell_ships(cells, 2, TWO_CELL_SHIPS);
    
    ships.insert(std::end(ships), std::begin(three_cell), std::end(three_cell));
    ships.insert(std::end(ships), std::begin(two_cell), std::end(two_cell));
    
    return ships;
}

void check_ships(std::vector<Ship>& ships, Coordinates coords) {
    ShipTargetStates status = ShipTargetStates::HIT;
    for(auto& ship : ships) {
        status = ship.get_status(coords);
        if(status != ShipTargetStates::MISSED) {
            break;
        }
    }
    switch(status) {
        case(ShipTargetStates::HIT):
            std::cout << "Trafiony ale nie zatopiony\n";
            break;
        case(ShipTargetStates::MISSED):
            std::cout << "Nie trafiles\n";
            break;
        case(ShipTargetStates::SANK):
            std::cout << "Trafiony i zatopiony\n";
            break;
    }
}
