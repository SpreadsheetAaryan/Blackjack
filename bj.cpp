#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

unordered_map<string, int> map;

struct Player {
    vector<string> hand;
    int money;
};

void player1Move(vector<string> &hand);
void player2Move(vector<string> &hand);
bool isBusted(vector<string> &hand);
void gameOver(int loser, int &p1m, int &p2m, int bet);
void deal(int cards, vector<string> &hand);
void displayValue(vector<string> &hand);
int compareValue(vector<string> &hand1, vector<string> &hand2);

int main() {

    map.insert(make_pair("2", 2));
    map.insert(make_pair("3", 3));
    map.insert(make_pair("4", 4));
    map.insert(make_pair("5", 5));
    map.insert(make_pair("6", 6));
    map.insert(make_pair("7", 7));
    map.insert(make_pair("8", 8));
    map.insert(make_pair("9", 9));
    map.insert(make_pair("10", 10));
    map.insert(make_pair("J", 10));
    map.insert(make_pair("Q", 10));
    map.insert(make_pair("K", 10));
    map.insert(make_pair("A", 1));
    map.insert(make_pair("Ace", 11));

    Player p1;
    Player p2;

    p1.money = 100;
    p2.money = 100;

    int rounds;

    cout << "Welcome to Blackjack! Get as close as you can to 21, but don't go over!" << endl;
    this_thread::sleep_for(chrono::seconds(3));

    cout << "Choose how many rounds you want to play! Your options are 1, 3, 5, and 7!" << endl;
    while (!(cin >> rounds) && rounds != 1 && rounds != 3 && rounds != 5 && rounds != 7) {
        cout << "Invalid input. Please enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (rounds > 1) {
        cout << "It will be best out of " << rounds << "!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    } else if (rounds == 1) {
        cout << "Only 1 round! Winner takes all!" << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    int p1s = 0;
    int p2s = 0;
    int lead;

    for (int i = 1; i <= rounds; i++) {

        p1.hand.clear();
        p2.hand.clear();

        cout << "" << endl;
        cout << "Player 1 has $" << p1.money << ".00!" << endl;
        cout << "Player 2 has $" << p2.money << ".00!" << endl;
        cout << "" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        int bet1;
        cout << "Player 1, choose how much you want to bet for this round!" << endl;
        while (!(cin >> bet1) && bet1 > p1.money) {
            cout << "Invalid input. Please enter a smaller number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int bet2;
        cout << "Player 2, choose how much you want to bet for this round!" << endl;
        while (!(cin >> bet2) && bet2 > p1.money) {
            cout << "Invalid input. Please enter a smaller number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "It is round " << i << "!" << endl;
        if (p2s > p1s) {
            lead = 2;
            cout << "The score is " << p1s << " - " << p2s << " with Player " << lead << " in the lead!" << endl;
        } else if (p1s > p2s) {
            lead = 1;
            cout << "The score is " << p1s << " - " << p2s << " with Player " << lead << " in the lead!" << endl;
        } else {
            cout << "The score is " << p1s << " - " << p2s << " with a tie game!!!" << endl;
        }
        cout << "" << endl;
        this_thread::sleep_for(chrono::seconds(2));

        cout << "Player 1's initial hand: " << endl;
        deal(2, p1.hand);
        displayValue(p1.hand);
        cout << "" << endl;

        this_thread::sleep_for(chrono::seconds(3));
        cout << "Player 2's initial hand: " << endl;
        deal(2, p2.hand);
        displayValue(p2.hand);
        cout << "" << endl;

        while (true) {
            if (!isBusted(p1.hand)) {
                player1Move(p1.hand);
            } else {
                gameOver(1, p1.money, p2.money, bet1);
                p2s++;
                break;
            }

            if (isBusted(p1.hand)) {
                gameOver(1, p1.money, p2.money, bet1);
                p2s++;
                break;
            }

            if (!isBusted(p2.hand)) {
                player2Move(p2.hand);
            } else {
                gameOver(2, p1.money, p2.money, bet2);
                p1s++;
                break;
            }

            if (isBusted(p2.hand)) {
                gameOver(2, p1.money, p2.money, bet2);
                p1s++;
                break;
            }

            if (compareValue(p1.hand, p2.hand) == 1) {

                cout << "" << endl;
                cout << "Player 1 has won the game!!!" << endl;
                p1.money += bet2;
                p2.money -= bet2;
                p1s++;
                break;

            } else if (compareValue(p1.hand, p2.hand) == 2) {

                cout << "" << endl;
                cout << "Player 2 has won the game!!!" << endl;
                p2.money += bet1;
                p1.money -= bet1;
                p2s++;
                break;

            } else {

                cout << "" << endl;
                cout << "It's a tie!" << endl;
                p1.hand.clear();
                p2.hand.clear();
                continue;

            }

        }

        if (i == rounds && rounds != 1) {
            cout << "The game is over with Player " << lead << " winning the game " << p1s << " - " << p2s << "!!!" << endl;
            exit(0);
        } else if (p1s == (rounds + 1) / 2 && rounds != 1) {
            cout << "The game is over with Player " << lead << " winning the game " << p1s << " - " << p2s << "!!!" << endl;
            exit(0);
        } else if (p2s == (rounds + 1) / 2 && rounds != 1) {
            cout << "The game is over with Player " << lead << " winning the game " << p1s << " - " << p2s << "!!!" << endl;
            exit(0);
        } else if (i == rounds && i == 1 && compareValue(p1.hand, p2.hand) == 2) {
            lead = 2;
            cout << "The game is over with Player " << lead << " winning the game " << p1s << " - " << p2s << "!!!" << endl;
            exit(0);
        }
        else if (i == rounds && i == 1 && compareValue(p1.hand, p2.hand) == 1) {
            lead = 1;
            cout << "The game is over with Player " << lead << " winning the game " << p1s << " - " << p2s << "!!!" << endl;
            exit(0);
        }

        if (p1.money <= 0) {
            cout << "The game is over with Player 2 winning the game! Player 1 has gone bankrupt!" << endl;
            exit(0);
        } else if (p2.money <= 0) {
            cout << "The game is over with Player 1 winning the game! Player 2 has gone bankrupt!" << endl;
            exit(0);
        }

    }
}

bool isBusted(vector<string> &hand) {
    int sum = 0;
    for (int i = 0; i < hand.size(); i++) {
        sum += map[hand[i]];
    }
    bool busted;
    sum > 21 ? busted = true : busted = false;
    return busted;
}

void gameOver(int loser, int &p1m, int &p2m, int bet) {
    cout << "Player " << loser << " has busted!!!" << endl;
    int winner;
    loser == 1 ? winner = 2 : winner = 1;
    cout << "Player " << winner << " has won the game!!!" << endl;

    loser == 1 ? p2m += bet : p1m += bet;
    loser == 1 ? p1m -= bet : p2m -= bet;
}

void displayValue(vector<string> &hand) {
    int sum = 0;
    for (int i = 0; i < hand.size(); i++) {
        sum += map[hand[i]];
    }

    cout << "Your current hand value is " << sum << endl;
}

void deal(int cards, vector<string> &hand) {
    for (int i = 0; i < cards; i++) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 13);

        int randomNumber = dis(gen);

        auto it = map.begin();
        advance(it, randomNumber);

        if (cards > 1) {
            if (i == 0) {
                cout << "Your first random card is " << it->first << endl;
                this_thread::sleep_for(chrono::seconds(1));
            } else {
                cout << "Your second random card is " << it->first << endl;
                this_thread::sleep_for(chrono::seconds(1));
            }
        } else {
            cout << "Your random card is " << it->first << endl;
            cout << "" << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        hand.push_back(it->first);

        if (cards > 1) {
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
} 

void player1Move(vector<string> &hand) {
    cout << "It is Player 1's turn!" << endl;
    cout << "" << endl;
    this_thread::sleep_for(chrono::seconds(1));

    bool end = false;

    while (!end) {

        if (!isBusted(hand)) {
            cout << "You have 2 choices! You can choose to hit or stay!" << endl;
            cout << "If you want to hit, type h, if you want to stay, press enter: " << endl;

            displayValue(hand);

            string input;
            cin >> input;

            if (input == "h" || input == "H" || input == "hit" || input == "Hit" || input == "HIT") {
                deal(1, hand);
            } else {
                end = true;
            }
        } else {
            end = true;
            return;
        }
    }
}

void player2Move(vector<string> &hand) {
    cout << "" << endl;
    cout << "It is Player 2's turn!" << endl;
    cout << "" << endl;
    this_thread::sleep_for(chrono::seconds(1));

    bool end = false;

    while (!end) {

        if (!isBusted(hand)) {
            cout << "You have 2 choices! You can choose to hit or stay!" << endl;
            cout << "If you want to hit, type h, if you want to stay, press enter: " << endl;

            displayValue(hand);

            string input;
            cin >> input;

            if (input == "h" || input == "H" || input == "hit" || input == "Hit" || input == "HIT") {
                deal(1, hand);
            } else {
                end = true;
            }
        } else {
            end = true;
            return;
        }
    }
}

int compareValue(vector<string> &hand1, vector<string> &hand2) {
    int sum1 = 0;
    for (int i = 0; i < hand1.size(); i++) {
        sum1 += map[hand1[i]];
    }

    int sum2 = 0;
    for (int i = 0; i < hand2.size(); i++) {
        sum2 += map[hand2[i]];
    }

    if (sum1 > sum2) {
        return 1;
    } else if (sum2 > sum1) {
        return 2;
    } else {
        return 3;
    }
}