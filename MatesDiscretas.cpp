#include <iostream>
#include <vector>

using namespace std;

int bienvenida();
void pideConjunto(vector<char> &universo, string tipo);
void imprimeConjunto(vector<char> res, int t);
void mensajeError(int index);
int menuDeOpciones(vector<char> a, vector<char> b, vector<char> u, vector<char> &res);
void revisaConjunto(vector<char> universo, vector<char> &conjunto, string tipo);
void interseccion (vector<char> a, vector<char> b, vector<char> &res);
void unionFn (vector<char> a, vector<char> b, vector<char> &res);
void complemento (vector<char> vec, vector<char> universo, vector<char> &res);
void diferencia (vector<char> vec1, vector<char> vec2, vector<char> &res);
void potencia(vector<char> vec, vector<char> &res);
vector<int> convertBinary(int num);

int main() {
    vector<char> u, a, b, res, vacio;
    
    int seleccion1, seleccion2;
    
    seleccion1 = bienvenida();
    
    while(seleccion1 == 1) {
        pideConjunto(u, "universo");
        pideConjunto(a, "A");
        revisaConjunto(u, a, "A");
        pideConjunto(b, "B");
        revisaConjunto(u, b, "B");

        while(seleccion2 != -1) {
            seleccion2 = menuDeOpciones(a, b, u, res);
            if(seleccion2 != -1)
                imprimeConjunto(res, seleccion2);
            res = vacio;
        }
        
        seleccion1 = bienvenida();
        seleccion2 = 1;
        
        u = vacio;
        a = vacio;
        b = vacio;
        res = vacio;
    }
    
    return 0;
}


int bienvenida() {
    int seleccion;
    do {
        cout << "1. Introducir nuevos conjuntos" << endl << "2. Terminar" << endl;
        cin >> seleccion;
    } while (seleccion != 1 && seleccion != 2 && cout << "ERROR - Selecciona una opción válida" << endl);
    return seleccion;
}

void pideConjunto(vector<char> &conjunto, string tipo) {
    cout << "Introduce conjunto " << tipo << ", valores separados por espacios" << endl;
    char temp;
    do {
        cin >> temp;
        conjunto.push_back(temp);
    } while(cin.get() != '\n');
}

void imprimeConjunto(vector<char> v, int t) {
    string tipo;
    switch (t) {
        case 1:
            tipo = "intersección";
            break;
        case 2:
            tipo = "unión";
            break;
        case 3:
            tipo = "complemento";
            break;
        case 4:
            tipo = "diferencia";
            break;
        case 5:
            tipo = "potencia";
            break;
    }
    cout << "Conjunto " << tipo << endl << "{ ";
    for(vector<char>::iterator it = v.begin() ; it != v.end(); ++it){
        cout << *it << " ";
    }
    cout << "}" << endl;
}


void revisaConjunto(vector<char> universo, vector<char> &conjunto, string tipo) {
    int contador = 0;
    vector<char> vacio;
    vector<char>::iterator it;
    for(it = conjunto.begin(); it != conjunto.end(); ++it) {
        vector<char>::iterator it2;
        for(it2 = universo.begin(); it2 != universo.end(); ++it2) {
            if(*it == *it2) {
                contador++;
            }
        }
        if(contador == 0) {
            mensajeError(1);
            conjunto = vacio;
            pideConjunto(conjunto, tipo);
            revisaConjunto(universo, conjunto, tipo);
            return;
        } else {
            contador = 0;
        }
    }
}

void mensajeError(int index) {
    if(index == 1) {
        cout << "ERROR - el universo debe contener todos los elementos del conjunto" << endl << "Vuelva a ingresarlo" << endl;
    }
}

void interseccion (vector<char> a, vector<char> b, vector<char> &res) {
    vector<char>::iterator it;
    for(it = a.begin(); it != a.end(); ++it) {
        vector<char>::iterator it2;
        for(it2 = b.begin(); it2 != b.end(); ++it2) {
            if(*it == *it2) {
                res.push_back(*it);
            }
        }
    }
}

