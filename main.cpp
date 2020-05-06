#include "bits/stdc++.h"
using namespace std;
///////////////////////////////////////////
const long long int INF = 1LL<<60;
const long long int Mod = 1000000007;
using ll = long long int; using ci = const int;
using vi = vector<int>;  using Vi = vector<long long int>;
using P = pair<int, int>;  using PLL = pair<ll, ll>;
using matrix = vector<vector<ll>>;
#define pb(x) push_back(x)
#define mp(x,y) make_pair(x,y)
#define all(x) (x).begin(),(x).end()
#define rep(i,N) for(ll i = 0; i < (ll)N; i++)
#define repi(i,a,b) for(ll i = ll(a); i < ll(b); ++i)
template<class T>bool chmax(T &former, const T &b) { if (former<=b) { former=b; return true; } return false; }
template<class T>bool chmin(T &former, const T &b) { if (b<=former) { former=b; return true; } return false; }
template<class T>T sqar(T x){ return x*x; }//sqrt(x)は平方根;
#define Sort(v) std::sort(v.begin(), v.end(), std::greater<decltype(v[0])>()) //降順でVをソート
#define p_queue(v) priority_queue<v, vector<v>, greater<v> >
template<class T> inline void princ(T x){cout<<x<<" ";};
template<class T> inline void print(T x){cout<<x<<"\n";};
template<class T> inline void Yes(T condition){ if(condition) cout << "Yes" << endl; else cout << "No" << endl; }
template<class T> inline void YES(T condition){ if(condition) cout << "YES" << endl; else cout << "NO" << endl; }
///////////////////////////////////////////////////////////////////////////////////

std::random_device seed_gen;
std::mt19937 engine(seed_gen());
int bxx[2] = {-1,1};
int bx[3] = {-1,0,1};
const int N = 8;
map<pair<PLL,ll>,ll> dp;

uint64_t trasf(uint64_t bd,int dir){//dir:0<,1^,2>,3v,4左上,5左下,6:右上,7:右下
	switch(dir){
		case 0:
			return (bd << 1) & 0xfefefefefefefefe;
			break;
		case 1:
			return (bd << 8) & 0xffffffffffffff00;
			break;
		case 2:
			return (bd >> 1) & 0x7f7f7f7f7f7f7f7f;
			break;
		case 3:
			return (bd >> 8) & 0x00ffffffffffffff;
			break;
		case 4:
			return (bd << 9) & 0xfefefefefefefe00;
			break;
		case 5:
			return (bd >> 7) & 0x00fefefefefefefe;
			break;
		case 6:
			return (bd << 7) & 0x7f7f7f7f7f7f7f00;
			break;
		case 7:
			return (bd >> 9) & 0x007f7f7f7f7f7f7f;
			break;
		default:
			return 0;
			break;
	}
}

struct bod{
	//vector<vector<uint8_t>> ma;//0,bl:1,wh:2
	uint64_t Black,White;
	uint64_t leg_b,leg_w;
	int8_t bl;
	int8_t wh;
	vector<pair<int,int>> stw,stb;
	//map<PLL,ll> dp;
	void init(){
		//ma.resize(N,vector<uint8_t>(N,0));
		Black = 0LL;
		White = 0LL;
		bl = 0LL;
		wh = 0LL;
		leg_b = 0LL;
		leg_w = 0LL;
	}
//	bool _ck(int x,int y){//0-indexed
//		if(x<0 || x>=N)return false;
//		if(y<0 || y>=N)return false;
//		if((Black & (1LL<<(x+y*8))) || (White & (1LL<<(x+y*8))))return false;
//		else return true;
//	}
//	bool _ck2(int x,int y){//8近傍チェック
//		if(x<0 || x>=N)return false;
//		if(y<0 || y>=N)return false;
//		if((Black & (1LL<<(x+y*8))) || (White & (1LL<<(x+y*8))))return true;
//		else return false;
//	}

//	bool ck(int x,int y){//(x,y)におけるかどうか//0-indexed
//		if(x<0 || x>=N)return false;
//		if(y<0 || y>=N)return false;
//		if((Black & (1LL<<(x+y*8))) || (White & (1LL<<(x+y*8))))return false;
//		bool ans = false;
////		rep(i,2){
////			if(_ck2(x+bxx[i],y))ans = true;
////			if(_ck2(x,y+bxx[i]))ans = true;
////		}
//		rep(i,3){
//			rep(j,3){
//				if(i!=1 || j!=1){
//					if(_ck2(x+bx[i],y+bx[j])){
//						ans = true;
//						break;
//					}
//				}
//			}
//		}
//		if(Black == 0 && White==0)return true;
//		return ans;
//	}

