#include "MagicalContainer.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace ariel;

MagicalContainer::MagicalContainer () : sizeOfCont(0) {}

bool MagicalContainer::isPrime (int num) {
    if (num < 2) {
        return false;
    }
    else if (num == 2) {
        return true;
    }
    for (int i = 2; i <= std::sqrt(num); i ++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void MagicalContainer::addElement (int ind) {
    if (this->sizeOfCont == 0) {
        this->cont.emplace_back(ind);
    }
    else {
        for (std::vector<int>::size_type i = 0; i < this->sizeOfCont; i++) {
            if (this->cont[i] < ind) {
                if (i == (this->sizeOfCont - 1)) {
                    this->cont.emplace_back(ind);
                    break;
                }
                continue;
            }
            auto it = this->cont.begin() + static_cast<std::vector<int>::difference_type>(i);
            this->cont.insert(it, ind);
            break;
        }
    }
    this->sizeOfCont++;
    // because when the capacity of the vector over, the vector could replace to another place
    this->forPrimes.clear();
    for (std::vector<int>::size_type i = 0; i < this->sizeOfCont; i++) {
        if (isPrime(this->cont[i])) {
            this->forPrimes.emplace_back(&this->cont[i]);
        }
    }
    this->forSide.clear();
    std::vector<int>::size_type i = 0;
    std::vector<int>::size_type j = this->sizeOfCont - 1;
    bool rondel = true;
    while (i <= j) {
        if (rondel) {
            this->forSide.emplace_back(&this->cont[i]);
            i++;
            rondel = false;
        }
        else {
            this->forSide.emplace_back(&this->cont[j]);
            j--;
            rondel = true;;
        }
    }
}

void MagicalContainer::removeElement (int ind) {
    bool exsit = false;
    for (std::vector<int>::size_type i = 0; i < this->cont.size(); i++) {
        if (this->cont[i] == ind) {
            this->cont.erase(this->cont.begin() + static_cast<std::vector<int>::difference_type>(i));
            this->sizeOfCont--;
            exsit = true;
        }
    }
    if (exsit) {
        this->forPrimes.clear();
        for (std::vector<int>::size_type i = 0; i < this->sizeOfCont; i++) {
            if (isPrime(this->cont[i])) {
                this->forPrimes.emplace_back(&this->cont[i]);
            }
        }
        this->forSide.clear();
        std::vector<int>::size_type i = 0;
        std::vector<int>::size_type j = this->sizeOfCont -1;
        bool rondel = true;
        while (i <= j) {
            if (rondel) {
                this->forSide.emplace_back(&this->cont[i]);
                i++;
                rondel = false;
            }
            else {
                this->forSide.emplace_back(&this->cont[j]);
                j--;
                rondel = true;;
            }
        }
    }
    else {
        throw runtime_error("this element dosent exist");   
    }
}

vector<int>::size_type MagicalContainer::size () {
    return this->sizeOfCont;
}

// ******************* ascending ************************
MagicalContainer::AscendingIterator::AscendingIterator (MagicalContainer& container) : pointToCurr(&container.cont[0]), mag(&container) {}

MagicalContainer::AscendingIterator::AscendingIterator (AscendingIterator& other) : pointToCurr(other.pointToCurr), mag(other.mag) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator::AscendingIterator (AscendingIterator&& other) noexcept: mag(other.mag), pointToCurr(other.pointToCurr) {
    other.pointToCurr = nullptr;
    other.mag = nullptr;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator= (AscendingIterator&& other) noexcept {
    if (this != &other) {
        this->mag = other.mag;
        this->pointToCurr = other.pointToCurr;
        other.mag = nullptr;
        other.pointToCurr = nullptr;
    }
    return *this;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator= (const AscendingIterator& other) {
    if (this != &other) {
        if (this->mag != other.mag && this->mag != nullptr && other.mag != nullptr) {
            throw runtime_error("the iterators needs to be from the same container");
        }
        this->mag = other.mag;
        this->pointToCurr = other.pointToCurr;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator== (const AscendingIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->pointToCurr == other.pointToCurr;
}

bool MagicalContainer::AscendingIterator::operator!= (const AscendingIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->pointToCurr != other.pointToCurr;
}

bool MagicalContainer::AscendingIterator::operator< (const AscendingIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->pointToCurr < other.pointToCurr;
}

bool MagicalContainer::AscendingIterator::operator> (const AscendingIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->pointToCurr > other.pointToCurr;
}

int MagicalContainer::AscendingIterator::operator* () const {
    return *this->pointToCurr;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++ () {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->pointToCurr == &this->mag->cont[this->mag->size()]) {
        throw runtime_error("you try to exceed from the container");
    }
    this->pointToCurr++;
    return *this;
}

const MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::operator++ (int) {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->pointToCurr == &this->mag->cont[this->mag->size()]) {
        throw runtime_error("you try to exceed from the container");
    }
    AscendingIterator asc(*this);
    this->pointToCurr++;
    return asc;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin () {
    AscendingIterator iter(*this->mag);
    iter.pointToCurr = &this->mag->cont[0];
    return iter;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end () {
    AscendingIterator iter(*this->mag);
    iter.pointToCurr = &this->mag->cont[this->mag->size()];
    return iter;
}

// ******************* sidecross ************************
MagicalContainer::SideCrossIterator::SideCrossIterator (MagicalContainer& container) : mag(&container), index(0) {}

MagicalContainer::SideCrossIterator::SideCrossIterator (SideCrossIterator& other) : mag(other.mag), index(other.index) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept: mag(other.mag), index(other.index) {
    other.index = 0;
    other.mag = nullptr;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator= (SideCrossIterator&& other) noexcept {
    if (this != &other) {
        this->mag = other.mag;
        this->index = other.index;
        other.mag = nullptr;
        other.index = 0;
    }
    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator= (const SideCrossIterator& other) {
    if (this != &other) {
        if (this->mag != other.mag && this->mag != nullptr && other.mag != nullptr) {
            throw runtime_error("the iterators needs to be from the same container");
        }
        this->mag = other.mag;
        this->index = other.index;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator== (const SideCrossIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index == other.index;
}

bool MagicalContainer::SideCrossIterator::operator!= (const SideCrossIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index != other.index;
}

bool MagicalContainer::SideCrossIterator::operator< (const SideCrossIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index < other.index;
}

bool MagicalContainer::SideCrossIterator::operator> (const SideCrossIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index > other.index;
}

int MagicalContainer::SideCrossIterator::operator* () const {
    return *this->mag->forSide[this->index];
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++ () {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->index == this->mag->forSide.size()) {
        throw runtime_error("you try to exceed from the container");
    }
    this->index++;
    return *this;
} 

const MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::operator++ (int) {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->index == this->mag->forSide.size()) {
        throw runtime_error("you try to exceed from the container");
    }
    SideCrossIterator sid(*this);
    sid.index = this->index;
    this->index++;
    return sid;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin () {
    return SideCrossIterator(*this->mag);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end () {
    SideCrossIterator iter(*this->mag);
    iter.index = this->mag->forSide.size();
    return iter;
}


// ******************* prime ************************
MagicalContainer::PrimeIterator::PrimeIterator (MagicalContainer& container) : index(0), mag(&container) {}

MagicalContainer::PrimeIterator::PrimeIterator (PrimeIterator& other) : index(other.index), mag(other.mag) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator (PrimeIterator&& other) noexcept: mag(other.mag), index(other.index) {
    other.mag = nullptr;
    other.index = 0;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator= (PrimeIterator&& other) noexcept {
    if (this != &other) {
        this->mag = other.mag;
        this->index = other.index;
        other.mag = nullptr;
        other.index = 0;
    }
    return *this;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator= (const PrimeIterator& other) {
    if (this != &other) {
        if (this->mag != other.mag && this->mag != nullptr && other.mag != nullptr) {
            throw runtime_error("the iterators needs to be from the same container");
        }
        this->mag = other.mag;
        this->index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator== (const PrimeIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index == other.index;
}

bool MagicalContainer::PrimeIterator::operator!= (const PrimeIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index != other.index;
}

bool MagicalContainer::PrimeIterator::operator< (const PrimeIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index < other.index;
}

bool MagicalContainer::PrimeIterator::operator> (const PrimeIterator& other) const {
    if (other.mag == nullptr || this->mag == nullptr) {
        throw runtime_error("one of the containers of this iterators not init yet");
    }
    return this->index > other.index;
}

int MagicalContainer::PrimeIterator::operator* () const {
    return *this->mag->forPrimes[this->index];
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++ () {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->index == this->mag->forPrimes.size()) {
        throw runtime_error("you try to exceed from the container");
    }
    this->index++;
    return *this;
}

const MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++ (int) {
    if (this->mag == nullptr) {
        throw runtime_error("this container dont init yet");
    }
    if (this->index == this->mag->forPrimes.size()) {
        throw runtime_error("you try to exceed from the container");
    }
    PrimeIterator pri(*this->mag);
    pri.index = this->index;
    this->index++;
    return pri;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin () {
    return PrimeIterator(*this->mag);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end () {
    PrimeIterator pri(*this->mag);
    pri.index = this->mag->forPrimes.size();
    return pri;
}