void unionFn (vector<char> a, vector<char> b, vector<char> &res) {
    res.insert(res.end(), a.begin(), a.end());
    res.insert(res.end(), b.begin(), b.end());
    
    for(int i = 0; i < res.size(); i++) {
        for(int j = i+1; j < res.size(); j++) {
            if(res[i] == res[j]) {
                res.erase(res.begin() + j);
            }
        }
    }
}

void complemento (vector<char> vec, vector<char> universo, vector<char> &res) {
    res.insert(res.end(), universo.begin(), universo.end());
    
    for(int i = 0; i < vec.size(); i++) {
        for(int j = 0; j < res.size(); j++) {
            if(vec[i] == res[j]) {
                res.erase(res.begin() + j);
            }
        }
    }
    
}

void diferencia (vector<char> vec1, vector<char> vec2, vector<char> &res) {
    res.insert(res.end(), vec1.begin(), vec1.end());
    
    for(int i = 0; i < vec2.size(); i++) {
        for(int j = 0; j < vec1.size(); j++) {
            if(vec2[i] == vec1[j]) {
                res.erase(res.begin() + j);
            }
        }
    }
    
}

void potencia(vector<char> vec, vector<char> &res) {
    int combinaciones = 2;
    vector<int> binario;
    for(int i = 1; i < vec.size(); i++) {
        combinaciones = combinaciones*2;
    }
    for(int i = 0; i < combinaciones; i++) {
        binario = convertBinary(i);
        res.push_back('{');
        for(int j = binario.size()-1; j >= 0; j--){
            if(binario[j] == 1) {
                if(binario.size() == 1) {
                    res.push_back(vec[vec.size()-1]);
                } else {
                    res.push_back(vec[j]);
                }
            }
        }
        res.push_back('}');
    }
}

vector<int> convertBinary(int num) {
    vector<int> res;
    int contador = 0;
    int temp = num;
    while(true){
        res.push_back(temp%2);
        temp /=2;
        if(temp==0) break;
    }
    return res;
}

int menuDeOpciones(vector<char> a, vector<char> b, vector<char> u, vector<char> &res) {
    int seleccionOpcion, seleccionOpcion2;
    cout << "¿Que operación deseas hacer? (1-6)" << endl;
    do {
        cout << "1.Intersección A ∩ B. \n2.Unión A ∪ B.\n3.Complemento\n4.Diferencia.\n5.Potencia.\n6.Salir" << endl;
        cin >> seleccionOpcion;
        switch(seleccionOpcion){
            case 1:
                interseccion(a, b, res);
                return 1;
            case 2:
                unionFn(a, b, res);
                return 2;
            case 3:
                do {
                    cout << "1. Complemento A" << endl << "2. Complemento B"<< endl;
                    cin >> seleccionOpcion2;
                    if(seleccionOpcion2 == 1) {
                        complemento(a, u, res);
                    } else if (seleccionOpcion2 == 2){
                        complemento(b, u, res);
                    }
                } while(seleccionOpcion2 != 1 && seleccionOpcion2 != 2 && cout << "ERROR - Selecciona una opción válida" << endl);
                return 3;
            case 4:
                do {
                    cout << "1. Diferencia A-B" << endl << "2. Diferencia B-A"<< endl;
                    cin >> seleccionOpcion2;
                    if(seleccionOpcion2 == 1) {
                        diferencia(a, b, res);
                    } else if (seleccionOpcion2 == 2){
                        diferencia(b, a, res);
                    }
                } while(seleccionOpcion2 != 1 && seleccionOpcion2 != 2 && cout << "ERROR - Selecciona una opción válida" << endl);
                return 4;
            case 5:
                do {
                    cout << "1. Potencia A" << endl << "2. Potencia B"<< endl;
                    cin >> seleccionOpcion2;
                    if(seleccionOpcion2 == 1) {
                        potencia(a, res);
                    } else if (seleccionOpcion2 == 2){
                        potencia(b, res);
                    }
                } while(seleccionOpcion2 != 1 && seleccionOpcion2 != 2 && cout << "ERROR - Selecciona una opción válida" << endl);
                return 5;
            case 6:
                return -1;
                break;
        }
    } while ((seleccionOpcion > 6 || seleccionOpcion <= 0) && cout << "ERROR - Selecciona una opción válida" << endl);
    return 1;
}