	int ck_color(int x,int y){
		if(Black & (1LL<<(x+y*8)))return 1;
		else if(White & (1LL<<(x+y*8)))return 2;
		else return 0;
	}
//	bool ck_same_bod(uint64_t Bl,uint64_t Wh){
//		if(Black == Bl && White == Wh)return true;
//		else return false;
//	}
//	bool _calc(int x,int y,int col,int fg = 0){//0-indexed//fg == 1だとこまが帰らなくてもok,fg==2だとcheckのみ
//		int ans = 0;
//		int rev = (col)%2+1;
//		int tmp = 0;
//		uint64_t Bl = Black;
//		uint64_t Wh = White;
//		if(!ck(x,y))return false;
//		repi(i,x+1,N){
//			if(ck_color(i,y)==col){
//				if(fg==2){
//					if(!ck_same_bod(Bl,Wh))return true;
//				}
//				Black = Bl;
//				White = Wh;
//				ans += tmp;
//				break;
//			}else if(ck_color(i,y)==0){
//				break;
//			}else{
//				if(col==1){
//					Wh &= ~(1LL<<(i+y*8));
//					Bl |= (1LL<<(i+y*8));
//				}else{
//					Bl &= ~(1LL<<(i+y*8));
//					Wh |= (1LL<<(i+y*8));
//				}
//				tmp++;
//			}
//		}
//		tmp = 0;
//		Bl = Black;
//		Wh = White;
//		for(int i=x-1;i>=0;i--){
//			if(ck_color(i,y)==col){
//				if(fg==2){
//					if(!ck_same_bod(Bl,Wh))return true;
//				}
//				Black = Bl;
//				White = Wh;
//				ans += tmp;
//				break;
//			}else if(ck_color(i,y)==0){
//				break;
//			}else{
//				if(col==1){
//					Wh &= ~(1LL<<(i+y*8));
//					Bl |= (1LL<<(i+y*8));
//				}else{
//					Bl &= ~(1LL<<(i+y*8));
//					Wh |= (1LL<<(i+y*8));
//				}
//				tmp++;
//			}
//		}
//		tmp = 0;
//		Bl = Black;
//		Wh = White;
//		for(int i=y-1;i>=0;i--){
//			if(ck_color(x,i)==col){
//				if(fg==2){
//					if(!ck_same_bod(Bl,Wh))return true;
//				}
//				Black = Bl;
//				White = Wh;
//				ans += tmp;
//				break;
//			}else if(ck_color(x,i)==0){
//				break;
//			}else{
//				if(col==1){
//					Wh &= ~(1LL<<(x+i*8));
//					Bl |= (1LL<<(x+i*8));
//				}else{
//					Bl &= ~(1LL<<(x+i*8));
//					Wh |= (1LL<<(x+i*8));
//				}
//				tmp++;
//			}
//		}
//		tmp = 0;
//		Bl = Black;
//		Wh = White;
//		for(int i=y+1;i<N;i++){
//			if(ck_color(x,i)==col){
//				if(fg==2){
//					if(!ck_same_bod(Bl,Wh))return true;
//				}
//				Black = Bl;
//				White = Wh;
//				ans += tmp;
//				break;
//			}else if(ck_color(x,i)==0){
//				break;
//			}else{
//				if(col==1){
//					Wh &= ~(1LL<<(x+i*8));
//					Bl |= (1LL<<(x+i*8));
//				}else{
//					Bl &= ~(1LL<<(x+i*8));
//					Wh |= (1LL<<(x+i*8));
//				}
//				tmp++;
//			}
//		}
//		rep(i,2){
//			rep(j,2){
//				Bl = Black;
//				Wh = White;
//				tmp = 0;
//				repi(k,1,N){
//					int nx = x+bxx[i]*k;
//					int ny = y+bxx[j]*k;
//					if(nx<0 || nx>=N)break;
//					if(ny<0 || ny>=N)break;
//					if(ck_color(nx,ny)==0)break;
//					if(ck_color(nx,ny)==rev){
//						tmp++;
//						if(col==1){
//							Wh &= ~(1LL<<(nx+ny*8));
//							Bl |= (1LL<<(nx+ny*8));
//						}else{
//							Bl &= ~(1LL<<(nx+ny*8));
//							Wh |= (1LL<<(nx+ny*8));
//						}
//					}
//					if(ck_color(nx,ny)==col){
//						if(fg==2){
//							if(!ck_same_bod(Bl,Wh))return true;
//						}
//						Black = Bl;
//						White = Wh;
//						ans += tmp;
//						break;
//					}
//				}
//			}
//		}
//		if(ans==0 && (fg==0 || fg==2)){
//			return false;
//		}
//		if(col==1){//bl
//			bl += ans+1;
//			wh -= ans;
//		}else if(col==2){//wh
//			bl -= ans;
//			wh += ans+1;
//		}
//		return true;
//	}

//	bool set_stone2(int x,int y,int col,int fg = 0){//col:1->bl,2->wh//i-indexed,fg=1強制追加,2:check
//		x--;
//		y--;//0-indexed
//		if(!ck(x,y))return false;
//		if(!_calc(x,y,col,fg))return false;
//		if(col==1){
//			//White &= ~(1LL<<(x+y*8));
//			Black |= (1LL<<(x+y*8));
//		}else{
//			//Black &= ~(1LL<<(x+y*8));
//			White |= (1LL<<(x+y*8));
//		}
//		if(fg==2)return true;
//		stb.erase(mp(x+1,y+1));
//		stw.erase(mp(x+1,y+1));
//		can.erase(mp(x+1,y+1));
//		rep(i,3){
//			rep(j,3){
//				if(_ck(x+bx[i],y+bx[j])){
//					if(_ck(x+bx[i],y+bx[j]))can.insert(mp(x+bx[i]+1,y+bx[j]+1));
//					if(_calc(x+bx[i],y+bx[j],2,2))stw.insert(mp(x+bx[i]+1,y+bx[j]+1));
//					if(_calc(x+bx[i],y+bx[j],1,2))stb.insert(mp(x+bx[i]+1,y+bx[j]+1));
//				}
//			}
//		}
//		set<pair<int,int>> tb,tw;
//
//		tw = stw;
//		tb = stb;
//		if(fg==0)for(auto i: stb){
//				if(_calc(i.first-1,i.second-1,2,2)) {
//					tw.insert(i);
//				}
//			}
//		if(fg==0)for(auto i: stw){
//				if(_calc(i.first-1,i.second-1,1,2)){
//					tb.insert(i);
//				}
//			}
//		if(fg==0)for(auto i: stb){
//				if(!_calc(i.first-1,i.second-1,1,2)){
//					tb.erase(i);
//				}
//			}
//		if(fg==0)for(auto i: stw){
//				if(!_calc(i.first-1,i.second-1,2,2)) {
//					tw.erase(i);
//				}
//			}
//		if(fg==0)stb = tb;
//		if(fg==0)stw = tw;
//		// stb.clear();
//		// stw.clear();
//		// rep(i,8){
//		// 	rep(j,8){
//		// 		if(ck(i,j) && _calc(i,j,1,2))stb.insert(mp(i+1,j+1));
//		// 		if(ck(i,j) && _calc(i,j,2,2))stw.insert(mp(i+1,j+1));
//		// 	}
//		// }
//		if(fg==0){
//			for(auto i: can){
//				if(_calc(i.first-1,i.second-1,1,2))stb.insert(i);
//				if(_calc(i.first-1,i.second-1,2,2))stw.insert(i);
//			}
//		}
//		return true;
//	}

