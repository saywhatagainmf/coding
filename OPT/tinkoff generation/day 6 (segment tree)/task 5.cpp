#define int long long
#define F first
#define S second
#define ll long long
#define pb push_back
#define mp make_pair
#define speed                         \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define pii pair<int, int>

const int inf = 1e9;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;

using namespace std;

struct el {
    int sum;
    int add;
};

int n, a[N], k, l, r, add, j;
el t[4 * N];
char command;

void build(int v, int tl, int tr) {
    if (tl == tr) {
        t[v].sum = a[tl];
        t[v].add = 0;
        return;
    }

    int tm = (tl + tr) / 2;
    build(2 * v, tl, tm);
    build(2 * v + 1, tm + 1, tr);
    t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
}

void push(int v, int tl, int tr) {
    if (t[v].add != 0) {
        int x = t[v].add;
        t[v].add = 0;

        int tm = (tl + tr) / 2;
        t[2 * v].add += x;
        t[2 * v].sum += (tm - tl + 1) * x;

        t[2 * v + 1].add += x;
        t[2 * v + 1].sum += (tr - tm) * x;
    }
}

void update(int v, int tl, int tr, int l, int r, int a) {
    if (tl > r || tr < l) return;

    if (l <= tl && tr <= r) {
        t[v].add += a;
        t[v].sum += (tr - tl + 1) * a;
        return;
    }

    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    update(2 * v, tl, tm, l, r, a);
    update(2 * v + 1, tm + 1, tr, l, r, a);
    t[v].sum = t[2 * v].sum + t[2 * v + 1].sum;
}

int get(int v, int tl, int tr, int i) {
    if (tl == tr) return t[v].sum;

    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    if (i <= tm)
        return get(2 * v, tl, tm, i);
    else
        return get(2 * v + 1, tm + 1, tr, i);
}

speed cin >> n;
for (int i = 1; i <= n; i++) cin >> a[i];
build(1, 1, n);

cin >> k;
for (int i = 1; i <= k; i++) {
    cin >> command;
    if (command == 'g') {
        cin >> j;
        cout << get(1, 1, n, j) << endl;
    } else {
        cin >> l >> r >> add;
        update(1, 1, n, l, r, add);
    }
}