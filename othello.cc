/*************************************************************************
      Hunter Stout   -   4/13/2022
      othello.cc     -   Othello Board Class File.
*************************************************************************/

 #include "othello.h"
 #include "colors.h"
 #include <stdlib.h>
 using namespace std;

namespace main_savitch_14 {

    const int Othello::ROW;

//#################### B O A R D   D E S I G N ####################

    void Othello::display_status()const {
        string grid = "    ✦━━━━ ━━━━━ ━━━━━ ━━━━━ ━━━━━ ━━━━━ ━━━━━ ━━━━    ", grid_end = "┃";
        string ends = "✦━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━✦";
        string blank_line = "┃                                                      ┃";

        system("clear"); //Clears terminal.

        //Sets board header (A-H).
        cout << endl << RED << ends << endl << RED << "┃      ";
        cout << WHITE << "A     B     C     D     E     F     G     H ";
        cout << RED <<"    ┃" << endl << blank_line << endl;

        for(int i = 0; i < ROW; i++) { //Vertical side loop.

            cout << RED << "┃ " << WHITE << (i + 1) << "    "; //Sets side (1-8).

            for (int j = 0; j < ROW; j++) { //Horizontal side loop.

                if (!oboard[i][j].is_empty()) { //Sets chips.

                    if (oboard[i][j].is_purple()) { //Purple chip.
                        cout << MAGENTA << "⬤" << WHITE << "  " << grid_end <<"  " << RESET;
                    }
                    else if (oboard[i][j].is_green()) { //Green chip.
                        cout << GREEN << "⬤" << WHITE << "  " << grid_end << "  " << RESET; 
                    }
                }
                else { cout << RED << "■" << WHITE << "  " << grid_end << "  " << RESET; } //Blank chip.

                //End of row formatting.
                if (j == 6) grid_end = " ";
                if (j == 7) { cout << RED << "┃" << RESET; grid_end = "┃"; }
            }
            if (i == 7) cout << endl << RED << blank_line << RESET << endl << WHITE; //End line.
            else cout << endl << RED << grid_end << WHITE << grid << RED << grid_end << RESET << endl << WHITE; //Grid line.
        }
        cout << RED << ends << RESET << endl;
    }

    void Othello::restart() {
        chips placeholder;

        system("clear"); //Clears terminal.

        //Resets entire board.
        cout << RESET;
        for (int i = 0; i < ROW; i++) { //Vertical
            
            for (int j = 0; j < ROW; j++) { //Horizontal

                if((i == 3 && j == 4) || (i == 4 && j == 3)) { //Starting purple chips.
                    placeholder.set_purple();
                }
                else if((i == 3 && j == 3) || (i == 4 && j == 4)) { //Starting green chips.
                    placeholder.set_green();
                }
                else { placeholder.set_empty(); } //Empties board.

                oboard[i][j] = placeholder;
            }
        }
    }

//#################### M O V E   H E L P E R S ####################

    string Othello::get_user_move() const {
		string input;
		cout << endl << YELLOW << "Enter your move: " << RESET;
		getline(cin, input);
		return input;
    }

    void Othello::make_move(const std::string& move) {
        //Converts to integers.
        chips placeholder;
        int horizontal = toupper(move[0]) - 65, vertical = (move[1]) - 49;
        
        if (last_mover() && compass(move)) { //Human move.
            placeholder.set_purple();
            oboard[vertical][horizontal] = placeholder;
        }
        else if (last_mover()) { //Compass error.
            cout << endl << RED << "Illegal move, try again." << RESET << endl;
		    string new_move;
		    new_move = get_user_move();
		    while (!is_legal(new_move)) {
			    cout << endl << RED << "Illegal move, try again." << RESET << endl;
			    new_move = get_user_move();
            }
		    make_move(new_move);
        }
    }

    bool Othello::compass(const string& move) { //Finds direction of chip play.
        bool legal_line = false;
        int h = toupper(move[0]) - 65, v = (move[1]) - 49;
        if (oboard[v+1][h+1].is_green() && v <= 5 && h <= 5) {if(chip_update(move, '+', '+')) legal_line = 1;}//South East (1).
        if (oboard[v+1][h].is_green() && v <= 5) {if(chip_update(move, '+', '*')) legal_line = 1;} //South (2).
        if (oboard[v+1][h-1].is_green() && v <= 5 && h >= 2) {if(chip_update(move, '+', '-')) legal_line = 1;} //South West (3).
        if (oboard[v][h-1].is_green() && h >= 2) {if(chip_update(move, '*', '-')) legal_line = 1;} //West (4).
        if (oboard[v-1][h-1].is_green() && v >= 2 && h >= 2) {if(chip_update(move, '-', '-')) legal_line = 1;} //North West (5).
        if (oboard[v-1][h].is_green() && v >= 1) {if(chip_update(move, '-', '*')) legal_line = 1;} //North (6).
        if (oboard[v-1][h+1].is_green() && v >= 2 && h <= 5) {if(chip_update(move, '-', '+')) legal_line = 1;} //North East (7).
        if (oboard[v][h+1].is_green() && h <= 5) {if(chip_update(move, '*', '+')) legal_line = 1;} //East (8).
    return legal_line;
    }