	uint64_t cal_cod(int x,int y){//calc coordinate.0-indexed
		return (uint64_t)1 << (x+y*8);
	}

	bool ck_turn(int x,int y,int col){//(x,y)にcolを置けるか.0-indexed
		uint64_t idn = cal_cod(x,y);
		if(idn & Black)return false;
		if(idn & White)return false;
		if(col==1){
			return (idn & leg_b);
		}else if(col==2){
			return (idn & leg_w);
		}else{
			return false;
		}
	}

	void make_legal(int col){//これは内部用...使わないで...
		uint64_t bd_now,bd_op;
		if(col==1){
			bd_now = Black;
			bd_op = White;
		}else if(col==2){
			bd_now = White;
			bd_op = Black;
		}else{
			bd_now = 0;
		}//set board
		uint64_t horiz = bd_op & 0x7e7e7e7e7e7e7e7e;//左右辺
		uint64_t vert = bd_op & 0x00FFFFFFFFFFFF00;//上下辺
		uint64_t edg = bd_op & 0x007e7e7e7e7e7e00;//全辺
		uint64_t ans;
		uint64_t blank = ~(Black | White);
		uint64_t tmp;

		tmp = horiz & (bd_now<<1);
		rep(i,5){
			tmp |= horiz & (tmp<<1);
		}
		ans = blank & (tmp<<1);

		tmp = horiz & (bd_now>>1);
		rep(i,5){
			tmp |= horiz & (tmp>>1);
		}
		ans |= blank & (tmp>>1);

		tmp = vert & (bd_now<<8);
		rep(i,5){
			tmp |= horiz & (tmp<<8);
		}
		ans |= blank & (tmp<<8);

		tmp = vert & (bd_now>>8);
		rep(i,5){
			tmp |= horiz & (tmp>>8);
		}
		ans |= blank & (tmp>>8);

		tmp = vert & (bd_now<<7);
		rep(i,5){
			tmp |= horiz & (tmp<<7);
		}
		ans |= blank & (tmp<<7);

		tmp = vert & (bd_now>>7);
		rep(i,5){
			tmp |= horiz & (tmp>>7);
		}
		ans |= blank & (tmp>>7);

		tmp = vert & (bd_now<<9);
		rep(i,5){
			tmp |= horiz & (tmp<<9);
		}
		ans |= blank & (tmp<<9);

		tmp = vert & (bd_now>>9);
		rep(i,5){
			tmp |= horiz & (tmp>>9);
		}
		ans |= blank & (tmp>>9);

		if(col==2)leg_w = ans;
		if(col==1)leg_b = ans;
	}

