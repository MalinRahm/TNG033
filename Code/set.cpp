#include "set.hpp"

// Default constructor
Set::Set() 
{
	head = new Node(0, nullptr);
}

// Constructor for creating a set from an int
Set::Set(int v)
{
	head = new Node(0, nullptr);
	Node *newNode = new Node(v, head->next);
	head->next = newNode;
}

// Constructor creating a set
// a non-sorted array of n intgers
Set::Set(const int a[], int n) 
{
	head = new Node(0, nullptr);
	Node *Current = head;
	
	for (int i = 0; i < n; i++)
	{
		Node *NewNode = new Node(a[i], Current->next);
		Current->next = NewNode;
		Current = NewNode;
	}

}

// copy constructor
Set::Set(const Set& source) 
{
	Node *CurrentSourceNode = source.head;
	head = new Node(0, nullptr); //Our new set head
	Node *CurrentCopyNode = head;

	while (CurrentSourceNode->next)
	{
		CurrentSourceNode = CurrentSourceNode->next;
		CurrentCopyNode->next = new Node(CurrentSourceNode->value, CurrentCopyNode->next);
		CurrentCopyNode = CurrentCopyNode->next;
	}

}

// Destructor: deallocate all nodes
Set::~Set() 
{
	Node *NodeToDelete = head;

	while (NodeToDelete->next)
	{
		head = head->next;
		delete NodeToDelete;
		NodeToDelete = head;
	}

	NodeToDelete = nullptr;
	delete head;
}

// Test if set is empty
bool Set::empty() const 
{
	if (!head->next)
		return true;
	return true;
}

// Return number of elements in the set
int Set::cardinality() const 
{
	int counter = 0;
	Node *CurrentNode = head;

	while( CurrentNode->next )
	{
		CurrentNode = CurrentNode->next;
		counter++;
	}

	return counter;
}

// Test if x is an element of the set
bool Set::member(int x) const 
{
	Node *CheckNode = head;

	while (CheckNode->next)
	{
		CheckNode = CheckNode->next;
		if (CheckNode->value == x)
			return true;
	}

    return false; 
}

// Assignment operator
Set& Set::operator=(const Set& s)
{
	Set copy(s);
	swap(copy.head, head);
	
	return *this;  // to be deleted
}

bool Set::operator<=(const Set& b) const 
{
    if(empty() && b.empty())
        return true;
    else if(cardinality() > b.cardinality())
        return false;
    else if (cardinality() < b.cardinality())
    {
        return true;
    }
    else
    {
        if(b!=*this || b<*this)
            return false;
        return true;
    }
}

bool Set::operator==(const Set& b) const 
{
	Node *S1 = head;
	Node *S2 = b.head;

	if (b.cardinality() != cardinality())
		return false;

	while (S1->next)
	{
		S1 = S1->next;
		S2 = S2->next;
		if (S1->value != S2->value)
			return false;
	}

    return true; 
}

bool Set::operator!=(const Set& b) const 
{
	if (b == *this)
		return false;
    return true; 
}

bool Set::operator<(const Set& b) const
{
    if(cardinality() < b.cardinality())
        return true;
    else if (cardinality() > b.cardinality())
        return false;
    else if (empty() && b.empty())
        return false;
    else //if equal number of elements
    {
        Node *C1 = head;
        Node *C2 = b.head;
        for(int i = 0; i < cardinality(); i++)
        {
            if(C1->value < C2->value)
            {
                C2 = C2->next;
                C1 = C1->next;
            }
            else
                return false;  
        }
         return true;
    }
}


// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const 
{
	Set S;
    Node *S1 = head;
    Node *S2 = b.head;
    Node *Sunion = S.head;
    bool exists = false, exists2 = false;
    
    while (S1->next && S2->next)
    {
        if (!S.empty())
        {
            exists = S.member(S1->next->value);
            exists2 = S.member(S2->next->value);
        }
        
        if (S1->next->value < S2->next->value)
        {
            exists = S.member(S1->next->value);
            if(!exists)
            {
                Sunion->next = new Node(S1->next->value, nullptr);
                Sunion = Sunion->next;
            }
            S1 = S1->next;
        }
        else if (S2->next->value < S1->next->value)
        {
            if(!exists2)
            {
                Sunion->next = new Node(S2->next->value, nullptr);
                Sunion = Sunion->next;
            }
            S2 = S2->next;
        }
        else
        {
            if(!exists2)
            {
                Sunion->next = new Node(S2->next->value, nullptr);
                Sunion = Sunion->next;
            }
            S1 = S1->next;
            S2 = S2->next;
        }
    }
    
    if (S1->next)
    {
        while (S1->next)
        {
            exists = S.member(S1->next->value);
            if(!exists)
            {
                Sunion->next = new Node(S1->next->value, nullptr);
                Sunion = Sunion->next;
            }
            S1 = S1->next;
        }
    }
    
    if (S2->next)
    {
        while (S2->next)
        {
            exists2 = S.member(S2->next->value);
            if(!exists2)
            {
                Sunion->next = new Node(S2->next->value, nullptr);
                Sunion = Sunion->next;
            }
            S2 = S2->next;
        }
    }
    
    return S;
}

// Set intersection, all elements alike should be in new list
Set Set::operator*(const Set& b) const
{
    Set S;
    Node *S1 = head;
    Node *S2 = b.head;
    Node *Sintersect = S.head;
    
    while(S1->next)
    {
        while(S2->next)
        {
            if(S1->next->value == S2->next->value)
            {
                Sintersect->next = new Node(S1->next->value, nullptr);
                Sintersect = Sintersect->next;
            }
            S2 = S2->next;
        }
        S2 = b.head;
        S1 = S1->next;
    }
    
    return S;
}

// Set difference
Set Set::operator-(const Set& b) const 
{
    // Add code
    return *this;  // to be deleted
}

// Set union with set {x}
Set Set::operator+(int x) const 
{
    Node *S1 = head;
    
    while(S1->next)
    {
        if(S1->value == x)
            return *this;
        S1 = S1->next;
    }
    
    S1->next = new Node(x, nullptr);
    
    return *this;
}

// Set difference with set {x}
Set Set::operator-(int x) const 
{
    // Add code
    return *this;  // to be deleted
}



std::ostream& operator<<(std::ostream& os, const Set& theSet) 
{
	if (theSet.empty())
	{
		os << "Set is empty!";
	}
    else
	{
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp)
		{
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }

    return os;
}
