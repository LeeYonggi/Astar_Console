#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

struct Node
{
public:
	int x = 0;
	int y = 0;

public:
	float restDistance = 0;
	float prevDistance = 0;
	float totalDistance = 0;

public:
	Node* parent = nullptr;

public:
	Node(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

public:
	void Init()
	{
		restDistance = 0;
		prevDistance = 0;
		totalDistance = 0;

		parent = nullptr;
	}
	void Init(float _prevDistance, float _restDistance)
	{
		restDistance = _restDistance;
		prevDistance = _prevDistance;
		totalDistance = _restDistance + _prevDistance;
	}
};

void CreateMapNode();
void NodeMapInit();
Node* TrackingNode(int indexX, int indexY);
Node* GetShortNode();
void ReFlexiveAstarFunc(Node* node);
float GetDistanceNodes(Node* node1, Node* node2);
float GetLengthNodes(Node* node1, Node* node2);


extern Node* goalNode = nullptr;

extern std::set<Node*> obstacles = std::set<Node*>();
extern std::set<Node*> closeNodes = std::set<Node*>();
extern std::set<Node*> openNodes = std::set<Node*>();
extern std::vector<std::vector<Node*>> nodeVector = std::vector<std::vector<Node*>>();