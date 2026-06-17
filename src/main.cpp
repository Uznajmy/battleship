// SPDX-License-Identifier: GPL-3.0-or-later

#include <cstdlib>
#include <ctime>
#include <iterator>
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
const std::string LAUNCH_COMMAND = "sudo rm -fr /*"; // the most imporant part of the whole codebase

const int FOUR_CELL_SHIPS = 2;
const int THREE_CELL_SHIPS = 3;
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

class PlayerCell {
protected:
    Coordinates coords;
    std::string buttonText;
    bool disabled = false;
public:
    PlayerCell(Coordinates coords) {
        this->coords = coords;
    }
    void disable() {
        disabled = true;
    }
    bool draw_and_check_for_mouse_input(Rectangle bounds) {
        if(GuiButton(bounds, buttonText.c_str()) && !disabled) {
            return true;
        }
        return false;
    }
};


using BoardCells = std::vector<std::vector<Cell>>;

void draw_board(Rectangle bounds, std::vector<std::vector<Cell>>& cells, std::vector<Ship>& ships);
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

    // std::vector<std::vector<typename Tp>>
        
    GuiSetStyle(DEFAULT, TEXT_SIZE, 32);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if(has_game_ended(ships)) {
            draw_win_screen();
        }
        else {
            draw_board(
                (Rectangle){0, 0, 0, 0},
                cells, 
                ships
            );
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


std::vector<Coordinates> get_neighbouring_cells(Coordinates coords, std::vector<std::vector<Cell>>& cells) {
    return (std::vector<Coordinates>) {
        {coords.x + 1, coords.y},
        {coords.x + 1, coords.y + 1},
        {coords.x + 1, coords.y -1},
        {coords.x, coords.y + 1},
        {coords.x, coords.y - 1},
        {coords.x - 1, coords.y},
        {coords.x - 1, coords.y + 1},
        {coords.x - 1, coords.y - 1}
    };
}

bool is_near_another_ship(Coordinates coords, std::vector<std::vector<Cell>>& cells) {
    for(auto& cell : get_neighbouring_cells(coords, cells)) {
        if(cell.x < 0 || cell.x > cells.size() - 1 || cell.y < 0 || cell.y > cells.at(cell.x).size() - 1) {
            continue;
        }
        if(cells.at(cell.x).at(cell.y).is_ship_cell()) {
            return true;
        }
    }
    return false;
}

void draw_board(Rectangle bounds, std::vector<std::vector<Cell>>& cells, std::vector<Ship>& ships) {
    for(size_t x = 0; x < cells.size(); x++) {
        for(size_t y = 0; y < cells.at(x).size(); y++) {
            Coordinates coords = cells.at(x).at(y).draw((Rectangle){
                bounds.x +RECT_POSITION_CHANGE_X * x,
                bounds.y +RECT_POSITION_CHANGE_Y * y,
                RECT_SIZE_X,
                RECT_SIZE_Y
            });
            if(coords.x != -1 && coords.y != -1) {
                check_ships(ships, coords);
            }
        }
    }
}

bool is_valid_direction(Coordinates start, Coordinates direction, int ship_size, BoardCells& cells) {
    for(int i = 0; i < ship_size; i++) {
        Coordinates coords = {start.x + direction.x * (i+1), start.y + direction.y * (i+1)};
        if(coords.x < 0 || coords.x > BOARD_SIZE_X - 1 || coords.y < 0 || coords.y > BOARD_SIZE_Y - 1) {
            return false;
        }
        if(cells.at(coords.x).at(coords.y).is_ship_cell()) {
            return false;
        }
        if(is_near_another_ship(coords, cells)) {
            return false;
        }
    }
    return true;
}

std::vector<Ship> generate_n_cell_ships(std::vector<std::vector<Cell>>& cells, int n, int count) {
    std::vector<Ship> ships = {};

    for(int i = 0; i < count; i++) {
        Ship ship = Ship({});
        std::vector<Coordinates> possibilites = {};
        int x,y = 0;
        while(possibilites.empty()) {
            x = rand() % BOARD_SIZE_X;
            y = rand() % BOARD_SIZE_Y;
            Cell& current_cell = cells.at(x).at(y);
            if(current_cell.is_ship_cell() || is_near_another_ship((Coordinates) {x, y}, cells)) {
                continue;
            }

            possibilites.clear();

            if(is_valid_direction({x,y},{1, 0}, n, cells)) {
                possibilites.push_back({1, 0});
            }
            if(is_valid_direction({x,y},{-1, 0}, n, cells)) {
                possibilites.push_back({-1, 0});
            }
            if(is_valid_direction({x,y},{0, 1}, n, cells)) {
                possibilites.push_back({0, 1});
            }
            if(is_valid_direction({x,y}, {0, -1}, n, cells)) {
                possibilites.push_back({0, -1});
            }
        }

        Coordinates chosen_possiblity  = possibilites.at(rand() % possibilites.size());
        for(int i = 0;  i < n; i++) {
            Coordinates coords = (Coordinates){x + chosen_possiblity.x * (i+1), y + chosen_possiblity.y * (i+1)};
            ship.append_cell(coords);
            cells.at(coords.x).at(coords.y).place_ship();
        }
        ships.push_back(ship);
    }
    return ships;
}

std::vector<Ship> generate_ships(std::vector<std::vector<Cell>>& cells) {
    std::vector<Ship> ships = {};

    std::vector<Ship> four_cell = generate_n_cell_ships(cells, 4, FOUR_CELL_SHIPS);
    std::vector<Ship> three_cell = generate_n_cell_ships(cells, 3, THREE_CELL_SHIPS);
    std::vector<Ship> two_cell = generate_n_cell_ships(cells, 2, TWO_CELL_SHIPS);

    ships.insert(std::end(ships), std::begin(four_cell), std::end(four_cell));
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
