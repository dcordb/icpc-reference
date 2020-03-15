/*
	Short and easy implementation of Small to Large
	Idea is to merge n sets of objects in O(n log n)
*/

template <typename T>
struct DataUnion {
	T s;

	DataUnion(const T &s = {}) : s(s) {}

	/*
		join this.s with o.s, the union is saved in this
		NOTICE: o.s will have out of date data
	*/

	void join(DataUnion &o) {
		if(s.size() < o.s.size())
			s.swap(o.s);

		for(auto &e : o.s)
			s.insert(e);
	}
};

/*
	Usage:
		DataUnion <set <int> > set1;
		DataUnion <set <int> > set2;
		set1.join(set2)
*/