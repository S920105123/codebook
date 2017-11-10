#include <bits/stdc++.h>
using namespace std;

const double PI=acos(-1);
template<class T>
struct Point {
	// Also a vector
	T x,y;
	Point<T> operator+(const Point<T> &p) const {
		return {x+p.x,y+p.y};
	}
	Point<T> operator-(const Point<T> &p) const {
		return {x-p.x,y-p.y};
	}
	Point<T> operator*(const T &mul) const {
		return {x*mul,y*mul};
	}
	Point<T> operator/(const T &mul) const {
		return {x/mul,y/mul};
	}
	bool operator==(const Point<T> &p) const {
		return x==p.x&&y==p.y;
	}
	T cross(const Point<T> &v) const {
		return x*v.y-y*v.x;
	}
	T dot(const Point<T> &v) const {
		return x*v.x+y*v.y;
	}
	Point<T> normal() { // Normal vector
		return {-y,x};
	}
	Point<T> len() { // length
		return sqrt(x*x+y*y);
	}
	T angle(const Point<T> &v) {
		// Angle from *this to v in [-pi,pi].
		return atan2(cross(v),dot(v));
	}
};

template<class T> 
struct Line {
	// Also a segment
	Point<T> p1,p2;
	T a,b,c; // ax+by+c=0
	Line(){}
	Line(const Point<T> &_p1, const Point<T> &_p2) {
		p1=_p1; p2=_p2;
		a=p1.y-p2.y;
		b=p2.x-p1.x;
		c=-a*p1.x-b*p1.y;
	}
	int relation(const Point<T> &p) {
		// For line, 0 if point on line
		// -1 if left, 1 if right
		Point<T> dir=p2-p1;
		T crs=dir.cross(p-p1);
		return crs==0?0:crs<0?-1:1;
	}
	bool on_segment(const Point<T> &p) { // Point on segment
		return relation(p)==0&&(p2-p).dot(p1-p)<=0;
	}
	bool parallel(const Line<T> &l) { // Two line parallel
		Point<T> dir=p2-p1;
		return dir.cross(l.dir)==0;
	}
	bool equal(const Line<T> &l) { // Two line equal
		return relation(l.p1)==0&&relation(l.p2)==0;
	}
	bool cross_seg(const Line<T> &seg) { // Line intersect segment
		Point<T> dir=p2-p1;
		return dir.cross(seg.p1-p1)*dir.cross(seg.p2-p1)<=0;
	}
	Point<T> intersection(const Line<T> &l) { // Intersection of lines
		T deno=a*l.b-l.a*b;
		if (deno!=0) {
			return { l.c*b-c*l.b/deno, l.a*c-a*l.c};
		}
		// Reaches here means no intersection. (parallel)
	}
	int seg_intersect(const Line<T> &s) const{ // Two segment intersect
		// 0 -> no, 1 -> one point, -1 -> infinity
		Point<T> dir=p2-p1, dir2=s.p2-s.p1;
		T c1=dir.cross(s.p2-p1);
		T c2=dir.cross(s.p1-p1);
		T c3=dir2.cross(p2-s.p1);
		T c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			// Don't need to be so complicated if ignore INF
			if((s.p2-p1).dot(s.p1-p1)>0&&(s.p2-p2).dot(s.p1-p2)>0&&
			   (p1-s.p1).dot(p2-s.p1)>0&&(p1-s.p2).dot(p2-s.p2)>0)return 0;
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return 1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return 1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return 1;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return 1;
			return -1;
		}else if(c1*c2<=0&&c3*c4<=0)return 1;
		return 0;
	}
	Point<T> seg_intersection(Line<T> &s) const {
		Point<T> dir=p2-p1, dir2=s.p2-s.p1;
		T c1=dir.cross(s.p2-p1);
		T c2=dir.cross(s.p1-p1);
		T c3=dir2.cross(p2-s.p1);
		T c4=dir2.cross(p1-s.p1);
		if (c1==0&&c2==0) {
			if((s.p2-p1).dot(s.p1-p1)>0&&(s.p2-p2).dot(s.p1-p2)>0&&
			   (p1-s.p1).dot(p2-s.p1)>0&&(p1-s.p2).dot(p2-s.p2)>0)return 0;
			if(p1==s.p1&&(p2-p1).dot(s.p2-p1)<=0)return p1;
			if(p1==s.p2&&(p2-p1).dot(s.p1-p1)<=0)return p1;
			if(p2==s.p1&&(p1-p2).dot(s.p2-p2)<=0)return p2;
			if(p2==s.p2&&(p1-p2).dot(s.p1-p2)<=0)return p2;
		}else if(c1*c2<=0&&c3*c4<=0)return line_intersection(s);
		// Reaches here means either INF or NOT ANY
		// Use seg_intersect to check OuO
	}
	T dist(const Point<T> &p, bool is_segment) const {
		// Point to Line/segment
		Point<T> dir=p2-p1,v=p-p1;
		if (is_segment) {
			if (dir.dot(v)<0) return v.len();
			if ((p1-p2).dot(p-p2)<0) return (p-p2).len();
		}
		T d=abs(dir.cross(v))/sqrt(v.len2);
		return d;
	}
};

template <class T>
struct Polygon {
	vector<Point<T>> V; // Counterclockwise
	T area() const {
		T res=0;
		for (int i=1;i+1<V.size();i++) {
			res+=(V[i]-V[0]).cross(V[i+1]-V[0]);
		}
		return abs(res/2.0);
	}
	
};

template <class T>
struct Circle {
	T r; // Radius
	Point<T> c; // Center
	
};

int main() {}
