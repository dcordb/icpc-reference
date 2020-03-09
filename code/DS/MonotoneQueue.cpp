/*
	implements monotone queue
	using comparator to compare v with last value of deque
*/

template <typename T, typename Comparator, typename RAIter>
struct monotone_queue {
	RAIter arr;
	deque <int> q;
	Comparator cmp;

	monotone_queue(RAIter x) {
		arr = x;
		cmp = Comparator();
	}

	void add(int p) {
		while(!q.empty() && cmp(arr[p], arr[q.back()]))
			q.pop_back();

		q.push_back(p);
	}

	void remove(int p) {
		while(!q.empty() && q.front() <= p)
			q.pop_front();
	}

	int get() {
		return q.empty() ? -1 : q.front();
	}
};

/*
	Usage: (monotone queue of array a)

	//of maximum (allow equal elements, else pass greater_equal <int>)
	monotone_queue <int, greater <int>, vector <int> :: iterator > mx(a.begin());

	//of minimum (allow equal elements, else pass less_equal <int>)
	monotone_queue <int, less <int>, vector <int> :: iterator > mn(a.begin());
*/