	void make_legal(){
		make_legal(1);
		make_legal(2);
		bl = __builtin_popcountll((ll)Black);
		wh = __builtin_popcountll((ll)White);
		//これ以下はいずれはなくすかも...
		stb.clear();
		stw.clear();
		rep(i,8){
			rep(j,8){
				if(ck_turn(i,j,1))stb.pb(mp(i+1,j+1));
				if(ck_turn(i,j,2))stw.pb(mp(i+1,j+1));
			}
		}
	}



	ll set_stone(int x,int y,int col,int flag = 0){//flag = 0:配置,1:強制配置,2:判定,1-indexed
		x--;
		y--;//0-indexed
		if(col!=1 && col!=2)return false;
		if(flag==1){
			if(col==1){
				Black |= cal_cod(x,y);
				make_legal();
				return true;
			}else{
				White |= cal_cod(x,y);
				make_legal();
				return true;
			}
		}
		if(flag==0 || flag==2){
			if(!ck_turn(x,y,col))return false;
			uint64_t pt = cal_cod(x,y),oppo,now;//opponent,now
			if(col==1){
				oppo = White;
				now = Black;
			}else{
				oppo = Black;
				now = White;
			}
			uint64_t ans = 0;//返す奴
			rep(i,8){//8方向
				uint64_t mask = trasf(pt,i);
				uint64_t tmp = 0;
				while((mask!=0) && ((mask & oppo) != 0)){
					tmp |= mask;
					mask = trasf(mask,i);
				}
				if(mask & now){
					ans |= tmp;
				}
			}
			if(flag==2)return ans;
			if(ans==0)return 0;
//			if(col==1){
//				Black ^= (pt|ans);
//				White ^= ans;
//			}else{
//				White ^= (pt|ans);
//				Black ^= ans;
//			}
//			make_legal();//合法手の生成.
			//if(ans==0)return false;
			set_rev(x,y,ans,col);
			return ans;
		}
		return 0;
	}

