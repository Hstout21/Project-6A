/*************************************************************************
      Hunter Stout   -   4/13/2022
      chips.h        -   Othello Chips Header File.
*************************************************************************/

#ifndef CHIPS_H
#define CHIPS_H
class chips {

    public:
        //Constructor
        chips() {empty = true, purple = false; green = false;}

        //Getters
        bool is_empty()const {return empty;}
        bool is_purple()const {return purple;}
        bool is_green()const {return green;}

        //Setters
        void set_empty() {empty = 1; purple = 0; green = 0;} //Sets spot as empty, no chip.
        void set_purple() {empty = 0; purple = 1; green = 0;} //Sets spot as player chip.
        void set_green() {empty = 0; purple = 0; green = 1;} //Sets spot as computer chip.

    private:
        bool empty; //No Chip
        bool purple; //User Chip
        bool green; //Computer Chip

};
#endif