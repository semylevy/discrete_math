//Proyecto final de mates discretas
//Salomon Levy, Salomon Charabati, Benny Stern.

#include <iostream>
#include <vector>

using namespace std;

void imprime(vector<char> arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
}

vector<char> interseccion (vector<char> arr1, vector<char> arr2) {
    vector<char> res;
    vector<char>::iterator it;
    for(it = arr1.begin(); it != arr1.end(); ++it) {
        vector<char>::iterator it2;
        for(it2 = arr2.begin(); it2 != arr2.end(); ++it2) {
            if(*it == *it2) {
                res.push_back(*it);
            }
        }
    }
    return res;
}

int main() {
    vector<char> a;
    vector<char> b;
    vector<char> res;
    
    a.push_back('a');
    a.push_back('b');
    a.push_back('c');
    
    b.push_back('b');
    
    res = interseccion(a,b);
    
    imprime(res);
    
    return 0;
}