	void set_rev(ll x,ll y,ll rev,ll col){
		ll pt = cal_cod(x,y);
		if(col==1){
			Black ^= (pt|rev);
			White ^= rev;
		}else{
			White ^= (pt|rev);
			Black ^= rev;
		}
		make_legal();
	}
	void clear_rev(ll x,ll y,ll rev,ll col){//make legalをする
		ll pt = cal_cod(x,y);
		if(col==1){
			Black ^= (pt|rev);
			White ^= rev;
		}else{
			White ^= (pt|rev);
			Black ^= rev;
		}
		make_legal();
	}
	void clear_rev(ll x,ll y,ll rev,ll col,vector<pair<int,int>> &vb,vector<pair<int,int>> &vw){//0-indexed
		ll pt = cal_cod(x,y);
		if(col==1){
			Black ^= (pt|rev);
			White ^= rev;
		}else{
			White ^= (pt|rev);
			Black ^= rev;
		}
		bl = __builtin_popcountll((ll)Black);
		wh = __builtin_popcountll((ll)White);
		stb = vb;
		stw = vw;
	}

	ll get_col(ll x,ll y){//0-ind
		ll id = cal_cod(x,y);
		if(Black & (1LL<<id))return 1;
		if(White & (1LL<id))return 2;
		else return 0;
	}

	ll count_kakutei(ll col){
		int bx[4]={0,0,7,7};
		int by[4]={0,7,0,7};
		ll ans = 0;
		uint64_t bit;
		if(col==1){
			bit = Black;
		}else{
			bit = White;
		}
		rep(i,4){
			ll xx = bx[i];
			ll yy = by[i];
			ll cod = cal_cod(xx,yy);
			if(ck_color(xx,yy)==col)ans++;
			if(get_col(xx,yy)!=col)continue;
			rep(j,8){
				rep(k,8){
					cod = trasf(cod,j);
					if(bit & cod)ans++;
//					else{
//						break;
//					}
				}
			}
		}
		return ans;
	}

	ll calc_value(){
		bl = __builtin_popcountll((ll)Black);
		wh = __builtin_popcountll((ll)White);
		ll ans = bl*2 - wh*2;
		ans += count_kakutei(1)*4;
		ans -= count_kakutei(2)*4;
		ans += stb.size();
		ans -= stw.size();
		return ans;
	};
};
bool operator==(bod x,bod y){
	if(x.Black==y.Black && x.White == y.White)return true;
	else return false;
}
bool operator<(bod x,bod y){
	if(x.Black==y.Black){
		if(x.White<y.White)return true;
		else return false;
	}else if(x.Black<y.Black)return true;
	else return false;
}
bool operator>(bod x,bod y){
	if(x.Black==y.Black){
		if(x.White>y.White)return true;
		else return false;
	}else if(x.Black>y.Black)return true;
	else return false;
}

char trans(bod bd,int x,int y){
	if(bd.ck_color(x,y)==0)return '_';
	if(bd.ck_color(x,y)==2)return 'o';
	else return '*';
}

