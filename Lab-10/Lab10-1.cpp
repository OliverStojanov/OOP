#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

class Exception{
    private:
        int num{0};
    public:
        Exception(int n){
            this->num = n;
        }
        void error(){
            cout<<num<<" out of bounds"<<endl;
        }
};

template <typename T>
class Array{
    private:
        T *arr{nullptr};
        int num{0};
    public:
        Array(){}
        Array(int n){
            num = n;
            arr = new T[n];
        }
        ~Array(){}

        T &operator[](int i){
            if(i<0 || i>num){
                throw Exception(i);
            }
            return arr[i];
        }

        friend ostream &operator<<(ostream &out, Array &other){
            out<<"Array[0] = "<<other.arr[0];
            for(int i=1; i<other.num; i++){
                out<<", Array["<<i<<"] = "<<other.arr[i];
            }
            out<<endl;
            return out;
        }

        void Erase(){
            delete[] arr;
            arr = new T[0];
            num = 0;
        }
        int getNum(){
            return num;
        }
};

template <typename T>
void BubbleSort(Array<T> &other){
    for(int i=0; i<other.getNum()-1; i++){
        for(int j=0; j<other.getNum()-1; j++){
            if(other[j] > other[j+1]){
                T temp;
                temp = other[j];
                other[j] = other[j + 1];
                other[j + 1] = temp;
            }
        }
    }
}

template <typename T>
T Sum(Array<T> &other){
    T sum = 0;
    for(int i=0; i<other.getNum(); i++){
        sum += other[i];
    }
    return sum;
}

template <typename T>
T Average(Array<T> &other){
    return Sum(other) / other.getNum();
}

template <typename T, typename M>
bool Equal(Array<T> &other, Array<M> &otherTwo){
    if(other.getNum() != otherTwo.getNum()){
        return false;
    }
    for(int i=0; i<other.getNum(); i++){
        if(other[i] != otherTwo[i]){
            return false;
        }
    }
    return true;
}

template <typename T>
bool Equal(Array<T> &other, Array<double> &otherTwo){
    if(other.getNum() != otherTwo.getNum()){
        return false;
    }
    for(int i=0; i<other.getNum(); i++){
        if(abs(other[i] - otherTwo[i]) > 0.1){
            return false;
        }
    }
    if(abs(Average(other) - Average(otherTwo) > 0.5)){
        return false;
    }
    return true;
}





int main()
{

  int n;
  double r;

  cin>>r;
  cin>>n;

  Array<int> anArray(n);
  Array<double> adArray(n);
  Array<int> intArray2(n);

  for (int nCount = 0; nCount < n; nCount++)
  {

      cin>>anArray[nCount];
      adArray[nCount] = anArray[nCount] + r;
  }

  BubbleSort(anArray);

  intArray2 = anArray;

  cout<<"The arrays: "<<endl;
  cout<<anArray;
  cout<<"and "<<endl;
  cout<<intArray2;
  cout<<((Equal(anArray,intArray2))?" ARE":" ARE NOT")<<" same!"<<endl;
  cout<<"The Average of the array adArray is: "<<Average(adArray)<<endl;

  cout<<"The arrays: "<<endl;
  cout<<anArray;
  cout<<"and "<<endl;
  cout<<adArray;
  cout<<((Equal(anArray,adArray))?" ARE":" ARE NOT")<<" same!";


return 0;
}
