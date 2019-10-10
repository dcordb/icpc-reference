//Steiner Tree DP O(n * 3 ** T + 2 ** T * n * n)

/*

DP(i, mask) = minimo steiner forest con raiz en el nodo i y mascara de terminales mask


Respuesta en DP(i, 1 << T - 1) para todo i
*/

int F(int i, int mask) {
    int &ans = dp[i][mask]; //ojo importante la referencia

    if(ans != -1)
        return ans;

    if(i < IMP && mask == (1 << i)) //caso base
        return ans = cost[i][i];

    if(mask == 0) //caso base
        return ans = cost[i][i];

    ans = INF;
    for(int s = (mask - 1) & mask; s > 0; s = (s - 1) & mask) { //submascara de mask
        int res = F(i, s) + F(i, mask - s); //transicion 1

        if(res < ans) {
            ans = res;
            typeT[i][mask] = 1; //esto es para recuperar
            got[i][mask] = s;
        }
    }

    for(int j = 0; j < l; j++) { //por cada nodo (incluyendo terminales y no terminales)
        if(i == j)
            continue;

        int res = F(j, mask) + cost[i][j]; //transicion 2

        if(res < ans) {
            ans = res;
            typeT[i][mask] = 2; //esto es para recuperar
            got[i][mask] = j;
        }
    }

    return ans;
}