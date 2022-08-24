#include <iostream>
#include <string.h>
using namespace std;
class PlDrustvo
{
private:
    char *ime;
    int brTuri, brClenovi;

public:
        PlDrustvo(char * _ime="",int _brTuri=0, int _brClenovi=0){
            ime=new char[strlen(_ime)+1];
            strcpy(ime,_ime);
            brTuri=_brTuri;
            brClenovi=_brClenovi;
        }
        PlDrustvo(const PlDrustvo & pd){
            ime=new char[strlen(pd.ime)+1];
            strcpy(ime,pd.ime);
            brTuri=pd.brTuri;
            brClenovi=pd.brClenovi;
        }
        PlDrustvo & operator=(const PlDrustvo & pd){
            if(this!=&pd){
                delete [] ime;
                ime=new char[strlen(pd.ime)+1];
                strcpy(ime,pd.ime);
                brTuri=pd.brTuri;
                brClenovi=pd.brClenovi;
            }
            return *this;
        }
        PlDrustvo operator+(const PlDrustvo & pd){
            return PlDrustvo(brClenovi > pd.brClenovi ? ime : pd.ime, brClenovi > pd.brClenovi ? brTuri : pd.brTuri, brClenovi + pd.brClenovi);
        }
        bool operator>(const PlDrustvo & pd){
            if(brClenovi>pd.brClenovi){
                return true;
            }else return false;
        }

        bool operator<(const PlDrustvo & pd){
            return !(*this > pd);
        }
        friend ostream &operator<<(ostream & out,PlDrustvo & pd){
            out << "Ime: " << pd.ime << " Turi: " << pd.brTuri << " Clenovi: " << pd.brClenovi << endl;
        }
        int getClenovi(){
            return brClenovi;
        }
};

void najmnoguClenovi(PlDrustvo *pd, int n)
{
    int maks = 0;
    for(int i = 0; i < n; i++)
    {
        if(pd[i].getClenovi() > pd[maks].getClenovi())
        {
            maks = i;
        }
    }
    cout << "Najmnogu clenovi ima planinarskoto drustvo: " << pd[maks];
}
int main()
{
    PlDrustvo drustva[3];
    PlDrustvo pl;
    for (int i=0;i<3;i++)
   	{
    	char ime[100];
    	int brTuri;
    	int brClenovi;
    	cin>>ime;
    	cin>>brTuri;
    	cin>>brClenovi;
    	PlDrustvo p(ime,brTuri,brClenovi);
        drustva[i] = p;

   	}

    pl = drustva[0] + drustva[1];
    cout<<pl;

    najmnoguClenovi(drustva, 3);

    return 0;
}
