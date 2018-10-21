#pragma once
#include "henry.h"

namespace _391{
	class Solution2 {
	public:
		bool isRectangleCover(vector<vector<int>> rectangles) {
			int area = 0;
			set<pair<int, int>> sp;
			auto f = [&sp](int x, int y) {
				if (sp.count({ x,y })) sp.erase({ x,y }); else sp.insert({ x,y });
			};
			for (auto v : rectangles) {
				area += (v[2] - v[0])*(v[3] - v[1]);
				f(v[0], v[1]);
				f(v[0], v[3]);
				f(v[2], v[1]);
				f(v[2], v[3]);
			}
			if (sp.size() != 4) return false;
			pair<int, int> p0 = *sp.begin(), p1 = *sp.rbegin();// , p2 = { p0.first, p1.second }, p3 = { p1.first, p0.second };
			return (p1.second - p0.second)*(p1.first - p0.first) == area;//sp.count(p2) && sp.count(p3)
		}
	};

    class Solution_wrong {
    public:
        bool isRectangleCover(vector<vector<int>> rectangles) {
            long long mi=LLONG_MAX, mx=0, area = 0;
            unordered_set<long long> sp;
            long long tmp;
            for (auto& v : rectangles) {
                area += (v[2] - v[0])*(v[3] - v[1]);
                tmp = ((long long)(v[0]) << 32) | v[1];//
                mi = min(tmp, mi);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[0]) << 32) | v[3];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[1];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[3];//
                mx = max(mx, tmp);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
            }
            return 4 == sp.size() &&
                sp.count(mi) &&
                sp.count(mx) &&
                sp.count(mx>>32 <<32|mi<<32>>32) &&
                sp.count(mi >> 32 << 32 | mx << 32 >> 32) &&
                ((mx>>32)-(mi>>32))*(((mx<<32)>>32) - ((mi<<32)>>32)) == area;
        }
    };

    class Solutionx {  //O(N)
    public:
        bool isRectangleCover(vector<vector<int>> rectangles) {
            unordered_map<string, int> hash;
            for (auto val : rectangles) {
                for (int i = 0; i < 4; i++) {
                    string tem = to_string(val[i / 2 * 2]) + ',' + to_string(val[i % 2 * 2 + 1]);
                    if (hash[tem] & (1 << i))
                        return false;
                    hash[tem] |= (1 << i);
                }
            }
            int cntCorner = 0;
            for (auto& val : hash) {
                int sec = val.second;
                if (!(sec&(sec - 1)) && cntCorner++ > 4) return false;
                if ((sec&(sec - 1)) && !(sec == 3 || sec == 12 || sec == 5 || sec == 10 || sec == 15))
                    return false;
            }
            return true;
        }
    };

    class Solution { // O(N)
    public:
        bool isRectangleCover(vector<vector<int>>& rectangles) {
            int minx = INT_MAX, miny = INT_MAX;
            for (auto& v : rectangles) {
                minx = min(min(v[0], v[2]), minx);
                miny = min(min(v[1], v[3]), miny);
            }
            if (minx<0)for (auto& v : rectangles) { v[0] -= minx, v[2] -= minx; }
            if (miny<0)for (auto& v : rectangles) { v[1] -= miny, v[3] -= miny; }

            unordered_set<long long> sp;
            long long mi = LLONG_MAX, mx = LLONG_MIN, area = 0, tmp;
            for (auto& v : rectangles) {
                area += (v[2] - v[0])*(v[3] - v[1]);
                tmp = ((long long)(v[0]) << 32) | v[1];
                mi = min(tmp, mi);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[0]) << 32) | v[3];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[1];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[3];
                mx = max(mx, tmp);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
            }
            return 4 == sp.size() &&
                sp.count(mi) &&
                sp.count(mx) &&
                sp.count(mx >> 32 << 32 | mi << 32 >> 32) &&
                sp.count(mi >> 32 << 32 | mx << 32 >> 32) &&
                ((mx >> 32) - (mi >> 32))*(((mx << 32) >> 32) - ((mi << 32) >> 32)) == area;
        }
    };

    class Solution3 {
    public:
        bool isRectangleCover(vector<vector<int>> rectangles) {
            int area = 0;
            set<pair<int, int>> sp;
            set<long long> h0, h1, h2, h3;
            auto f = [&sp](int x, int y) {
                if (sp.count({ x,y })) sp.erase({ x,y }); else sp.insert({ x,y });
            };
            long long tmp;
            for (auto v : rectangles) {
                tmp = long long(v[0]) << 32 | v[1];
                if (h0.count(tmp)) return false; else h0.insert(tmp);
                tmp = long long(v[0]) << 32 | v[1];
                if (h0.count(tmp)) return false; else h0.insert(tmp);
                tmp = long long(v[0]) << 32 | v[1];
                if (h0.count(tmp)) return false; else h0.insert(tmp);
                area += (v[2] - v[0])*(v[3] - v[1]);
                f(v[0], v[1]);
                f(v[0], v[3]);
                f(v[2], v[1]);
                f(v[2], v[3]);
            }
            if (sp.size() != 4) return false;
            pair<int, int> p0 = *sp.begin(), p1 = *sp.rbegin();// , p2 = { p0.first, p1.second }, p3 = { p1.first, p0.second };
            return (p1.second - p0.second)*(p1.first - p0.first) == area;//sp.count(p2) && sp.count(p3)
        }
    };

    class Solution4 {
    public:
        bool isRectangleCover(vector<vector<int>>& rectangles) {
            /*int minx=INT_MAX, miny=INT_MAX;
            for(auto& v : rectangles){
            if(v[0]<0) minx=min(v[0],minx);
            if(v[1]<0) miny=min(v[1],miny);
            }
            if(minx<0)for(auto& v : rectangles){v[0]-=minx, v[2]-=minx;}
            if(miny<0)for(auto& v : rectangles){v[1]-=miny, v[3]-=miny;}*/
            long long mask = 0xFFFFFFFFLL, SIGN = 0x80000000LL;
            unordered_set<long long> sp;
            long long mi = LLONG_MAX, mx = LLONG_MIN, area = 0, tmp;
            for (auto& v : rectangles) {
                area += (v[2] - v[0])*(v[3] - v[1]);
                tmp = ((long long)(v[0]) << 32) | (v[1] & mask) | ((v[0] & SIGN) << 32) | ((v[1] & SIGN) << 32);
                mi = min(tmp, mi);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[0]) << 32) | (v[3] & mask);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | (v[1] & mask);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | (v[3] & mask) | ((v[2] & SIGN) << 32) | ((v[3] & SIGN) << 32);
                mx = max(mx, tmp);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
            }
            cout << rectangles.size() << endl;
            cout << area << endl;
            cout << mx << endl;
            cout << mi << endl;
            cout << (((mx&(~(1LL << 63))) >> 32) - ((mi&(~(1LL << 63))) >> 32)) << endl;
            cout << (int)(mx&mask) << endl;
            cout << (int)(mi&mask) << endl;
            cout << (((mx&LLONG_MAX)>>32) - (((mi&LLONG_MAX) >> 32)))*((int)(mx&mask) - (int)(mi&mask)) << endl;
            return 4 == sp.size() && sp.count(mi) && sp.count(mx) && (((mx&(~(1LL << 63))) >> 32) - ((mi&(~(1LL << 63))) >> 32))*((int)(mx&mask) - (int)(mi&mask)) == area;
        }
    };

    class Solution5 {
    public:
        bool isRectangleCover(vector<vector<int>>& rectangles) {
            int minx = INT_MAX, miny = INT_MAX;
            for (auto& v : rectangles)
                minx = min(v[0], minx), miny = min(v[1], miny);
            if (minx<0)for (auto& v : rectangles) { v[0] -= minx, v[2] -= minx; }
            if (miny<0)for (auto& v : rectangles) { v[1] -= miny, v[3] -= miny; }
            unordered_set<long long> sp;
            long long mi = LLONG_MAX, mx = LLONG_MIN, area = 0, tmp;
            for (auto& v : rectangles) {
                area += (v[2] - v[0])*(v[3] - v[1]);
                tmp = ((long long)(v[0]) << 32) | v[1];
                mi = min(tmp, mi);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[0]) << 32) | v[3];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[1];
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
                tmp = ((long long)(v[2]) << 32) | v[3];
                mx = max(mx, tmp);
                if (sp.count(tmp)) sp.erase(tmp); else sp.insert(tmp);
            }
            return 4 == sp.size() && sp.count(mi) && sp.count(mx) && ((mx >> 32) - (mi >> 32))*((mx << 32 >> 32) - (mi << 32 >> 32)) == area;
        }
    };

	void test() {
		Solution2 s;
        assert(s.isRectangleCover({ { 0, 0, 1, 1 },{ 0,0,2,1 },{ 1,0,2,1 },{ 0,2,2,3 } })
            == false);
		assert(s.isRectangleCover({ { 0,0,4,1 },{ 0,0,4,1 } })
			== false);
		assert(s.isRectangleCover({ { 1,1,2,2 },{ 1,1,2,2 },{ 2,1,3,2 } })
			== false);
	}
}
