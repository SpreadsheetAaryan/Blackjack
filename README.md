# Blackjack Game

## Overview
This is a simple implementation of a Blackjack game in C++. The game allows two players to play against each other, betting money on each round, and the winner takes the bet. The game can be played for a specified number of rounds (1, 3, 5, or 7).

## Features
- Players can bet on each round.
- Cards are dealt randomly.
- Players can choose to hit (receive another card) or stay (end their turn).
- The game tracks player money and announces the winner of each round and the overall winner based on the number of rounds played.

## How to Play
1. **Starting the Game:**
   - Players start with $100.00 each.
   - Choose the number of rounds to play (1, 3, 5, or 7).
   
2. **Game Rounds:**
   - Each round, players bet a specified amount of money.
   - Players are dealt two cards initially.
   - Each player takes turns to decide whether to hit (receive another card) or stay (end their turn).
   - The round ends when a player's hand value exceeds 21 (busted).
   - The player closest to 21 without exceeding it wins the round and takes the bet.

3. **End of Game:**
   - The game ends when all rounds are completed.
   - The player with the most round wins (best out of the specified rounds) is declared the overall winner.
   - If a player runs out of money during the game, the other player automatically wins.

## Implementation Details
- **Dependencies:** This game uses standard C++ libraries including `<iostream>`, `<vector>`, `<unordered_map>`, `<string>`, `<random>`, `<thread>`, and `<chrono>`.
- **Data Structures:** `unordered_map` is used to map card names to their respective values.
- **Functions:**
  - `isBusted(vector<string> &hand)`: Checks if a player's hand value exceeds 21.
  - `gameOver(int loser, int &p1m, int &p2m, int bet)`: Handles the end of a round when a player busts.
  - `deal(int cards, vector<string> &hand)`: Deals a specified number of cards randomly to a player's hand.
  - `displayValue(vector<string> &hand)`: Displays the current total value of a player's hand.
  - `compareValue(vector<string> &hand1, vector<string> &hand2)`: Compares the total values of two players' hands to determine the winner of a round.
  - `player1Move(vector<string> &hand)`, `player2Move(vector<string> &hand)`: Simulates a player's turn to decide whether to hit or stay.

## Getting Started
To run the game:
- Compile the source code (`blackjack.cpp`) using a C++ compiler.
- Execute the compiled binary.
