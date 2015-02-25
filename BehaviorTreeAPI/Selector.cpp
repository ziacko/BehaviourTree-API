#include <BehaviourTree.h>

bool Selector::Execute(double DeltaTime)
{
#if defined(_MSC_VER)
	for each(auto Iter in Children)
#else
	for (auto Iter : Children)
#endif
	{
		//if ANY children return true then return true and ignore any other children
		// OR gate
		if (Iter->Execute(DeltaTime))
		{
			return true;
		}
	}
	//if all children fail then return fail
	return false;
}