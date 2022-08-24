#include <iostream>
#include<cstring>
using namespace std;

class NBAPlayer
{
protected:
        char * ime;
        char tim[40];
        double brPoeni, brSkokovi, brAsistencii;

public:
        NBAPlayer(char *_ime="", char *_tim="", double _brPoeni=0, double _brAsistencii=0, double _brSkokovi=0){
            ime= new char[strlen(_ime)+1];
            strcpy(ime,_ime);
            strcpy(tim,_tim);
            brPoeni=_brPoeni;
            brAsistencii=_brAsistencii;
            brSkokovi=_brSkokovi;
        }
        NBAPlayer(const NBAPlayer & nbap){
            ime= new char[strlen(nbap.ime)+1];
            strcpy(ime,nbap.ime);
            strcpy(tim,nbap.tim);
            brPoeni=nbap.brPoeni;
            brAsistencii=nbap.brAsistencii;
            brSkokovi=nbap.brSkokovi;
        }

        NBAPlayer &operator=(const NBAPlayer & nbap){
            if(this!=&nbap){
                delete [] ime;
                ime= new char[strlen(nbap.ime)+1];
                strcpy(ime,nbap.ime);
                strcpy(tim,nbap.tim);
                brPoeni=nbap.brPoeni;
                brAsistencii=nbap.brAsistencii;
                brSkokovi=nbap.brSkokovi;
            }
            return *this;
        }
        ~NBAPlayer(){
            delete [] ime;
        }
        double rating(){
            return brPoeni*0.45+brAsistencii*0.3+brSkokovi*0.25;
        }
        void print(){
            cout<<ime<<" - "<<tim<<endl;
            cout<<"Points: "<<brPoeni<<endl;
            cout<<"Assists: "<<brAsistencii<<endl;
            cout<<"Rebounds: "<<brSkokovi<<endl;
            cout<<"Rating: "<<rating()<<endl;
        }
};
class AllStarPlayer : public NBAPlayer {
    private:
        double ptsAllStar, assistAllStar, rebAllStar;
    public:
        AllStarPlayer(char *_ime="", char *_tim="", double _brPoeni=0, double _brAsistencii=0, double _brSkokovi=0, double _ptsAllStar=0, double _assistAllStar=0, double _rebAllStar=0) : NBAPlayer(_ime, _tim, _brPoeni, _brAsistencii, _brSkokovi){
            ptsAllStar=_ptsAllStar;
            assistAllStar=_assistAllStar;
            rebAllStar=_rebAllStar;
        }
        AllStarPlayer(NBAPlayer nbap, double _ptsAllStar=0, double _assistAllStar=0, double _rebAllStar=0) : NBAPlayer(nbap){
            ptsAllStar=_ptsAllStar;
            assistAllStar=_assistAllStar;
            rebAllStar=_rebAllStar;
        }
        AllStarPlayer(const AllStarPlayer &asp) : NBAPlayer(asp){
            ptsAllStar=asp.ptsAllStar;
            assistAllStar=asp.assistAllStar;
            rebAllStar=asp.rebAllStar;
        }

        AllStarPlayer & operator=(const AllStarPlayer &asp){
                NBAPlayer :: operator=(asp);
                ptsAllStar=asp.ptsAllStar;
                assistAllStar=asp.assistAllStar;
                rebAllStar=asp.rebAllStar;
        }
        double allStarRating() {
            return ptsAllStar*0.3+assistAllStar*0.4+rebAllStar*0.3;
        }
        double rating(){
            return (NBAPlayer::rating()+allStarRating())/2;
        }
        void print(){
            NBAPlayer::print();
            cout << "All Star Rating: " << allStarRating() << endl << "New Rating: " << (NBAPlayer::rating() + allStarRating()) / 2 << endl;
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
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
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
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }

    delete [] players;
    delete [] asPlayers;
}
