#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull mulmod(ull a, ull b, ull m){ return (__int128)a * b % m; }

ull powmod(ull a, ull e, ull m){
    ull r = 1; a %= m;
    while (e) { if (e & 1) r = mulmod(r, a, m); a = mulmod(a, a, m); e >>= 1; }
    return r;
}

bool millerRabin(ull n){
    if (n < 2) return false;
    for (ull p : {2,3,5,7,11,13,17,19,23,29,31,37})
        if (n % p == 0) return n == p;
    ull d = n - 1; int r = 0;
    while (d % 2 == 0) { d /= 2; r++; }
    for (ull a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        ull x = powmod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (int i = 0; i < r - 1; i++) {
            x = mulmod(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

ull pollardRho(ull n){
    if (n % 2 == 0) return 2;
    ull x = rand() % n, y = x, c = rand() % n + 1, d = 1;
    while (d == 1) {
        x = (mulmod(x, x, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        y = (mulmod(y, y, n) + c) % n;
        d = __gcd(x > y ? x - y : y - x, n);
    }
    return d != n ? d : pollardRho(n);
}

void factor(ull n, map<ull,int>& f){
    if (n == 1) return;
    if (millerRabin(n)) { f[n]++; return; }
    ull d = pollardRho(n);
    factor(d, f);
    factor(n / d, f);
}

long long divisorCount(ull n){
    if (n == 1) return 1;
    map<ull,int> f;
    factor(n, f);
    long long res = 1;
    for (auto& pr : f) res *= (pr.second + 1);
    return res;
}

int N;
vector<long long> v;

struct Candidato { bool ok = false; long long X = 0, faltante = 0; };

// Caso A: X ya está en la lista, es el máximo
Candidato casoA(){
    Candidato c;
    long long X = v[N-1];
    int mismatches = 0;
    long long faltanteVal = -1;

    for (int i = 0; i < N; i++) {
        long long a = v[i];
        if (X % a != 0) return c; // a no divide a X -> candidato inválido
        long long pareja = X / a;
        if (!binary_search(v.begin(), v.end(), pareja)) {
            mismatches++;
            faltanteVal = pareja;
            if (mismatches > 1) return c;
        }
    }

    if (mismatches == 0) {
        long long s = (long long) sqrtl((long double) X);
        while (s * s > X) s--;
        while ((s + 1) * (s + 1) <= X) s++;
        if (s * s == X && !binary_search(v.begin(), v.end(), s)) faltanteVal = s;
        else return c; // 0 desemparejados solo tiene sentido si X es cuadrado perfecto
    }

    if (divisorCount((ull) X) != N + 1) return c; // verificación final: nada quedó afuera

    c.ok = true; c.X = X; c.faltante = faltanteVal;
    return c;
}

// Caso B: el que falta es X mismo
Candidato casoB(){
    Candidato c;
    if (N < 2 || v[0] != 1) return c;

    long long p = v[1], M = v[N-1];
    if (!millerRabin((ull) p)) return c; // v[1] tiene que ser primo (menor factor primo real)
    if (p > (long long) 1e18 / M) return c; // guard de overflow
    long long X = p * M;
    if (X > (long long) 1e18) return c;

    for (int i = 0; i < N; i++) {
        long long a = v[i];
        if (X % a != 0) return c;
        if (a == 1) continue; // 1 empareja con X, que es justamente el que falta
        long long pareja = X / a;
        if (!binary_search(v.begin(), v.end(), pareja)) return c;
    }
    if (binary_search(v.begin(), v.end(), X)) return c; // X no puede estar ya en la lista

    if (divisorCount((ull) X) != N + 1) return c;

    c.ok = true; c.X = X; c.faltante = X;
    return c;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    v.resize(N);
    for (auto &x : v) cin >> x;
    sort(v.begin(), v.end());

    Candidato a = casoA();
    Candidato b = casoB();

    vector<pair<long long,long long>> resultados;
    if (a.ok) resultados.push_back({a.X, a.faltante});
    if (b.ok) resultados.push_back({b.X, b.faltante});
    sort(resultados.begin(), resultados.end());
    resultados.erase(unique(resultados.begin(), resultados.end()), resultados.end());

    if (resultados.size() == 1) cout << resultados[0].first << " " << resultados[0].second << "\n";
    else cout << "*\n";

    return 0;
}