#include "BehaviourTree.h"

Node::~Node()
{
	
}

bool Node::Execute(double DeltaTime)
{
	return true;
}

Node* Node::AddNode(Node* node)
{
	return nullptr;
}