/*************************************************************************
      Hunter Stout   -   4/13/2022
      othello.h      -   Othello Board Header File.
*************************************************************************/

#include "game.h"
#include "chips.h"
#include <iostream>
#include <queue>

namespace main_savitch_14 {

    class Othello : public game {

        public:
            static const int ROW = 8; //Max row size.
            Othello() {}

        protected:
            //Design
            virtual void display_status()const;
            virtual void restart();

            //Helpers
            bool compass(const std::string& move);
            bool chip_update(const std::string& move, char vertical, char horizontal); //v & h are compass directions.

            //Moves & Helpers
            virtual std::string get_user_move() const;
            virtual void make_move(const std::string& move);
            virtual bool is_legal(const std::string& move)const;

            //Rules - (TODO, part 2)
            virtual game* clone()const {game* test; return test;}
            virtual void compute_moves(std::queue<std::string>& moves)const {}
            virtual int evaluate()const {return 1;}
            virtual bool is_game_over()const;

        private:
            chips oboard[ROW][ROW];
    };
}