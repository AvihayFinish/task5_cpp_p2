#pragma once
#include <vector>

namespace ariel {

    class MagicalContainer {
        private:
            std::vector<int> cont;
            std::vector<int*> forPrimes;
            std::vector<int*> forSide;
            std::vector<int>::size_type sizeOfCont;
            bool isPrime (int num);
        public:
            MagicalContainer ();
            void addElement (int ind);
            void removeElement (int ind);
            std::vector<int>::size_type size ();

            class AscendingIterator {
                private:
                    int* pointToCurr;
                    MagicalContainer* mag;
                public:
                    // ctors and dtor
                    AscendingIterator (MagicalContainer& cont);
                    AscendingIterator (AscendingIterator& other);
                    ~AscendingIterator ();
                    AscendingIterator (AscendingIterator&& other) noexcept;
                    AscendingIterator& operator= (AscendingIterator&& other) noexcept;
                    AscendingIterator& operator= (const AscendingIterator& other);

                    // bool functions
                    bool operator== (const AscendingIterator& other) const;
                    bool operator!= (const AscendingIterator& other) const;
                    bool operator< (const AscendingIterator& other) const;
                    bool operator> (const AscendingIterator& other) const;

                    // other functions
                    int operator* () const;
                    AscendingIterator& operator++ ();
                    const AscendingIterator operator++ (int);
                    AscendingIterator begin ();
                    AscendingIterator end ();
            };

            class SideCrossIterator {
                private:
                    std::vector<int>::size_type index;
                    MagicalContainer* mag;
                public:
                    // ctors and dtor
                    SideCrossIterator (MagicalContainer& cont);
                    SideCrossIterator (SideCrossIterator& other);
                    ~SideCrossIterator();
                    SideCrossIterator(SideCrossIterator&& other) noexcept;
                    SideCrossIterator& operator=(SideCrossIterator&& other) noexcept;
                    SideCrossIterator& operator= (const SideCrossIterator& other);

                    //bool functions
                    bool operator== (const SideCrossIterator& other) const;
                    bool operator!= (const SideCrossIterator& other) const;
                    bool operator< (const SideCrossIterator& other) const;
                    bool operator> (const SideCrossIterator& other) const;

                    // other functions
                    int operator* () const;
                    SideCrossIterator& operator++ ();
                    const SideCrossIterator operator++ (int);
                    SideCrossIterator begin ();
                    SideCrossIterator end ();
            };

            class PrimeIterator {
                private:
                    std::vector<int>::size_type index;
                    MagicalContainer* mag;
                public:
                    // ctors and dtor
                    PrimeIterator (MagicalContainer& cont);
                    PrimeIterator (PrimeIterator& other);
                    ~PrimeIterator();
                    PrimeIterator(PrimeIterator&& other) noexcept;
                    PrimeIterator& operator=(PrimeIterator&& other) noexcept;
                    PrimeIterator& operator= (const PrimeIterator& other);

                    // bool functions
                    bool operator== (const PrimeIterator& other) const;
                    bool operator!= (const PrimeIterator& other) const;
                    bool operator< (const PrimeIterator& other) const;
                    bool operator> (const PrimeIterator& other) const;

                    // other functions
                    int operator* () const;
                    PrimeIterator& operator++ ();
                    const PrimeIterator operator++ (int);
                    PrimeIterator begin ();
                    PrimeIterator end ();
            };
    };
}