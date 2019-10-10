//Mo's Algorithm
struct Query
{
    int st, ed, id;
}qry[Q];

bool cmp(Query a, Query b)
{
    if(a.st/bs != b.st/bs) return a.st/bs < b.st/bs;
    return a.ed < b.ed;
}

void perform(int x0)	//t actual
{
    int aux = arr[inv[x0]];	//valor actual
    pty[inv[x0]] ^= 1;		//paridad

    if(pty[inv[x0]])		//paridad = 1, caso: insertar
    {
        ++fq[aux];
        if(fq[aux] == 1) ++tot;
    }
    else 					//paridad = 0, caso: remover
    {
        --fq[aux];
        if(fq[aux] == 0) --tot;
    }
}

/*
En el Euler Tour del arbol hay que poner en dt[u] = ++t y en ft[u] = ++t,
asi como inv[t] = u en ambos casos.
Cuando se anade una query hay que cambiar u con v si dt[u] > dt[v],
luego actualizar pend[i] = arr[l], si l no conicide con u
*/

for(int i = 1; i <= q; ++i)
{
	int u, v; scanf("%d %d", &u, &v);
	if(dt[u] > dt[v]) swap(u, v);

	int l = lca(u, v);
	if(l == u)	// caso: l -> u
	{
		qry[i].st = dt[u];	//incio
		qry[i].ed = dt[v];	//fin
	}
	else 	//caso: u -> l -> v
	{
		qry[i].st = ft[u];	//inicio
		qry[i].ed = dt[v];	//fin
		pend[i] = arr[l];	//hay que anadir l porque no esta en [ft[u],dt[v]]
	}

	qry[i].id = i;	//para responder en orden
}

bs = sqrt(2*n);
sort(qry + 1, qry + q + 1, cmp);

int curL = 1, curR = 0;	//intervalo vacio de t
for(int i = 1; i <= q; ++i)
{
	int l = qry[i].st;
	int r = qry[i].ed;
	int id = qry[i].id;

	while(curL > l) perform(--curL);
	while(curR < r) perform(++curR);

	while(curL < l) perform(curL++);
	while(curR > r) perform(curR--);

	ans[id] = tot;
	if(pend[id]) ans[id] += (fq[pend[id]] == 0);	//caso LCA no coincide con u
}
