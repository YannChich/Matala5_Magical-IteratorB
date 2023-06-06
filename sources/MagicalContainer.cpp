#include "MagicalContainer.hpp"
#include <math.h>
#include <stdexcept> 
/*
Help with https://cplusplus.com/reference/vector/vector/
*/
using namespace std;
using namespace ariel;

// O(n)
void MagicalContainer::updateAscending() {
    // I clean my vector of int* and update him
    this->Ascending_Container.clear();
    for (size_t i = 0; i < Container.size(); i++)
    {
        this->Ascending_Container.push_back(&this->Container[i]);
    }
}

// Prime is always sorted   O(n)
void MagicalContainer::updatePrime() {
    this->Prime_Container.clear();
    for (size_t i = 0; i < Container.size(); i++)
    {
        if(isPrime(this->Container[i]) == 1){
            this->Prime_Container.push_back(&this->Container[i]);
        }
    }

}
// We need to hold the begin and the end and alternate with this  O(n)
void MagicalContainer::updateCross() {
    this->Cross_Container.clear();
    size_t begin = 0;
    size_t end = this->Container.size() - 1;
    /*
    We are pointing the start and end. adding the begin and the end
    when begin == end we need to out and add the last element
    Example : 1 2 3
    begin 0 end 2 --> push 1 push 3 begin == end --out_while--> push 2   : 1 3 2
    Example : 1 2 3 4
    begin 0 end 3 --> push 1 push 4 begin=1 end=2 --> push 2 push 3 begin 2 end 1 --out_while--> 1 4 2 3
    we are not enter in the next if because 4%2 = 0
    */
    while (begin < end) {
        this->Cross_Container.push_back(&this->Container[begin]);
        this->Cross_Container.push_back(&this->Container[end]);  
        begin++;
        end--;
    }
    // if the size of the vector is odd
    if (begin == end && this->size()%2 != 0) {
        this->Cross_Container.push_back(&this->Container[begin]);
    }
}

// O(n)
int MagicalContainer::getIndex(int number) {
    if(isExist(number) == 0) return -1;
    for (size_t i = 0; i < this->size(); i++){
        if(this->Container[i] ==  number){
            return i;
        }
    }
    return -1;
}

// Chekc if a number is prime O(sqrt(n))
bool MagicalContainer::isPrime(int number) {
    if(number == 0 || number == 1) return false;
    if(number == 2) return true;
    for(int i = 2;i<=sqrt(number);i++){
        if((number % i) == 0){
            return false;
        }
    }
    return true;
}

// Check if the number is already in the Container O(n)
bool MagicalContainer::isExist(int number) {
    for (size_t i = 0; i < this->size(); i++)
    {
        if(this->Container[i] == number){
            return true;
        }
    }
    return false;
}
/*
When i add a new element on my Container i want to update the different vector of int* that i have
I want to check if the number is Prime / already exist
O(n)
*/
void MagicalContainer::addElement(int element) {
    // If the element already exists, return
    if (isExist(element)) {  // O(n)
        return;
    }
    
    // Find the appropriate position to insert the element
    auto begin = Container.begin();
    for (; begin != Container.end(); ++begin) {  //O(n)
        if (element < *begin) {
            break;
        }
    }
    
    // Insert the element at the appropriate position
    Container.insert(begin, element); // Linear complecity 
    
    // Update the other containers
    updateAscending(); // O(n)
    updatePrime(); // O(n)
    updateCross(); // O(n)
}

/*
To simplify the implementation, we will ignore the case where an iterator points to an element while we delete that element. 
In such a case, the iterator is no longer valid. There is no need to implement a solution for this situation; 
it's up to the programmer not to use it.
O(n)
*/
void MagicalContainer::removeElement(int element) {
    int index = getIndex(element); // O(n)
    // trying to remove nothing
    if (index == -1) {
        throw runtime_error("The element not exist");
    }

    // Remove the element from the original container
    // Linear on the number of elements erased (destructions) plus the number of elements after the last element deleted (moving). (cplusplus.com)
    Container.erase(Container.begin() + index); 
    // O(3n)
    updateAscending();
    updatePrime();
    updateCross();
    
}/*
We are now going to create every function of each Iterator
Every Iterator should work in O(1) in both memory and time complexity
Each function going to use the function of ::vector like end() and begin()
*/
// current going to be a ptr of the first element of Ascending_Container
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &Mcontainer): container(&Mcontainer), position(0) {
    this->current = container->Ascending_Container.begin();
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) {
    this->container = other.container;
    this->current = other.current;
    this->position = other.position;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this->container != other.container){
        throw runtime_error("Cannot assign iterators from different containers");
    }
    if (this != &other) {
        // copy the data members from the other object
        this->current = other.current;
        this->container = other.container;
        this->position = other.position;
    }
    // return the object
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return this->container == other.container && this->current == other.current && this->position == other.position;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}
// we need to check with number every iterator are pointing through vector<int*>
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
   return this->position > other.position;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
 
    return this->position < other.position;
}