    bool Othello::chip_update(const std::string& move, char vertical, char horizontal) { //Updates multiple chips in a line.

        //Limits - borders, change - compass direction, counter - amount of chips to change.
        int v_limit, h_limit, v_change, h_change, chip_counter = 1;
        bool legal_line = false;
        int h = toupper(move[0]) - 65, v = (move[1]) - 49; //Original cordinates.
        int h_cords = h, v_cords = v; //Copy cordinates.

        //Sets loop in compass direction & sets limit accordingly.
        if (vertical == '+') v_change = 1, v_limit = 6;
        else if (vertical == '-') v_change = -1, v_limit = 1;
        else v_change = 0, v_limit = 10;

        if (horizontal == '+') h_change = 1, h_limit = 6;
        else if (horizontal == '-') h_change = -1, h_limit = 1;
        else h_change = 0, h_limit = 10;

        v_cords += v_change;
        h_cords += h_change;

        //Checks for consecutive chips with an end cap.
        for (int i = v_cords, j = h_cords; i != v_limit && j != h_limit && !oboard[i+v_change][j+h_change].is_green(); i += v_change, j += h_change) {
            if (oboard[i+v_change][j+h_change].is_green()) {
                chip_counter++;
            }
            else if(oboard[i+v_change][j+h_change].is_purple()) {
                legal_line = true;
            }
            else if (oboard[i+v_change][j+h_change].is_empty()) {
                break;
            }
        }

        //Updates chips in the case of a legal line.
        if (legal_line) {
            chips placeholder;
            placeholder.set_purple();
            oboard[v][h] = placeholder;
            for (int i = 0, v_temp = v_cords, h_temp = h_cords; i < chip_counter; i++, v_temp += v_change, h_temp += h_change) {
                oboard[v_temp][h_temp] = placeholder;
            }
        }

    return legal_line;
    }

    bool Othello::is_legal(const std::string& move)const { //Checks a single chip move.
        bool legal = false;
        int h = toupper(move[0]) - 65, v = (move[1]) - 49;
        if (move.size() == 2 && h >= 0 && h <= 7 && v >= 0 && v <= 7 && oboard[v][h].is_empty()) { //Checks size and if both digits are 1-8
            //Basic scan in all directions of potential move, checks for opponent chip, next chip, and border.
            if (oboard[v+1][h+1].is_green() && !oboard[v+2][h+2].is_empty() && v <= 5 && h <= 5) legal = true; //SE (1).
            else if (oboard[v+1][h].is_green() && !oboard[v+2][h].is_empty() && v <= 5) legal = true; //S (2).
            else if (oboard[v+1][h-1].is_green() && !oboard[v+2][h-2].is_empty() && v <= 5 && h >= 2) legal = true; //SW (3).
            else if (oboard[v][h-1].is_green() && !oboard[v][h-2].is_empty() && h >= 2) legal = true; //W (4).
            else if (oboard[v-1][h-1].is_green() && !oboard[v-2][h-2].is_empty() && v >= 2 && h >= 2) legal = true; //NW (5).
            else if (oboard[v-1][h].is_green() && !oboard[v-2][h].is_empty() && v >= 2) legal = true; //N (6).
            else if (oboard[v-1][h+1].is_green() && !oboard[v-2][h+2].is_empty() && v >= 2 && h <= 5) legal = true; //NE (7).
            else if (oboard[v][h+1].is_green() && !oboard[v][h+2].is_empty() && h <= 5) legal = true; //E (8).
        }
        return legal;
    }

    bool Othello::is_game_over()const {
        int counter = 0;
        for(int i = 0; i < ROW; i++) { //Vertical side loop.
            for (int j = 0; j < ROW; j++) { //Horizontal side loop.
                if (oboard[i][j].is_empty()) {
                    counter++;
                }
            }
        }
        return (counter == 0); 
    }
}