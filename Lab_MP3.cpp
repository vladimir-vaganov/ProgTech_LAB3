#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <time.h>
#include <locale.h>
#include <chrono>
#include <map>
#include <set>

using namespace std;

unsigned int hash1(string key){
    unsigned int ans = 1;
    for (int i = 0; i < key.size(); i++)
        ans *= (key[i] - 'a');

    return ans;
}

unsigned int hash2(string key){
    unsigned int ans = 0;

    for (int i = 0; i < key.size(); i++)
        ans = 37 * ans + (key[i] - 'a');

    return ans;
}

class Prepod{
public:
    Prepod();
    Prepod(ifstream& in);
    ~Prepod();

    string getFname() const;
    string getLname() const;
    string getMname() const;
    string getFaculty() const;
    string getAdegree() const;
    string getAtitle() const;
    unsigned int getHash1() const;
    unsigned int getHash2() const;

    Prepod& operator= (const Prepod& A);
    friend ostream& operator<< (ostream& out, const Prepod& A);

private:
    string fname, lname, mname, faculty, adegree, atitle;
    unsigned int hash_1, hash_2;
};

Prepod::Prepod(){
    fname = "";
    lname = "";
    mname = "";
    faculty = "";
    adegree = "";
    atitle = "";
    hash_1 = 0;
    hash_2 = 0;
}

Prepod::Prepod(ifstream& in){
    in >> fname >> lname >> mname >> faculty >> adegree >> atitle;
    hash_1 = hash1(fname);
    hash_2 = hash2(fname);
}

Prepod::~Prepod(){

}

string Prepod::getFname() const {
    return fname;
}

string Prepod::getLname() const {
    return lname;
}

string Prepod::getMname() const {
    return mname;
}

string Prepod::getFaculty() const {
    return faculty;
}

string Prepod::getAdegree() const {
    return adegree;
}

string Prepod::getAtitle() const {
    return atitle;
}

unsigned int Prepod::getHash1() const{
    return hash_1;
}

unsigned int Prepod::getHash2() const{
    return hash_2;
}

Prepod& Prepod::operator= (const Prepod& A){
    fname = A.getFname();
    lname = A.getLname();
    mname = A.getMname();
    faculty = A.getFaculty();
    adegree = A.getAdegree();
    atitle = A.getAtitle();
    hash_1 = A.getHash1();
    hash_2 = A.getHash2();

    return *this;
}

ostream& operator<< (ostream& out, const Prepod& A){
    out << A.fname << " ";
    out << A.lname << " ";
    out << A.mname << " ";
    out << A.faculty << " ";
    out << A.adegree << " ";
    out << A.atitle << " ";
    out << endl;

    return out;
}

bool operator== (const Prepod& A, const Prepod& B){
    return ((A.getFname() == B.getFname()) &&
            (A.getLname() == B.getLname()) &&
            (A.getMname() == B.getMname()) &&
            (A.getFaculty() == B.getFaculty()) &&
            (A.getAdegree() == B.getAdegree()) &&
            (A.getAtitle() == B.getAtitle()));
}

bool operator!= (const Prepod& A, const Prepod& B){
    return !(A == B);
}

bool operator> (const Prepod& A, const Prepod& B){
    if (A == B)
        return false;

    if (A.getFname() != B.getFname())
        return (A.getFname() > B.getFname());

    if (A.getFaculty() != B.getFaculty())
        return (A.getFaculty() > B.getFaculty());

    if (A.getLname() != B.getLname())
        return (A.getLname() > B.getLname());

    if (A.getMname() != B.getMname())
        return (A.getMname() > B.getMname());

    if (A.getAdegree() != B.getAdegree())
        return (A.getAdegree() > B.getAdegree());

    if (A.getAtitle() != B.getAtitle())
        return (A.getAtitle() > B.getAtitle());

    return false;
}

bool operator< (const Prepod& A, const Prepod& B){
    return (A != B && !(A > B));
}

bool operator >= (const Prepod& A, const Prepod& B){
    return (A == B || A > B);
}

bool operator <= (const Prepod& A, const Prepod& B){
    return (A == B || A < B);
}

