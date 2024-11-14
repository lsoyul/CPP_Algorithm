#include <iostream>
#include <vector>
#include <list>

using namespace std;

struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacents;

void CreateGraph()
{
	vertices.resize(6);
	adjacents = vector<vector<int>>(6, vector<int>(6, -1));

	adjacents[0][1] = 15;
	adjacents[0][3] = 35;
	adjacents[1][0] = 15;
	adjacents[1][2] = 5;
	adjacents[1][3] = 10;
	adjacents[3][4] = 5;
	adjacents[5][4] = 5;
}

void Dijikstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};

	list<VertexCost> discovered;		// 발견 목록
	vector<int> best(6, INT32_MAX);		// 각 정점별로 지금까지 발견한 최소거리
	vector<int> parent(6, -1);

	discovered.push_back(VertexCost{ here, 0 });
	best[here] = 0;
	parent[here] = here;

	while (discovered.empty() == false)
	{
		// 제일 좋은 후보를 찾는다.
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin(); it != discovered.end(); it++)
		{
			const int cost = it->cost;

			if (cost < bestCost)
			{
				bestCost = cost;
				bestIt = it;
			}
		}

		int cost = bestIt->cost;
		here = bestIt->vertex;
		discovered.erase(bestIt);

		// 방문? 더 짧은 경로를 뒤늦게 찾았다면 skip
		if (best[here] < cost)
			continue;

		// 방문!
		for (int there = 0; there < 6; there++)
		{
			// 연결되지 않았으면 스킵.
			if (adjacents[here][there] == -1)
				continue;

			// 더 좋은 경로를 과거에 찾았으면 스킵.
			int nextCost = best[here] + adjacents[here][there];
			if (nextCost >= best[there])
				continue;

			best[there] = nextCost;
			parent[there] = here;

			discovered.push_back(VertexCost{ there, nextCost });
		}
	}
}

int main()
{

}