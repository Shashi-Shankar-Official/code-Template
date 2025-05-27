#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#ifndef ONLINE_JUDGE
#define deb2(x,y) cerr<<#x<<"="<<x<<", "<<#y<<"="<<y<<endl;
#define deb(x) cout<<#x<<"="<<x<<endl;
#else
#define deb(x);
#define deb2(x,y)
#endif

#define fo(i,n) for(i=0;i<n;i++)
#define rfo(i,k,n) for(i=k;k<n? i<n: i>n; k<n? i++;i--)
#define si(x) scanf("%d", &x);
#define sl(x) scanf("%lld", &x);
#define ss(x) scanf("%s", &x);
#define pi(x) printf("%d\n", x);
#define pl(x) printf("%lld\n", x);
#define ps(x) printf("%s\n", x);
#define p_b push_back
#define m_p make_pair
#define fir first
#define sec second
#define full(x) x.begin(),x.end()
#define line cout<<"\n";
#define tr(it, a) for(auto it = a.begin(); it != a.end(); it++)
#define srt(x) sort(full(x));
typedef pair<int, int> pii;
typedef pair<ll, ll> pll ;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vll;
typedef vector<vector<int> > vii;
const int mod = 1000000007;
const int N=3e5, M=N;
int mpow(int base, int exp);
void ipgraph(int n, int m);
void dfs(int u, int par);
vi g[N];
int a[N];

/*------------------------------------------------------------------------------------*/
/*---------------------- Code starts here --------------------------------------------*/
/*------------------------------------------------------------------------------------*/

class SGTree {
    public:
    vector<int> seg;
    SGTree(int n) {
        seg.resize(4*n+1);
    }

    void build(int ind, int low, int high, int arr[]) {
        if(low == high) {
            seg[ind]=arr[low];
            deb2(ind,seg[ind]);
            return;
        }

        int  mid = (low+high)/2;
        build(2*ind+1,low,mid,arr);
        build(2*ind+2, mid+1, high, arr);
        seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
        deb2(ind,seg[ind]);
    }

    int query(int ind, int low, int high, int l, int r) {
        if(r<low || high <l) return INT_MAX;

        if(low >= l && high <= r) return seg[ind];

        int mid = (low+high)/2;
        int left = query(2*ind+1, low,mid,l,r);
        int right = query(2*ind+2, mid+1,high,l,r);
        return min(left,right);
    }

    void update(int ind, int low, int high, int i, int val) {
        if(low== high) {
            seg[ind]=val;
            return;
        }
        int mid= (low+high)/2;
        if(i<= mid) update(2*ind+1, low, mid, i,val);
        else update(2*ind+2, mid+1, high, i, val);
        seg[ind]=min(seg[2*ind+1], seg[2*ind+2]);
    }

    void print() {
        cout<<"hello printing the build array: "<<endl;
        for(int i=0;i<seg.size();i++) {
            cout<<seg[i]<<" ";
        }
        cout<<endl;
    }
};

/*-------------------------------------------------------------------------------------*/
/*------------------ Segment Tree Portion Ends Here -----------------------------------*/
/*-------------------------------------------------------------------------------------*/

void build(int ind, int low, int high, int arr[],int seg[], int ora) {
    if(low == high) {
        seg[ind]= arr[low];
        return;
    }

    int mid=(low+high)/2;
    build(2*ind+1, low,mid,arr,seg, !ora);
    build(2*ind+2,mid+1,high,arr,seg,!ora);
    if(ora) seg[ind]=seg[2*ind+1] | seg[2*ind+2];
    else seg[ind]=seg[2*ind+1] ^ seg[2*ind+2];
}

void update(int ind, int low,int high, int seg[],int orr, int i, int val) {
    if(low == high) {
        seg[ind]= val;
        return;
    }
    int mid= (low+high)/2;
    if(i<=mid) update(2*ind+1,low,mid,seg,!orr,i,val);
    else update(2*ind+2,mid+1,high,seg,!orr,i,val);
    if(orr) seg[ind]=seg[2*ind+1] | seg[2*ind+2];
    else seg[ind]=seg[2*ind+1] ^ seg[2*ind+2];
}

void solve() {
    int n,q;
    cin>>n>>q;
    int el= pow(2,n);
    int arr[el];
    for(int i=0;i<el;i++) cin>>arr[i];
    int seg[4*el];
    if(n%2 == 0) build(0,0,el-1,arr, seg,0);
    else build(0,0,el-1,arr, seg,1);
    while(q--) {
        int i,val;
        cin>>i>>val;
        i--;
        if(n%2 == 0) update(0,0,el-1,seg,0,i,val);
        else update(0,0,el-1,seg,1,i,val);
        cout<<seg[0];
        line
    }
}


/*---------------------------------------------------------------------------------------*/
/*--------------------- Single Segment Tree portion ends here ---------------------------*/
/*---------------------------------------------------------------------------------------*/

// Function for returning the prime factors of a number
vector<ll> PrimeFactors(ll n) {
    vector<ll> ans;
    for(ll i=2;i*i <=n;i++) {
        if(n%i == 0) {
            ans.p_b(i);
            while(n%i == 0) {
                n = n/i;
            }
        }
    }
    if(n != 1) {
        ans.p_b(n);
    }
    return ans;
}

// Function for returning the factors of a number
vl findFactors(ll n) {
    vl factors;
    for(int d=1;d*d<=n;d++) {
        if(n%d == 0) {
            factors.p_b(d);
            if(d != n/d) factors.p_b(n/d); // d should be different from n/d
        }
    }
    return factors;
}

void Chaos_Clown() {
   int val;
   cin>>val;
   cout<<val<<endl;
   deb(val);
}


int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	srand(chrono:: high_resolution_clock::now().time_since_epoch().count());

	#ifndef ONLINE_JUDGE
	   freopen("Error.txt", "w", stderr);
	#endif
    int t=1;
	// cin>>t;
	while(t--) {
		Chaos_Clown();
	}

    return 0;
}

int mpow(int base, int exp) {
	base %= mod;
	int result =1;
	while(exp >0) {
		if(exp & 1) result = ((ll) result * base)%mod;
		base = ((ll) base * base)%mod;
		exp >>=1;
	}
	return result;
}


void ipgraph(int n, int m) {
	int i, u,v;
	while(m--) {
		cin>>u>>v;
		u--;v--;
		g[u].p_b(v);
		g[v].p_b(u);
	}
}

void dfs(int u, int par) {
	for(int v: g[u]) {
		if(v==par) continue;
		dfs(v,u);
	}
}
