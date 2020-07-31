// Astar Console.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "Astar Console.h"


//Node* goalNode = nullptr;
//
//set<Node*> obstacles = set<Node*>();
//set<Node*> closeNodes = set<Node*>();
//set<Node*> openNodes = set<Node*>();

int main()
{
	CreateMapNode();
	NodeMapInit();

	obstacles.insert(nodeVector[4][5]);
	obstacles.insert(nodeVector[5][5]);
	obstacles.insert(nodeVector[6][5]);

	goalNode = nodeVector[5][9];
	
	ReFlexiveAstarFunc(nodeVector[5][1]);

	for (int y = 0; y < nodeVector.size(); y++)
	{
		for (int x = 0; x < nodeVector[y].size(); x++)
		{
			delete nodeVector[y][x];
		}
		nodeVector[y].clear();
	}
	nodeVector.clear();
	obstacles.clear();
	closeNodes.clear();
	openNodes.clear();
}

void CreateMapNode()
{
	for (int y = 0; y < 10; y++)
	{
		nodeVector.push_back(std::vector<Node*>());

		for (int x = 0; x < 10; x++)
		{
			nodeVector[y].push_back(new Node(x, y));
		}
	}
}

void NodeMapInit()
{
	for (int y = 0; y < nodeVector.size(); y++)
	{
		for (int x = 0; x < nodeVector[y].size(); x++)
		{
			Node* tempNode = nodeVector[y][x];

			tempNode->Init();
		}
	}
}

Node* TrackingNode(int indexX, int indexY)
{
	Node* startNode = nodeVector[indexY][indexX];

	if(openNodes.find(startNode) != openNodes.end())
		openNodes.erase(startNode);
	closeNodes.insert(startNode);

	for (int y = indexY - 1; y <= indexY + 1; y++)
	{
		if (y < 0 || y >= nodeVector.size())
			continue;
		for (int x = indexX - 1; x <= indexX + 1; x++)
		{
			if (x < 0 || x >= nodeVector[y].size())
				continue;

			Node* tempNode = nodeVector[y][x];
			std::set<Node*>::iterator obstacleIter = obstacles.find(tempNode);
			std::set<Node*>::iterator closeIter = closeNodes.find(tempNode);
			std::set<Node*>::iterator openIter = openNodes.find(tempNode);

			if (openIter != openNodes.end())
			{
				float nextTotal = startNode->prevDistance + (**openIter).restDistance;

				nextTotal += GetLengthNodes(startNode, tempNode);

				if (nextTotal < (*openIter)->totalDistance)
				{
					(*openIter)->parent = startNode;
				}
			}
			else if (obstacleIter == obstacles.end() && closeIter == closeNodes.end())
			{
				tempNode->parent = startNode;
				tempNode->Init(GetLengthNodes(tempNode, startNode), GetDistanceNodes(tempNode, goalNode));

				openNodes.insert(tempNode);

				if (tempNode == goalNode)
				{
					return tempNode;
				}
			}
		}
	}
	return nullptr;
}

Node* GetShortNode()
{
	Node* shortNode = nullptr;
	for (std::set<Node*>::iterator iter = openNodes.begin(); iter != openNodes.end(); iter++)
	{
		if (shortNode == nullptr)
			shortNode = (*iter);
		else if (shortNode->totalDistance > (*iter)->totalDistance)
			shortNode = (*iter);
	}
	return shortNode;
}

void ReFlexiveAstarFunc(Node* node)
{
	Node* tempNode = TrackingNode(node->x, node->y);

	if (tempNode != nullptr)
	{
		while (tempNode->parent != nullptr)
		{
			std::cout << tempNode->x << ", " << tempNode->y << std::endl;
			tempNode = tempNode->parent;
		}
		return;
	}

	ReFlexiveAstarFunc(GetShortNode());
}

float GetDistanceNodes(Node* node1, Node* node2)
{
	float distance = 0;
	float x = node2->x - node1->x;
	float y = node2->y - node1->y;

	if (x != 0)
		distance += abs(x);
	if (y != 0)
		distance += abs(y);

	return distance;
}

float GetLengthNodes(Node* node1, Node* node2)
{
	float x = node2->x - node1->x;
	float y = node2->y - node1->y;

	return sqrt(x * x + y * y);
}