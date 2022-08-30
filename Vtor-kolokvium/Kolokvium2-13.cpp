#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Image{
    protected:
        char * ime;
        char sopstvenik[50];
        int sirina, visina;
    public:
        Image(const char * i="untitled", const char * s="unknown", int si=800, int vi=800){
            ime = new char [strlen(i)+1];
            strcpy(ime,i);
            strcpy(sopstvenik,s);
            sirina=si;
            visina=vi;
        }

        virtual int fileSize() const{
            return sirina*visina*3;
        }
        bool operator>(Image &i){
            return fileSize()>i.fileSize();
        }
        friend ostream & operator<<(ostream &out, Image &i){
            return out<<i.ime<<" "<<i.sopstvenik<<" "<<i.fileSize()<<endl;
        }
};

class TransparentImage : public Image{
    protected:
        bool transparentna;
    public:
        TransparentImage(char * i="untitled", char * s="unknown", int si=800, int vi=800 , bool t=true) : Image(i,s,si,vi){
            transparentna=t;
        }

        int fileSize() const{
            if(transparentna){
                return sirina*visina*4;
            } return sirina * visina + (sirina * visina)/8;
        }
};

class Folder{
    protected:
        char ime[255];
        char sopstvenik[50];
        Image * img[100];
    public:
        Folder(const char * i ="untitled",const char * s ="unknown",  Image **im=0){
            strcpy(ime,i);
            strcpy(sopstvenik,s);
            img[0]=NULL;
        }
        int folderSize(){
            double vk=0;
            for(int i=0;img[i]!=NULL && i<100; i++){
                vk+=img[i]->fileSize();
            }
            return vk;
        }
        Image * getMaxFile(){
            int max=0;
            for(int i=0; img[i]!=NULL && i<100; i++){
                if(img[i]->fileSize()>img[max]->fileSize()){
                    max=i;
                }
            }
            return img[max];
        }
        Folder & operator+=(Image & im){
            int i;
            for(i=0; img[i]!=NULL && i<100; i++);
            img[i]=&im;
            img[i+1]=NULL;
        }
        friend ostream & operator<<(ostream &out, Folder f){
            out<<f.ime<<" "<<f.sopstvenik<<endl<<"--"<<endl;
            for(int i=0; f.img[i]!=NULL && i<100; i++){
                out<<*f.img[i];
            }
            out<<"--"<<endl<<"Folder size: "<<f.folderSize()<<endl;
        }
        Image * operator [](int n){
            if(img[n]){
                return img[n];
            }return NULL;
        }

};

Folder max_folder_size(Folder * fo, int num){
    int max=0;
    for(int i=0; i<num; i++){
        if(fo[i].folderSize()>fo[max].folderSize()){
            max = i;
        }
    }
    return fo[max];
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
