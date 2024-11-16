#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		//------ 우선 힙 구조 맞추기
		_heap.push_back(data);

		// 바꿔치기 시작
		int now = static_cast<int>(_heap.size()) - 1;	// 맨 마지막 인덱스

		// 루트 노드까지 계속 시도
		while (now > 0)
		{
			// 부모 노드 데이터보다 더 작으면 stay
			int next = (now - 1) / 2;
			if (_predicate(_heap[now], _heap[next]))
				break;

			// 부모 노드 데이터보다 더 크면 바꿔치기
			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	void pop()
	{
		_heap[0] = _heap.back();
		_heap.pop_back();

		int now = 0;	// now = 루트

		while (true)
		{
			int left = 2 * now + 1;
			int right = 2 * now + 2;

			// 리프에 도달한 경우 종료
			if (left >= _heap.size())
				break;

			int next = now;

			// 왼쪽과 비교
			if (_predicate(_heap[next], left))
				next = left;

			// 위 둘 중 큰 값을 right 값과 비교
			if (right < _heap.size() && _predicate(_heap[next], _heap[right]))
				next = right;

			// 왼쪽/오른쪽 둘 다 현재값보다 작다면 종료
			if (next == now)
				break;

			::swap(_heap[now], _heap[next]);
			now = next;
		}
	}

	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:
	Container _heap = {};
	Predicate _predicate = {};
};

int main()
{
	PriorityQueue<int, vector<int>, less<int>> pq;
	pq.push(100);
	pq.push(300);
	pq.push(200);
	pq.push(500);
	pq.push(400);

	while (pq.empty() == false)
	{
		int value = pq.top();
		pq.pop();

		cout << value << endl;
	}
}