void printb(bod x){
	cout<<"  ";
	rep(i,N)cout<<i+1;
	print("");
	for(int i = N-1;i>=0;i--){
		cout<<i+1<<"|";
		rep(j,N){
			cout<<trans(x,j,i);
		}
		cout<<""<<endl;
	}
	cout<<"  ";
	rep(i,N)cout<<i+1;
	cout<<"|  black:"<<(int)x.bl<<", white:"<<(int)x.wh;
	print("");

}
ll dfs(bod &bd,int col,int depth,ll mi,ll mx,int flag = 0){//iddfs,flag = 2の時は枝刈り,1の時はメモなし全探索,3の時は全探索
	PLL bd_memo = mp(bd.Black,bd.White);
	if(dp.count(mp(bd_memo,col)))return dp[mp(bd_memo,col)];
	if(depth<0){
		//printb(bd);
		//print(bd.calc_value());
		return bd.calc_value();
	}
	ll ans = 0;
	//set<pair<int,int>> stt;
	vector<pair<int,int>> stt;
	if(col==1){
		stt = bd.stb;
	}else{
		stt = bd.stw;
	}
	if(stt.empty()){
		return bd.bl-bd.wh;
	}
	ll rand;
	vector<pair<int,int>> preB,preW;//復元用
	preB = bd.stb;
	preW = bd.stw;
	if(col == 1){//bl
		ans = -INF;
		priority_queue<pair<ll,pair<ll,pair<int,int>>>> pq;//{評価値,rev}
		for(auto i:stt) {
			rand = engine();
			//if(rand%23 ==0 && flag!=0)continue;
			//bdd = bd;
			//bool flg = bdd.set_stone(i.first, i.second, col);
			ll rev = bd.set_stone(i.first,i.second,col,2);
			if(rev==0){
				bd.clear_rev(i.first-1,i.second-1,rev,col,preB,preW);
				continue;
			}
			bd.set_rev(i.first-1,i.second-1,rev,col);
			if(flag!=0)chmax(ans, dfs(bd, 2, depth-1,mi,mx,flag));
			if(flag==0){
				ll tmp = dfs(bd, 2, 6,mi,mx,1);
				pq.push(mp(tmp,mp(rev,mp(i.first,i.second))));
			};
			bd.clear_rev(i.first-1,i.second-1,rev,col,preB,preW);
			if(flag!=0)chmax(mi,ans);
			if(flag!=0 && flag !=3)if(mi>=mx)break;
		}
		if(flag==0){
			while(!pq.empty()){
				ll rev = pq.top().second.first;
				int xx = pq.top().second.second.first;
				int yy = pq.top().second.second.second;
				pq.pop();
				bd.set_rev(xx-1,yy-1,rev,col);
				chmax(ans, dfs(bd, 2, depth,mi,mx,2));
				bd.clear_rev(xx-1,yy-1,rev,col,preB,preW);//復元
				chmax(mi,ans);
				if(mi>=mx)break;
			}
		}
	}else{
		ans = INF;
		priority_queue< pair<ll,pair<ll,pair<int,int>>> ,vector<pair<ll,pair<ll,pair<int,int>>>>,
				greater< pair<ll,pair<ll,pair<int,int>>>> > pq;
		for(auto i:stt) {
			//rand = engine();
			//if(rand%23 ==0 && flag!=0)continue;
			ll rev = bd.set_stone(i.first,i.second,col,2);
			if(rev==0){
				bd.clear_rev(i.first-1,i.second-1,rev,col,preB,preW);
				continue;
			}
			bd.set_rev(i.first-1,i.second-1,rev,col);
			if(flag!=0)chmin(ans, dfs(bd, 1, depth-1,mi,mx,flag));
			if(flag==0){
				ll tmp = dfs(bd, 1, 6,mi,mx,1);
				pq.push(mp(tmp,mp(rev,mp(i.first,i.second))));
			}
			bd.clear_rev(i.first-1,i.second-1,rev,col,preB,preW);
			if(flag!=0)chmin(mx,ans);
			if(flag!=0 && flag!=3)if(mi>=mx)break;
		}
		if(flag==0){
			while(!pq.empty()){
				ll rev = pq.top().second.first;
				ll xx = pq.top().second.second.first;
				ll yy = pq.top().second.second.second;
				pq.pop();
				bd.set_rev(xx-1,yy-1,rev,col);
				chmin(ans, dfs(bd, 1, depth,mi,mx,2));
				bd.clear_rev(xx-1,yy-1,rev,col,preB,preW);//復元
				chmin(mi,ans);
				if(mi>=mx)break;
			}
		}
	}
	if(col==1 && ans == -INF)ans = bd.calc_value();
	if(col==2 && ans == INF)ans = bd.calc_value();
	if(flag == 1)return ans;
	return dp[mp(bd_memo,col)] = ans;
}

