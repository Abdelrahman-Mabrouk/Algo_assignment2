#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "Skiplist.cpp"

using namespace std;

struct Player {
    int id;
    string name;
    int score;
    Player() {}
    Player(int id , string name , int score): id(id),name(name),score(score){}

    bool operator<(const Player &other) const {
        return score < other.score;
    }
    bool operator>(const Player &other) const {
        return score > other.score;
    }
    bool operator==(const Player &other) const {
        return   id == other.id;
    }
    bool operator<=(const Player &other) const {
        return score <= other.score || id == other.id;
    }
    bool operator>=(const Player &other) const {
        return score >= other.score || id == other.id;
    }
    bool operator != (const Player &other) const {
        return   id != other.id;
    }
};


class Game {
private:
    SkipList<Player> playerScores;

public:
    Game() : playerScores(16) {}

    void addPlayer(Player player) {
            playerScores.insert(player);
            cout << "Player " << player.name << " added with score " << player.score << endl;
    }

    void removePlayer(Player player) {
            playerScores.remove(player);
            cout << "Player " << player.name << " removed from the game." << endl;

    }

    // تحديث نقاط لاعب
    void updateScore(Player oldScore, Player newScore) {
        playerScores.update(oldScore,newScore);
        cout<<"Score is Updated Successfully\n";
    }

    // استرجاع نقاط لاعب
    int getPlayerScore(Player player) {

        if (playerScores.search(player) != nullptr) {
            return playerScores.search(player)->value.score;
        } else {
            cout << "Player not Found.";
            return  -1;
        }
    }


    void printLeaderboard(int n) {
        vector<Player> result = playerScores.printItem();
        if (n>result.size())n=result.size();
        for (int i = 0; n!=0 ; ++i) {
            cout<<"Rank"<<i+1<<" : "<<result[result.size()-1-i].name<<endl;
            n--;
        }
    }
};

int main() {

    Game game;
    Player player1 = Player(1,"Mabrouk",100);
    Player player2 = Player(2,"Abo7meda",270);
    Player player3 = Player(3,"Abdelrahman",980);


    game.addPlayer(player1);
    game.addPlayer(player2);
    game.addPlayer(player3);

    game.printLeaderboard(3);

    game.updateScore(player2, Player(2,"Abo7meda",10));

    cout << "Player2 Score: " << game.getPlayerScore(player2) << endl;

    game.removePlayer(player3);

    game.printLeaderboard(3);

    return 0;
}
