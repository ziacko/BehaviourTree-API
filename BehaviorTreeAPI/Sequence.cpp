#include <BehaviourTree.h>

bool Sequence::Execute(double DeltaTime)
{
#if defined(_MSC_VER)
	for each (auto Iter in Children)
#else
	for (auto Iter : Children)
#endif
	{
		//if all children return true then return true. AND gate
		if (Iter->Execute(DeltaTime))
		{
			//keep going!
			return true;
		}

		else
		{
			return false;
		}
	}

	return false;
}