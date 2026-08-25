#include <bits/stdc++.h>
using namespace std;

int N, M;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;    
    vector<int> oros(N+1,0); //para inicializarlo con todos 0, si usaba array estaria con basura pq su tamaño es variable
    int opciones[N+1]; //dejo el arreglo pq no me importa que este inicializado con basura, total voy a estar pisando valores (no sumandole a los viejos)

    for (int i = 0; i < M; i++) {
        int xTemp, yTemp, cantOp1, oroOp1;
        cin >> xTemp >> yTemp;
        // por defecto ines toma la opcion1
        cantOp1 = 1;  
        opciones[N] = 1;

        for (int j = 0; j < N; j++) {
            cin >> opciones[j];

            if (opciones[j] == 1) {
                cantOp1++;
            }
        }

        oroOp1 = xTemp / cantOp1;
        if (oroOp1 < yTemp) {
            // ines no elige la opcion 1
            opciones[N] = 2;

            // alguien ademas de ines elige esa opcion
            if (cantOp1 > 1) {
                cantOp1--;
                oroOp1 = xTemp / cantOp1;
            }
        } 

        for (int j = 0; j < N+1; j++) {
            if (opciones[j] == 1) {
                oros[j] += oroOp1;
            } else {
                oros[j] += yTemp;
            }
        }
    }

    // imprimir
    for (int i = 0; i < N+1; i++) {
        cout << oros[i] << " ";
    }
    cout << "\n";

    return 0;
}