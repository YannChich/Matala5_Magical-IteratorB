#include "doctest.h"
#include "sources/MagicalContainer.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test addElement() and getSize() methods") {
    ariel::MagicalContainer magicalContainer;
    CHECK(magicalContainer.size() == 0);
    magicalContainer.addElement(5);
    CHECK(magicalContainer.size() == 1);
    magicalContainer.addElement(2);
    CHECK(magicalContainer.size() == 2);
    magicalContainer.addElement(5); // Test adding a duplicate value.
    CHECK(magicalContainer.size() == 2); // Size shouldn't increase as 5 already exists.
}

TEST_CASE("Test removeElement() method") {
    ariel::MagicalContainer magicalContainer;
    magicalContainer.addElement(5);
    magicalContainer.addElement(2);
    CHECK(magicalContainer.size() == 2);
    magicalContainer.removeElement(2);
    CHECK(magicalContainer.size() == 1);
    magicalContainer.removeElement(3); // Test removing a non-existing value.
    CHECK(magicalContainer.size() == 1); // Size shouldn't decrease as 3 didn't exist.
}

TEST_CASE("Test AscendingIterator") {
    ariel::MagicalContainer magicalContainer;
    magicalContainer.addElement(5);
    magicalContainer.addElement(3);
    magicalContainer.addElement(4);
    magicalContainer.addElement(1);
    magicalContainer.addElement(2);

    ariel::MagicalContainer::AscendingIterator it(magicalContainer);
    CHECK(*it.begin() == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(it == it.end()); // Check if iterator reaches end
}

TEST_CASE("Test SideCrossIterator") {
    ariel::MagicalContainer magicalContainer;
    magicalContainer.addElement(1);
    magicalContainer.addElement(2);
    magicalContainer.addElement(4);
    magicalContainer.addElement(5);
    magicalContainer.addElement(14);

    ariel::MagicalContainer::SideCrossIterator it(magicalContainer);
    CHECK(*it.begin() == 1);
    ++it;
    CHECK(*it == 14);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(*it == 4);
    ++it;
    CHECK(it == it.end()); // Check if iterator reaches end
}

TEST_CASE("Test PrimeIterator") {
    ariel::MagicalContainer magicalContainer;
    magicalContainer.addElement(1);
    magicalContainer.addElement(2);
    magicalContainer.addElement(4);
    magicalContainer.addElement(5);
    magicalContainer.addElement(14);

    ariel::MagicalContainer::PrimeIterator it(magicalContainer);
    CHECK(*it.begin() == 2);
    ++it;
    CHECK(*it == 5);
    ++it;
    CHECK(it == it.end()); // Check if iterator reaches end
}

TEST_CASE("Test Exception Handling") {
    ariel::MagicalContainer magicalContainer;
    magicalContainer.addElement(1);
    magicalContainer.addElement(2);
    magicalContainer.addElement(4);
    magicalContainer.addElement(5);
    magicalContainer.addElement(14);

    // The removeElement method should throw an exception if we try to remove a non-existent element
    CHECK_THROWS(magicalContainer.removeElement(20));

    // We assume the PrimeIterator begin() method should throw an exception if there are no prime numbers in the container
    ariel::MagicalContainer::PrimeIterator primeIter(magicalContainer);
    magicalContainer.removeElement(2);
    magicalContainer.removeElement(5);
    CHECK_THROWS(primeIter.begin());

    // Similarly, AscendingIterator begin() should throw an exception if the container is empty
    ariel::MagicalContainer::AscendingIterator ascIter(magicalContainer);
    magicalContainer.removeElement(1);
    magicalContainer.removeElement(4);
    magicalContainer.removeElement(14);
    CHECK_THROWS(ascIter.begin());
}

