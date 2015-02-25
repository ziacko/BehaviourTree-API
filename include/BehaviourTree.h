#ifndef BEHAVIOR_TREE_H
#define BEHAVIOR_TREE_H 

#include <list>
#include <map>

enum BehaviourStatus
{
	FAILURE = 0, //is the node unsuccessful?
	SUCCESS, 
	RUNNING //is the node still running?
};

class Node
{
public:
	virtual bool Execute(double DeltaTime);
	virtual Node* AddNode(Node* node);
protected:
	virtual ~Node();
	Node* Parent;
};

class Composite : protected Node
{
protected:

	std::list<Composite*> Children;

};
/************************************************************************/
/*A Sequence will visit each child in order, starting with the first,
 * and when that succeeds will call the second, and so on down the list
 * of children. If any child fails it will immediately return failure 
 * to the parent. If the last child in the sequence succeeds, then the
 * sequence will return success to its parent. Analogous to an AND gate 
 * and requires all children to succeed to return a success. 
/************************************************************************/
class Sequence : public Composite
{
	bool Execute(double DeltaTime);
};

/************************************************************************/
/* A selector will return a success if any of its children succeed and not process
 * any further children. It will process the first child, and if it fails will
 * process the second, and if that fails will process the third, until a success
 * is reached, it which point it will instantly return success. It will fail if
 * all children fail. Analogous to an OR gate and can be used to check multiple
 * conditions too see if any one of them is true.
/************************************************************************/
class Selector : protected Composite
{
	bool Execute(double DeltaTime);
};

class Decorator : protected Node
{
protected:

	Node* Child;
};

/************************************************************************/
/* Will invert or negate the result of their child node. Success becomes
 *failure and failure becomes success.  
/************************************************************************/
class Inverter : protected Decorator
{

};

/************************************************************************/
/* A Succeeder will always return Success, irrespective of what the child 
* node actually returned. 
/************************************************************************/
class Succeeder : protected Decorator
{

};

/************************************************************************/
/* A repeater will reprocess the child its child returns a result. 
 * Repeaters may optionally run their children a set number of times
 * before returning to their parent. 
/************************************************************************/
class Repeater : protected Decorator
{

};

/************************************************************************/
/* Like a repeater, these decorators will continue to reprocess their child
* until the child returns a failure at which point the repeater will return 
* success to its parent
/************************************************************************/
class RepUntilFail : protected Decorator
{

};

/************************************************************************/
/* the lowest level node type and incapable of having any children.
* these are to defined and implemented by your project to do the specific 
* tests or actions. Leaf nodes are essentially game specific function
* calls that actually perform the task for your AI.
/************************************************************************/
class Leaf : protected Node
{
	/**
	 * called the first time a node is visited by its parent 
	 * during its parents execution. This function is used to 
	 * initialize the node and start the action the node represents.
	 */
	virtual bool Init(double DeltaTime);

	/**
	 * This is called every tick of the behavior while the node is 
	 * processing, If this function returns Success or Failure, then 
	 * the processing will end and the result will be passed to its 
	 * parent. If it returns Running it will be processed next tick
	 * again and again until it returns a Success or Failure 
	 */
	virtual bool Process(double Deltatime);
};


#endif
