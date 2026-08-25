#include <bits/stdc++.h>
using namespace std;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, B, C, vuelto;
    cin >> A >> B >> C;
    vuelto = B - A;

    if (vuelto % C == 0) {
        cout << "S\n";
    } else {
        cout << "N\n";
    }

    return 0;
}