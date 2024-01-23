------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -Wall -Werror -Wpedantic -std=c++17 Candystore.cpp Board.cpp Player.cpp  boardDriver.cpp -o candyland
Run: ./candyland

------------------------
DEPENDENCIES
------------------------
Board.h, Player.h, Candystore.h, riddles.txt, candy.txt, winner.txt and characters.txt must be in the same directory as the cpp files in order to compile.

------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Fall 2023 Project 2
Author: David Thumma
Recitation: 605 - Vrinda Anil
Date: Dec 7 2023

------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game fashioned after the game Candyland. It is a 2 player game so it begins with asking for both players names and characters selections and then allows them to visit a candystore.  A main menu appears prompting player 1 to continue with their turn after this.  The goal of the game is to reach the Castle before the other player.  There are many candystores, special events, treasures and calamities that can occur/appear on the way.  There are also random Marshmallow hailstorms which can possibly blow players back to the start. You can use Candy to assist yourself or make the other players journey harder.  The winner's stats are written on the winner.txt file after the game ends.