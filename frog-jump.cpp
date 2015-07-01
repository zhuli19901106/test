// http://www.1point3acres.com/bbs/thread-137338-1-1.html
/*
6 7 3
1 3 1 4 2 5
*/
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

int findRoot(int a[], int x)
{
    int r = x;
    while (r != a[r]) {
        r = a[r];
    }
    int k = x;
    while (x != r) {
        x = a[x];
        a[k] = r;
        k = x;
    }
    return r;
}

int solution(int A[], int N, int X, int D)
{
    int *dj;
    
    dj = new int[X + 1];
    memset(dj, 0, (X + 1) * sizeof(int));
    
    int i;
    for (i = 0; i <= X; ++i) {
        dj[i] = i;
    }
    
    for (i = 1; i <= D && i <= X; ++i) {
        dj[i] = 0;
    }
    if (findRoot(dj, X) == 0) {
        return 0;
    }
    
    int ll, rr;
    i = 0;
    while (i < N && findRoot(dj, X) != 0) {
        if (findRoot(dj, min(A[i] + D, X)) == findRoot(dj, A[i])) {
			++i;
            continue;
        }
        
        ll = A[i] + 1;
        rr = min(A[i] + D, X);
        
        if (dj[ll] == ll) {
            while (ll <= rr && dj[ll] == ll) {
                dj[ll++] = dj[A[i]];
            }
        } else if (dj[rr] == rr) {
            while (ll <= rr && dj[rr] == rr) {
                dj[rr--] = dj[A[i]];
            }
        } else {
            while (ll <= rr && dj[ll] != ll) {
                ++ll;
            }
            while (ll <= rr && dj[rr] != rr) {
                --rr;
            }
            while (ll <= rr) {
                dj[ll++] = A[i];
            }
        }
        
		if (findRoot(dj, X) == 0) {
			break;
		}
		++i;
    }
    delete[] dj;
    
    return i < N ? i : -1;
}

int main()
{
    const int MAXN = 100005;
    int *A, N, X, D;
    
    A = new int[MAXN];
    scanf("%d%d%d", &N, &X, &D);
    int i;
    for (i = 0; i < N; ++i) {
        scanf("%d", &A[i]);
    }
    printf("%d\n", solution(A, N, X, D));
    delete[] A;
    
    return 0;
}

/*
int main()
{
    const int MAXN = 100005;
	const int M = 100000;
    int *A, N, X, D;
    
    A = new int[MAXN];
	N = M;
	X = M;
	D = M / 2;
    int i;
    for (i = 0; i < N; ++i) {
		A[i] = N - 1 - i;
    }
    printf("%d\n", solution(A, N, X, D));
    delete[] A;
    
    return 0;
}
*/