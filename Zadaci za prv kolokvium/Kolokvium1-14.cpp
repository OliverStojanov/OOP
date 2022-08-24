#include<iostream>
#include<cstring>

using namespace std;
enum Extension{txt,pdf,exe};

class File{
    private:
        char *ime, *imeSopstvenik;
        Extension ext;
        int golDat;
    public:
        File(char *i="",char *s="", int gd=0, Extension e=(Extension)-1){
            ime=new char[strlen(i)+1];
            imeSopstvenik= new char[strlen(s)+1];
            strcpy(ime,i);
            strcpy(imeSopstvenik,s);
            golDat=gd;
            ext=e;
        }
        File(const File & f){
            ime=new char[strlen(f.ime)+1];
            imeSopstvenik= new char[strlen(f.imeSopstvenik)+1];
            strcpy(ime,f.ime);
            strcpy(imeSopstvenik,f.imeSopstvenik);
            golDat=f.golDat;
            ext=f.ext;
        }
        ~File(){
            delete [] ime;
            delete [] imeSopstvenik;
        }
        File & operator=(const File & f){
            if(this!=&f){
                delete [] ime;
                delete [] imeSopstvenik;
                ime=new char[strlen(f.ime)+1];
                imeSopstvenik= new char[strlen(f.imeSopstvenik)+1];
                strcpy(ime,f.ime);
                strcpy(imeSopstvenik,f.imeSopstvenik);
                golDat=f.golDat;
                ext=f.ext;
                return *this;
            }

        }
        void print(){
            char *ek[]={"pdf", "txt", "exe"};
            cout<<"File name: "<<ime<<"."<<ek[ext]<<endl;
            cout<<"File owner: "<<imeSopstvenik<<endl;
            cout<<"File size: "<<golDat<<endl;
        }
        bool equals(const File & that) {
            if(!strcmp(ime,that.ime) && !strcmp(imeSopstvenik,that.imeSopstvenik) && ext==that.ext){
                return true;
            }
            else return false;
        }
        bool equalsType(const File & that){
            if(!strcmp(ime,that.ime) && ext==that.ext){
                return true;
            }
            else return false;
        }
};
class Folder{
    private:
        char * imeDirektorium;
        int brDat;
        File *file;
    public:
        Folder(const char* name){
            imeDirektorium= new char[strlen(name)+1];
            strcpy(imeDirektorium,name);
            brDat=0;
            file=new File[0];
        }
        ~Folder(){
            delete [] imeDirektorium;
            delete [] file;
        }
        void print(){
            cout << "Folder name: " << imeDirektorium << endl;
            for(int i = 0; i < brDat; i++){
                file[i].print();
            }
        }
        void remove(const File & dat){
            for(int i=0; i<brDat; i++){
                if(file[i].equals(dat)){
                    for(int j=i; j<brDat-1; j++){
                        file[j]=file[j+1];
                    }
                    brDat--;

                }
            }
        }
         void add(const File & dat){
             File *tmp= new File[brDat+1];
             for(int i=0; i<brDat; i++){
                 tmp[i]=file[i];
             }
             delete [] file;
             file=tmp;
             file[brDat]=dat;
             brDat++;
        }
};

int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}
