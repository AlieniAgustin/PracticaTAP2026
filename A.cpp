#include <bits/stdc++.h>
using namespace std;

int main() {
    // Optimizacion de entrada/salida (Fast I/O)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool estaT = false, estaA = false, estaP = false;
    string palabra;

    // Lectura directa
    cin >> palabra; 

    for(int i = 0; i < palabra.size(); i++) {
        if (palabra[i] == 'T') {
            estaT = true;
        } else if (estaT && palabra[i] == 'A') {
            estaA = true;
        } else if (estaA && palabra[i] == 'P') {
            estaP = true;
        }
    }

    // Salida
    if (estaP) {
        cout << "S\n";
    } else {
        cout << "N\n";
    }

    return 0;
}