#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, minX, maxX, minY, maxY, tempX, tempY, base, altura, perimetro;
    cin >> N;
    
    minX = INT_MAX;
    maxX = INT_MIN;
    minY = INT_MAX;
    maxY = INT_MIN;

    for (int i = 0; i < N; i++) {
        cin >> tempX >> tempY;
        minX = min(minX,tempX);
        maxX = max(maxX,tempX);
        minY = min(minY,tempY);
        maxY = max(maxY, tempY);
    }

    base = maxX - minX + 2;;
    altura = maxY - minY + 2;
    perimetro = 2 * (base + altura);

    cout << perimetro;
}