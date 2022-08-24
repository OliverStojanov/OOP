#include <iostream>
#include <cstring>
using namespace std;

class InvalidPassword{
    private:
        char poraka[100];
    public:
        InvalidPassword(char * p){
            strcpy(poraka,p);
        }
        void message(){
            cout<<poraka<<endl;
        }
};
class InvalidEmail{
    private:
        char poraka[100];
    public:
        InvalidEmail(char * p){
            strcpy(poraka,p);
        }
        void message(){
            cout<<poraka<<endl;
        }
};
class MaximumSizeLimit{
    private:
        int br;
    public:
        MaximumSizeLimit(int b){
            br=b;
        }
        void message(){
            cout<<"You can't add more than "<<br<<" users."<<endl;
        }
};

class User{
    protected:
        char username[50], password[50], email[50];
    public:
        User(char * user="",char * pass="", char * mail=""){
            strcpy(username,user);
            bool mali=false,golemi=false, broj=false;
            for(int i=0;i<strlen(pass);i++){
                if(islower(pass[i])){
                    mali=true;
                }else if(isupper(pass[i])){
                    golemi=true;
                }else if(isdigit(pass[i])){
                    broj=true;
                }else if(mali && golemi && broj){
                    strcpy(password,pass);
                    break;
                }
            }
            if(!(mali && golemi && broj)){
                throw InvalidPassword("Password is too weak.");
            }
            int brMajmunce=0;
            for(int i=0;i<strlen(mail);i++){
                if(mail[i]=='@'){
                    brMajmunce++;
                }
            }
            if(brMajmunce==1){
                strcpy(email,mail);
            }else{
                throw InvalidEmail("Mail is not valid.");
            }
        }
        virtual double popularity() = 0;
};

class FacebookUser : public User{
    private:
        int prijateli,lajkovi,komentari;
    public:
        FacebookUser(char * user="",char * pass="", char * mail="", int p=0, int like=0, int kom=0) : User(user,pass,mail){
            prijateli=p;
            lajkovi=like;
            komentari=kom;
        }
        double popularity(){
            return prijateli + lajkovi*0.1 + komentari*0.5;
        }

};
class TwitterUser : public User{
    private:
        int sledbenici, tvitovi;
    public:
        TwitterUser(char *user="",char *pass="", char *mail="", int sled=0, int tvit=0) : User(user,pass,mail){
            sledbenici=sled;
            tvitovi=tvit;
        }
        double popularity(){
            return sledbenici + tvitovi*0.5;
        }
};

class SocialNetwork{
    private:
        User ** user;
        int korisnici;
        int maxKorisnici;
    public:
        SocialNetwork(){
            user = new User*[0];
            korisnici = 0;
            maxKorisnici=5;
        }
        ~SocialNetwork(){
            delete [] user;
        }
        SocialNetwork & operator+=(User *u){
            if(korisnici+1<=maxKorisnici){
                User **tmp= new User*[korisnici+1];
                for(int i=0; i<korisnici; i++){
                    tmp[i]=user[i];
                }
                delete [] user;
                user = tmp;
                user[korisnici]=u;
                korisnici++;
            }else{
                throw MaximumSizeLimit(maxKorisnici);
            }
            return *this;
        }
        double avgPopularity(){
            double vkupno=0;
            for(int i=0; i<korisnici; i++){
                vkupno+=user[i]->popularity();
            }
            return vkupno/korisnici;
        }
        void changeMaximumSize(int number){
            maxKorisnici=number;
        }
};

int main() {

  SocialNetwork network = SocialNetwork();
    int n;
    cin >> n;
    char username[50];
    char password[50];
    char email[50];
    int userType;
    for (int i=0; i < n; ++i) {
      cin >> username;
      cin >> password;
      cin >> email;
      cin >> userType;
      if (userType == 1) {
        int friends;
        int likes;
        int comments;
        cin >> friends >> likes >> comments;

        try{
            User * u = new FacebookUser(username,password,email,friends,likes,comments);
            network += u;
        }
        catch(InvalidPassword &pass){
            pass.message();
        }
        catch(InvalidEmail &mail){
            mail.message();
        }
        catch(MaximumSizeLimit &msl){
            msl.message();
        }
      }
      else {
        int followers;
        int tweets;
        cin >> followers >> tweets;

        try{
            User * u= new TwitterUser(username,password,email,followers,tweets);
            network += u;
        }
        catch(InvalidPassword &pass){
            pass.message();
        }
        catch(InvalidEmail &mail){
            mail.message();
        }
        catch(MaximumSizeLimit &msl){
            msl.message();
        }
      }

    }
    network.changeMaximumSize(6);
    cin >> username;
    cin >> password;
    cin >> email;
    int followers;
    int tweets;
    cin >> followers >> tweets;

    try{
        User * u= new TwitterUser(username,password,email,followers,tweets);
        network += u;
    }
    catch(InvalidPassword &pass){
        pass.message();
    }
    catch(InvalidEmail &mail){
        mail.message();
    }
    catch(MaximumSizeLimit &msl){
        msl.message();
    }
    cout << network.avgPopularity();

}