int main(){
	//cin.tie(0);ios::sync_with_stdio(false);
	chrono::system_clock::time_point start, end;//時間
	bod s;
	s.init();
//	s.Black |= (1LL<<(3+3*8));
//	s.Black |= (1LL<<(4+4*8));
//	s.White |= (1LL<<(3+4*8));
//	s.White |= (1LL<<(4+3*8));
//	s.bl = 2; s.wh = 2;
	s.set_stone(4,4,1,1);
	s.set_stone(4,5,2,1);
	s.set_stone(5,5,1,1);
	s.set_stone(5,4,2,1);
	//game_set
	printb(s);
//	cout<<"Loading"<<std::flush;
//	for(auto i:s.stw){
//		bod tmp = s;
//		ll fg = tmp.set_stone(i.first,i.second,2);
//		if(fg==0)continue;
//		dfs(tmp,1,58,-INF,INF,3);
//		cout<<"."<< std::flush;
//	}
	print("");
	while(!s.stw.empty()){
		cout<<"座標を半角,空白区切りで入力してください.(入力例)2 2"<<endl;
		int xx,yy;
		while(1){
			cin>>xx>>yy;
			if(s.set_stone(xx,yy,2)){
				break;
			}else{
				cout<<"もう一度"<<endl;
			}
		}
		//s.set_stone(xx,yy,2);
		printb(s);
		if(s.stb.empty()){
			cout<<"end"<<endl;
			break;
		}
		cout<<"now thinking :| "<<endl;
		cout<<"calculating"<< std::flush;
		pair<int,int> pt;
		ll num = -INF;
		bod tmp;
		dp.clear();
		ll sum = s.bl+s.wh;
		//set<pair<int,int>> stb_b = s.stb;
		vector<pair<int,int>> stb_b = s.stb;
		start = chrono::system_clock::now();//時間
		for(auto i:stb_b){
			tmp = s;
			ll fg = tmp.set_stone(i.first,i.second,1);
			if(fg==0)continue;
			if(sum<10)if(chmax(num,dfs(tmp,2,40,num,INF)))pt = i;
			if(sum>=10 && sum<20)if(chmax(num,dfs(tmp,2,34,num,INF)))pt = i;
			if(sum>=20 && sum<25)if(chmax(num,dfs(tmp,2,34,num,INF)))pt = i;
			if(sum>=25 && sum<30)if(chmax(num,dfs(tmp,2,34,num,INF)))pt = i;
			if(s.bl+s.wh>=30 && s.bl+s.wh<40)if(chmax(num,dfs(tmp,2,34,num,INF)))pt = i;
			if(s.bl+s.wh>=40)if(chmax(num,dfs(tmp,2,40,num,INF)))pt = i;
			cout<<"."<< std::flush;
		}
		end = chrono::system_clock::now();//時間
		print("");
		cout<<"time:"<<chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0<<"ms"<<endl;
		cout<<"駒数";
		princ(sum);
		cout<<"評価値:";
		print(num);
		s.set_stone(pt.first,pt.second,1);

		printb(s);
	}
	return 0;
}
