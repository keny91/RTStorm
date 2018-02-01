

class Effect
{
	
};


// abstract class; use it as the parent model for the rest
class modifier
{

	public:
	//
	void* reference;   // class/struct that has this mod associated
	ModifierType type;  // 
	
	
	protected:   // children will have these defined
	
	
	virtual int applyModifier (int value);
	virtual int modifyValue (int amount);
	virtual bool reachedCap();
	virtual void *getParent() = 0;  // pure virtual -> must be redifined 
	// dpending on the child we know which is our type of parent (type of pointer returning)
	
	//private:	// no-sense to declare any privates in the parent
	
};


class AttackModifier : protected modifier 
{

}

