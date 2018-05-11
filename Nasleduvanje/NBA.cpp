#include<iostream>
#include<cstring>
using namespace std;

class NBAPlayer {
protected:
  char * name;
  char team[40];
  double points;
  double assists;
  double rebounds;

  void copy(const NBAPlayer &np) {
    name = new char[strlen(np.name) + 1];
    strcpy(name,np.name);
    strcpy(team,np.team);
    points = np.points;
    assists = np.assists;
    rebounds = np.rebounds;
  }
public:

  NBAPlayer() {
    name = new char[0];
    points = assists = rebounds = 0;
    strcpy(team,"");
  }

  ~NBAPlayer() {
    delete [] name;
  }

  NBAPlayer(const char * ime, const char * tim, double p, double a, double r) {
    name = new char[strlen(ime) + 1];
    strcpy(name,ime);
    strcpy(team,tim);
    points = p;
    assists = a;
    rebounds = r;
  }

  NBAPlayer(const NBAPlayer &np){
    copy(np);
  }

  NBAPlayer &operator =(const NBAPlayer &np) {
    if (this != &np) {
      delete [] name;
      copy(np);
    }
    return *this;
  }

  double rating() {
    return points * 0.45 + assists * 0.3 + rebounds * 0.25;
  }

  void print() {
    cout << name << " - " << team << endl;
    cout << "Points: " << points << endl;
    cout << "Assists: " << assists << endl;
    cout << "Rebounds: " << rebounds << endl;
    cout << "Rating: " << rating() << endl;
  }
};

class AllStarPlayer : public NBAPlayer {
private:
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  void copyAllStar(const AllStarPlayer &all) {
    allStarPoints = all.allStarPoints;
    allStarAssists = all.allStarAssists;
    allStarRebounds = all.allStarRebounds;
  }
public:

  AllStarPlayer()
  : NBAPlayer() {
    allStarPoints = allStarAssists = allStarRebounds = 0;
  }

  AllStarPlayer(const char * ime, const char * tim, double p, double a, double r,
                double allP, double allA, double allR) : NBAPlayer(ime,tim,p,a,r) {
                  allStarPoints = allP;
                  allStarAssists = allA;
                  allStarRebounds = allR;
                }

  AllStarPlayer(const NBAPlayer &np, double asp, double asa, double asr)
  : NBAPlayer(np) {
    allStarPoints = asp;
    allStarAssists = asa;
    allStarRebounds = asr;
  }

  AllStarPlayer(const AllStarPlayer &all)
  : NBAPlayer(all){
    copyAllStar(all);
  }

  AllStarPlayer & operator = (const AllStarPlayer &all) {
    if (this != &all) {
      delete [] name;
      copy(all);
      copyAllStar(all);
    }
    return *this;
  }

  double allStarRating() {
    return allStarPoints * 0.3 + allStarAssists * 0.4 + allStarRebounds * 0.3;
  }

  double rating() {
    return (NBAPlayer::rating() + allStarRating()) / 2;
  }

  void print() {
    NBAPlayer::print();
    cout << "All Star Rating: " << allStarRating() << endl;
    cout << "New Rating: " << rating() << endl;
  }

};

int main() {

  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarAssists);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarAssists);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    
    delete [] players;
    delete [] asPlayers;
}
