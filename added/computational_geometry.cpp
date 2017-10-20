template<class T>
int intersection(Segment<T> &s1, Segment<T> &s2, Point<T> &inter) {
	// Return 0 -> one point, 1 -> infinity, -1 -> no
	// Store intersection into inter.
	Vector<T> v1={s1.p1,s1.p2},v2={s1.p1,s2.p1},v3={s1.p1,s2.p2};
	Vector<T> v4={s2.p1,s2.p2},v5={s2.p1,s1.p1},v6={s2.p1,s1.p2};
	bool b1=op_signed(cross(v1,v2),cross(v1,v3));
	bool b2=op_signed(cross(v4,v5),cross(v4,v6));
	if (b1&&b2) {
		T mul=cross({s1.p1,s2.p1},v4)/cross(v1,v4);
		inter={s1.p1.x+mul*v1.x,s1.p1.y+mul*v1.y};
		return 0;
	}
	
	vector<Point<T>> v;
	if (in_segment(s1.p1,s2)) v.push_back(s1.p1);
	if (in_segment(s1.p2,s2)) v.push_back(s1.p2);
	if (in_segment(s2.p1,s1)) v.push_back(s2.p1);
	if (in_segment(s2.p2,s1)) v.push_back(s2.p2);
	if (v.empty()) return -1;
	if (v.size()==1||(v.size()==2&&v[0]==v[1])) {
		inter=v[0];
		return 0;
	}
	return 1;
}