int MagicalContainer::AscendingIterator::operator*() const {
// current is an iterator of int* so i need to use 2 * to get the value of the original Container
    return **current;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
// if the iterator is already the end we can't use ++ and need to throw runtime error
    if(this->current == this->container->Ascending_Container.end()){
        throw runtime_error("You are already at the end");
    }
// we need to increment the iterator 
    ++current;
    ++position;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
// we are using the constructor , he will return a new iterator that pointing to the begining of Ascending_vector
    AscendingIterator new_Iterator = AscendingIterator(*container);
    return new_Iterator;
}
// Creating a new iterator and using the function end of ::vector
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator new_Iterator = AscendingIterator(*container);
    new_Iterator.current = this->container->Ascending_Container.end();
    new_Iterator.position = this->container->size();
    return new_Iterator;
}

// current going to be a ptr of the first element of Ascending_Container
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &Mcontainer): container(&Mcontainer),position(0) {
    this->current = container->Cross_Container.begin();
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) {
    this->container = other.container;
    this->current = other.current;
    this->position = other.position;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    if (this->container != other.container){
        throw runtime_error("Cannot assign iterators from different containers");
    }
    if (this != &other) {
        // copy the data members from the other object
        this->current = other.current;
        this->container = other.container;
        this->position = other.position;
    }
    // return the object
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
    return this->container == other.container && this->current == other.current && this->position == other.position;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
    return !(*this == other);
}
// we need to check with number every iterator are pointing through vector<int*>
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {
   return this->position > other.position;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {
 
    return this->position < other.position;
}

int MagicalContainer::SideCrossIterator::operator*() const {
// current is an iterator of int* so i need to use 2 * to get the value of the original Container
    return **current;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
    if(this->current == this->container->Cross_Container.end()){
        throw runtime_error("You are already at the end");
    }
// we need to increment the iterator 
    ++current;
    ++position;
    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
// we are using the constructor , he will return a new iterator that pointing to the begining of Ascending_vector
    SideCrossIterator new_Iterator = SideCrossIterator(*container);
    new_Iterator.current = this->container->Cross_Container.begin();
    return new_Iterator;
}
// Creating a new iterator and using the function end of ::vector
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator new_Iterator = SideCrossIterator(*container);
    new_Iterator.current = this->container->Cross_Container.end();
    new_Iterator.position = this->container->size();
    return new_Iterator;
}

// current going to be a ptr of the first element of Ascending_Container
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &Mcontainer): container(&Mcontainer),position(0) {
    this->current = container->Prime_Container.begin();
}
MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) {
    this->container = other.container;
    this->current = other.current;
    this->position = other.position;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    if (this->container != other.container){
        throw runtime_error("Cannot assign iterators from different containers");
    }
    if (this != &other) {
        // copy the data members from the other object
        this->current = other.current;
        this->container = other.container;
        this->position = other.position;
    }
    // return the object
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
    return this->container == other.container && this->current == other.current && this->position == other.position;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
    return !(*this == other);
}
// we need to check with number every iterator are pointing through vector<int*>
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {
   return this->position > other.position;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {
 
    return this->position < other.position;
}

int MagicalContainer::PrimeIterator::operator*() const {
// current is an iterator of int* so i need to use 2 * to get the value of the original Container
    return **current;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {
    if(this->current == this->container->Prime_Container.end()){
        throw runtime_error("You are already at the end");
    }
// we need to increment the iterator 
    ++current;
    ++position;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
// we are using the constructor , he will return a new iterator that pointing to the begining of Ascending_vector
    PrimeIterator new_Iterator = PrimeIterator(*container);
    new_Iterator.current = this->container->Prime_Container.begin();
    return new_Iterator;
}
// Creating a new iterator and using the function end of ::vector
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    PrimeIterator new_Iterator = PrimeIterator(*container);
    new_Iterator.current = this->container->Prime_Container.end();
    new_Iterator.position = this->container->Prime_Container.size();
    return new_Iterator;
}