template <typename T>
void bubbleSort(T* A, size_t n){
    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (A[j] > A[j + 1])
                swap(A[j], A[j + 1]);
}

template <typename T>
void quickSort(T* A, size_t n) {
    int i = 0, j = n - 1;
    T mid = A[n / 2];

    do {
        while(A[i] < mid)
            i++;

        while(A[j] > mid)
            j--;

        if (i <= j) {
            swap(A[i], A[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if(j > 0)
        quickSort(A, j + 1);
    if (i < n)
        quickSort(&A[i], n - i);

    return;
}

template <typename T>
void mergeSort(T* A, size_t n){
    if (n == 1)
        return;

    mergeSort(A, n / 2);
    mergeSort(&A[n / 2], n - n / 2);

    size_t i = 0, j = n / 2, k = 0;

    T* tmp = new Prepod[n];

    while(k < n){
        if (i == n / 2){
            tmp[k] = A[j];
            j++;
        }
        else
        if (j == n){
            tmp[k] = A[i];
            i++;
        }
        else
        if (A[i] < A[j]){
            tmp[k] = A[i];
            i++;
        }
        else
        {
            tmp[k] = A[j];
            j++;
        }
        k++;
    }

    for (size_t i = 0; i < n; i++)
        A[i] = tmp[i];
}

template <typename T>
int linearSearch(T* A, size_t n, string keyName){
    for (size_t i = 0; i < n; i++)
        if (A[i].getFname() == keyName)
            return i;
    return -1;
}

template <typename T>
int binarySearch(T* A, size_t n, string keyName){

    size_t left = 0, right = n, mid;

    while (left <= right){
        mid = (left + right) / 2;

        if (A[mid].getFname() == keyName)
            return mid;
        if (A[mid].getFname() > keyName)
            right = mid - 1;
        else
            left = mid + 1;
    }

    return -1;
}

Prepod *data100 = new Prepod[100],
       *data500 = new Prepod[500],
       *data1000 = new Prepod[1000],
       *data5000 = new Prepod[5000],
       *data10000 = new Prepod[10000],
       *data50000 = new Prepod[50000],
       *data100000 = new Prepod[100000];

void readData(){
    ifstream in100("100.txt");

    if (in100.is_open())
        for (size_t i = 0; i < 100; i++)
            data100[i] = Prepod(in100);
    in100.close();


    ifstream in500("500.txt");
    if (in500.is_open())
        for (size_t i = 0; i < 500; i++)
            data500[i] = Prepod(in500);
    in500.close();

    ifstream in1000("1000.txt");
    if (in1000.is_open())
        for (size_t i = 0; i < 1000; i++)
            data1000[i] = Prepod(in1000);
    in1000.close();

    ifstream in5000("5000.txt");
    if (in5000.is_open())
        for (size_t i = 0; i < 5000; i++)
            data5000[i] = Prepod(in5000);
    in5000.close();

    ifstream in10000("10000.txt");
    if (in10000.is_open())
        for (size_t i = 0; i < 10000; i++)
            data10000[i] = Prepod(in10000);
    in10000.close();

    ifstream in50000("50000.txt");
    if (in50000.is_open())
        for (size_t i = 0; i < 50000; i++)
            data50000[i] = Prepod(in50000);
    in50000.close();

    ifstream in100000("100000.txt");
    if (in100000.is_open())
        for (size_t i = 0; i < 100000; i++)
            data100000[i] = Prepod(in100000);
    in100000.close();
}

class HashTable1{
public:
    Prepod** table;
    unsigned int sizes[20000] = {0};

    HashTable1(){

    }

    HashTable1(Prepod* data, size_t n){
        int counter = 0;

        table = new Prepod* [20000];

        cout << "Creating hash table from data with value of " << n << endl;

        for (size_t i = 0; i < 20000; i++)
            table[i] = nullptr;

        for (size_t i = 0; i < n; i++){
            unsigned int hash = hash1(data[i].getFname());
            if (table[hash] == nullptr){
                table[hash] = new Prepod [1];
                table[hash][0] = data[i];
                sizes[hash] = 1;
            }
            else
            {
                counter++;
                unsigned int old_n = sizes[hash];
                Prepod* tmp = new Prepod [old_n + 1];
                for (size_t j = 0; j < old_n; j++)
                    tmp[j] = table[hash][j];
                tmp[old_n] = data[i];
                table[hash] = tmp;
                sizes[hash]++;
            }
        }

        cout << counter << " collisions" << endl;
    }
};

class HashTable2{
public:
    Prepod** table;
    unsigned int sizes[40000] = {0};

    HashTable2(){

    }

    HashTable2(Prepod* data, size_t n){
        int counter = 0;

        table = new Prepod* [40000];

        cout << "Creating hash table from data with value of " << n << endl;

        for (size_t i = 0; i < 40000; i++)
            table[i] = nullptr;

        for (size_t i = 0; i < n; i++){
            unsigned int hash = hash2(data[i].getFname());
            if (table[hash] == nullptr){
                table[hash] = new Prepod [1];
                table[hash][0] = data[i];
                sizes[hash] = 1;
            }
            else
            {
                counter++;
                unsigned int old_n = sizes[hash];
                Prepod* tmp = new Prepod [old_n + 1];
                for (size_t j = 0; j < old_n; j++)
                    tmp[j] = table[hash][j];
                tmp[old_n] = data[i];
                table[hash] = tmp;
                sizes[hash]++;
            }
        }

        cout << counter << " collisions" << endl;
    }
};

Prepod findWithHashTable(HashTable1 hashTable, string key){
    unsigned int hash = hash1(key);

    if (hashTable.table[hash] == nullptr)
        return Prepod();
    else
    {
        for (int i = 0; i < hashTable.sizes[hash]; i++)
            if (hashTable.table[hash][i].getFname() == key)
                return hashTable.table[hash][i];
        return Prepod();
    }
}

Prepod findWithHashTable(HashTable2 hashTable, string key){
    unsigned int hash = hash2(key);

    if (hashTable.table[hash] == nullptr)
        return Prepod();
    else
    {
        for (int i = 0; i < hashTable.sizes[hash]; i++)
            if (hashTable.table[hash][i].getFname() == key)
                return hashTable.table[hash][i];
        return Prepod();
    }
}


int main(){
    setlocale(LC_ALL, "Russian");

    readData();

    cout << "Data has read" << endl;

    int choice;

    cout << "Which hash-function you'll test:\n\n1. Simple\n2. Hard\n\n";
    cin >> choice;
    cout << endl << endl;
    if (choice == 1){
        HashTable1 ht100(data100, 100),
                   ht500(data500, 500),
                   ht1000(data1000, 1000),
                   ht5000(data5000, 5000),
                   ht10000(data10000, 10000),
                   ht50000(data50000, 50000),
                   ht100000(data100000, 100000);




        cout << "Data sampling with a volume of 100:\t";
        auto start_t = chrono::steady_clock::now();
        auto tmp = findWithHashTable(ht100, "fmw");
        auto end_t = chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 500:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht500, "byu");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 1000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht1000, "lga");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 5000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht5000, "ocy");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 10000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht10000, "wmc");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 50000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht50000, "thl");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 100000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht100000, "ntx");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

    }
    if (choice == 2){
        HashTable2 ht100(data100, 100),
                   ht500(data500, 500),
                   ht1000(data1000, 1000),
                   ht5000(data5000, 5000),
                   ht10000(data10000, 10000),
                   ht50000(data50000, 50000),
                   ht100000(data100000, 100000);




        cout << "Data sampling with a volume of 100:\t";
        auto start_t = chrono::steady_clock::now();
        auto tmp = findWithHashTable(ht100, "fmw");
        auto end_t = chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 500:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht500, "byu");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 1000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht1000, "lga");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 5000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht5000, "ocy");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 10000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht10000, "wmc");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 50000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht50000, "thl");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

        cout << "Data sampling with a volume of 100000:\t";
        start_t = chrono::steady_clock::now();
        tmp = findWithHashTable(ht100000, "ntx");
        end_t = chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_t - start_t);
        cout << elapsed_ms.count() << " nanoseconds\n";

    }
}


