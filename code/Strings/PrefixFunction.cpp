//p[i] = longest proper prefix/sufix of prefix i
for(int i = 2; i <= n; i++) { //prefix function al patron
    while(k > 0 && A[k + 1] != A[i])
        k = P[k];

    if(A[k + 1] == A[i])
        k++;

    P[i] = k;
}

k = 0;
for(int i = 1; i <= m; i++) {
    while(k > 0 && A[k + 1] != B[i])
        k = P[k];

    if(A[k + 1] == B[i])
        k++;

    if(k == n) {
        sol++;
        k = P[k];
    }
}
