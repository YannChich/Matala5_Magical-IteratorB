#include "MagicalContainer.hpp"
#include <math.h>
#include <stdexcept> 

using namespace std;
using namespace ariel;


void MagicalContainer::updateAscending(int element) {

}

// Prime is always sorted 
void MagicalContainer::updatePrime(int element) {

}

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
*/
void MagicalContainer::addElement(int element) {
    // we are going to add the first element to our container
    if(this->size() == 0){
        this->Container.push_back(element);
    }
    // if the element arlready exist 
    if(isExist(element) == 1){
        return;
    }
    this->Container.push_back(element);
    // We now going to update each vector of ptr 
    updateAscending(element);
    updatePrime(element);
    // We are just adding the element in our vector , the iterator going to make the job
    Cross_Container.push_back(&Container[static_cast<size_t>(getIndex(element))]);

  
}
/*
To simplify the implementation, we will ignore the case where an iterator points to an element while we delete that element. 
In such a case, the iterator is no longer valid. There is no need to implement a solution for this situation; 
it's up to the programmer not to use it.
*/
void MagicalContainer::removeElement(int element) {
    int index = getIndex(element);
    // trying to remove nothing
    if (index == -1) {
        throw runtime_error("The element not exist");
    }

    // Remove the element from the original container
    Container.erase(Container.begin() + index);

    // Remove the element from the Ascending_Container, Prime_Container and Cross_Container
    // we are running into every vector and using erase (function in ::vector)
    for (auto it = Ascending_Container.begin(); it != Ascending_Container.end(); ++it) {
        if (**it == element) {
            Ascending_Container.erase(it);
            break;
        }
    }

    for (auto it = Prime_Container.begin(); it != Prime_Container.end(); ++it) {
        if (**it == element) {
            Prime_Container.erase(it);
            break;
        }
    }

    for (auto it = Cross_Container.begin(); it != Cross_Container.end(); ++it) {
        if (**it == element) {
            Cross_Container.erase(it);
            break;
        }
    }
}
// current going to be a ptr of the first element of Ascending_Container
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &Mcontainer) {
    this->container = &Mcontainer;
    this->current = container->Ascending_Container.begin();
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) {
    this->container = other.container;
    this->current = other.current;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other) {
    if (this != &other) {
        // copy the data members from the other object
        this->current = other.current;
        this->container = other.container;
    }
    // return the object
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
    return this->container == other.container && this->current == other.current;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
    return !(*this == other);
}
// we need to check with number every iterator are pointing through vector<int*>
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const {
   return current > other.current;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const {
 
    return current < other.current;
}

int MagicalContainer::AscendingIterator::operator*() const {
// current is an iterator of int* so i need to use 2 * to get the value of the original Container
    return **current;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() {
// we need to increment the iterator 
    ++current;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() {
// we are using the constructor , he will return a new iterator that pointing to the begining of Ascending_vector
    AscendingIterator new_Iterator = AscendingIterator(*container);
    new_Iterator.current = this->container->Ascending_Container.begin();
    return new_Iterator;
}
// Creating a new iterator and using the function end of ::vector
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() {
    AscendingIterator new_Iterator = AscendingIterator(*container);
    new_Iterator.current = this->container->Ascending_Container.end();
    return new_Iterator;
}

MagicalContainer::SideCrossIterator::SideCrossIterator() {

}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &Mcontainer) {

}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) {

}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {

}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other) {
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {

    return false;
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {

    return false;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const {

    return false;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const {

    return false;
}

int MagicalContainer::SideCrossIterator::operator*() const {

    return 0;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() {
    
    return SideCrossIterator();
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() {
    
    return SideCrossIterator();
}

MagicalContainer::PrimeIterator::PrimeIterator() {

}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &Mcontainer) {

}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) {

}

MagicalContainer::PrimeIterator::~PrimeIterator() {

}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other) {
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {

    return false;
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {

    return false;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const {

    return false;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const {

    return false;
}

int MagicalContainer::PrimeIterator::operator*() const {

    return 0;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() {

    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() {
    
    return PrimeIterator();
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() {
    
    return PrimeIterator();
}


