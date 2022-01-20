// Created by Tyler Starling on 5/23/2021.
// COP4530

#ifndef _TVECTOR_HPP
#define _TVECTOR_HPP

#include <iostream>

using namespace std;

//  default constructor
template <typename T>
TVector < T >::TVector() {
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity];
}

// double parameter constructor that takes in number of copies of the data element val
template <typename T>
TVector < T >::TVector(T val, int num){
    capacity = num + SPARECAPACITY;
    size = num;
    array = new T[capacity];
    for(int i = 0; i < size; i++){
        array[i] = val;
    }
}

//  destructor
template <typename T>
TVector < T >::~TVector(){  //  cleaning it up
    if(size != 0){
        delete [] array;
    }
}

// copy constructor
template <typename T>
TVector < T >::TVector(const TVector<T>& v){
    Copier(v);  //  calls for a deep copy
}

// copy assignment operator
template <typename T>
TVector < T >& TVector < T >::operator=(const TVector<T>& v){
    if(this != &v){
        delete[] array; // clean up old array
        Copier(v);  //  calls for a deep copy
    }

    return *this;   //  returns the calling object
}

// move constructor
template <typename T>
TVector< T >::TVector(TVector&& v){
    capacity = v.capacity;
    size = v.size;
    array = v.array;

    v.array = 0;
}

// move assignment operator
template <typename T>
TVector < T >& TVector < T >::operator=(TVector<T>&& v){
    capacity = v.capacity;
    size = v.size;
    T* temp = array;
    array = v.array;
    v.array = temp;

    return *this;
}

// checks to see if the container is empty; returns true if so
template <typename T>
bool TVector < T >::IsEmpty() const{
    return !size;   //  genius.
}

//  clears out the vector and resets it to empty
template <typename T>
void TVector < T >::Clear(){    //  resets the vector back to the default constructor
    capacity = SPARECAPACITY;
    size = 0;
    array = new T[capacity];
}

//  returns the size of the vector
template <typename T>
int TVector < T >::GetSize() const {
    return size;    //  it matters
}

//  inserts data as the last item in the container
template <typename T>
void TVector < T >::InsertBack(const T &d) {
    if(size >= capacity){   //  Checks for growth need
        Grow(); //  Gets bigger
        array[size++] = d;  //  Increments size and inserts the new data
    }else{
        array[size++] = d;  //  Increments size and inserts the new data
    }
}

//  removes the last element in the container; leave empty is IsEmpty = true
template <typename T>
void TVector < T >::RemoveBack(){
    if(!IsEmpty())
        size--; //  :( it matters
}

//  returns the first data element in the vector (by reference)
template <typename T>
T& TVector < T >::GetFirst() const {
    if(!IsEmpty()){ //  Runs if the vector has a size > 0
        return array[0];
    }else{
        return dummy;   //  bad data return
    }
}

//  returns the last data element in the vector (by reference)
template <typename T>
T& TVector < T >::GetLast() const {
    if(!IsEmpty()){ //  Runs if the vector has a size > 0
        return array[size - 1];
    }else{
        return dummy;   //  bad data return
    }
}

//  Creates and returns an iterator that is positioned on the first item in the vector; empty returns default iterator
template <typename T>
TVectorIterator<T> TVector < T >::GetIterator() const{
    TVectorIterator< T > newItr;    //  Creates a new iterator for return purposes
    if(!IsEmpty()){ //  Updates the iterator to point at the beginning of the container if it's not empty
        newItr.index = 0;
        newItr.vsize = size;
        newItr.ptr = &array[0];
    }
    return newItr;
}

//  Creates and returns an iterator that is positioned on the last item in the vector; empty returns default iterator
template <typename T>
TVectorIterator<T> TVector < T >::GetIteratorEnd() const{
    TVectorIterator< T > newItr;    //  Creates a new iterator for return purposes
    if(!IsEmpty()){ //  Updates the iterator to point to the end of the container if it's not empty
        newItr.index = size - 1;
        newItr.vsize = size;
        newItr.ptr = &array[size - 1];
    }
    return newItr;
}

//  Change the vector's capacity to the parameter value
template <typename T>
void TVector < T >::SetCapacity(unsigned int c){
    if(c > capacity){   // Growing Capacity
        capacity = c;
        T* newVector = new T[capacity]; //  deep copy with the new capacity
        for(int i = 0; i < size; i++){
            T t = array[i];
            newVector[i] = t;
        }
        delete [] array;    //  clean up that old stuff
        array = newVector;  //  set our array equal to the new data
    }else if(c < capacity){ //  Decreasing Capacity
        if(c < size){   //  Decreasing Size
            size = capacity;
        }else{
            capacity = c;
        }
    }
}

//  Inserts the new data element (2nd param) just before the pos value in the vector
//  If the container is empty, insert single item, if iterator doesn't refer to valid spot, insert at end of container
//  Returns an iterator to the newly inserted item
template <typename T>
TVectorIterator<T> TVector < T >::Insert(TVectorIterator<T> pos, const T& d){
    TVectorIterator< T > returnIterator;

    if(IsEmpty()){  //  case for container being empty
        InsertBack(d);  //  inserts the data at the back (start of the container, because empty)
        return GetIterator();   //  returns the iterator at the beginning of the container
    }else{
        //  this where the juice happens
        if(pos.index >= size){  //  niche case where the iterator isn't referring to a valid spot
            InsertBack(d);  //  inserts the data at the end of the container
            return GetIteratorEnd();    //  returns the iterator at the end of the container
        }else{  //  case for a valid insert at pos
            TVector< T > tempVector;    //  creates a temporary vector
            for(int i = 0; i < pos.index; i++){ //  populates the temp vector with the first bit of data
                tempVector.InsertBack(array[i]);
            }
            tempVector.InsertBack(d);   //  inserts the d at the correct position specified
            for(int i = pos.index; i < size; i++){  //  populates the temp vector with the rest of the data
                tempVector.InsertBack(array[i]);
            }
            TVectorIterator< T > tempIterator = tempVector.GetIterator();   //  creates a temp iterator that points to the beginning of the temp vector

            Clear();    //  clears our container

            while(tempIterator.HasNext()){  //  adds the new data from the temp vector to the original container
                InsertBack(tempIterator.GetData());
                tempIterator.Next();
            }
            returnIterator = GetIterator(); //  sets the returnIterator equal to the beginning of the container
            for(int i = 0; i < pos.index; i++){ //  iterates through the container to the new value's position
                returnIterator.Next();
            }
            return returnIterator;  //  returns the iterator at the new value's position
        }
    }
}

//  Removes the data item that is given by the position parameter
//  Returns an iterator to the next data item; if empty, return default iterator
template <typename T>
TVectorIterator<T> TVector < T >::Remove(TVectorIterator<T> pos){
    TVectorIterator< T > returnIterator;
    if(IsEmpty()){
        return returnIterator;
    }else{
        TVector< T > tempVector;    //  creates a temporary vector
        returnIterator = GetIterator();  //  points the returnIterator to the start of the container
        for(int i = 0; i < pos.index; i++){ //  populates the temp vector with the first bit of data
            tempVector.InsertBack(array[i]);
            returnIterator.Next();
        }
        returnIterator.Next();
        for(int i = pos.index + 1; i < size; i++){  //  skips over the data to be removed and populates the rest
            tempVector.InsertBack(array[i]);
        }
        Clear();
        for(int i = 0; i < tempVector.size; i++){   //  fills up the container with the tempVector data
            InsertBack(tempVector.array[i]);
        }
        return returnIterator;  //  returns the iterator at the new value's position
    }
}

//  Removes the data items in the range that starts as the first iterator (pos1), up through
//  but not including (pos2). Returns an iterator to the next data item; if empty
//  return default iterator. If first iterator is after second iterator, return first iterator (pos1).
template <typename T>
TVectorIterator<T> TVector < T >::Remove(TVectorIterator<T> pos1, TVectorIterator<T> pos2){
    TVectorIterator< T > returnIterator;
    if(IsEmpty()){  //  Nothing to delete; return default iterator
        return returnIterator;
    }else if(pos1.index > pos2.index){  //  first pos is after 2nd pos, just returns the first iterator (pos1)
        return pos1;
    }else{
        TVector< T > tempVector;    //  creates a temporary vector
        returnIterator = GetIterator();  //  points the returnIterator to the start of the container
        for(int i = 0; i < pos1.index; i++){ //  populates the temp vector with the first bit of data
            tempVector.InsertBack(array[i]);
            returnIterator.Next();
        }
        for(int i = pos1.index; i < pos2.index; i++){
            returnIterator.Next();
        }
        for(int i = pos2.index; i < size; i++){  //  skips over the data to be removed and populates the rest
            tempVector.InsertBack(array[i]);
        }
        Clear();
        for(int i = 0; i < tempVector.size; i++){   //  fills up the container with the tempVector data
            InsertBack(tempVector.array[i]);
        }
        return returnIterator;  //  returns the iterator at the new value's position
    }
}

//  prints the contents of the vector in order, separated by delimiter
template <typename T>
void TVector < T >::Print(ostream& os, char delim) const{
    for(int i = 0; i < size; i++){
        if(i < size - 1){
            os << array[i] << delim;
        }else{
            os << array[i];
        }
    }
    os << endl;
}

//  operator+ overload that returns a TVector object that is the result of the concatenation of two TVector objects
template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2){
    TVector < T > returnVector; //  Creates a new vector for return purposes
    TVectorIterator< T > t1Iterator, t2Iterator;    //  Creates 2 iterator vectors
    t1Iterator = t1.GetIterator();  //  Sets the first iterator vector equal to the beginning of t1
    t2Iterator = t2.GetIterator();  //  Sets the second iterator vector equal to the beginning of t2

    while(t1Iterator.HasNext()){    //  Populates the returnVector with the t1 vector's data
        returnVector.InsertBack(t1Iterator.GetData());
        t1Iterator.Next();
    }
    while(t2Iterator.HasNext()){    //  Populates the returnVector with the t2 vector's data
        returnVector.InsertBack(t2Iterator.GetData());
        t2Iterator.Next();
    }

    return returnVector;    //  Returns the concatenated vector
}

// deep copy function
template <typename T>
void TVector< T >::Copier(const TVector <T>& v){
    capacity = v.capacity;
    size = v.size;
    array = new T[capacity];
    for(int i = 0; i < size; i++){
        array[i] = v.array[i];
    }
}

// grow function
template <typename T>
void TVector< T >::Grow(){
    capacity *= 2;
    T* newVector = new T[capacity];

    for(int i = 0; i < size; i++){
        T t = array[i];
        newVector[i] = t;
    }

    delete [] array;
    array = newVector;
}

/*********** TVectorIterator Definitions ************/
//  default constructor for the TVectorIterator class (null iterator)
template <typename T>
TVectorIterator< T >::TVectorIterator(){
    ptr = nullptr;
    index = 0;
    vsize = 0;
}

//  returns true if there is another data element after the current one, false otherwise
template <typename T>
bool TVectorIterator< T >::HasNext() const{
    if(index == vsize){
        return false;
    }else{
        if(index < vsize){
            return true;
        }
    }
    return false;
}

//  returns true if there is another data element before the current one, false otherwise
template <typename T>
bool TVectorIterator < T >::HasPrevious() const{
    return (index > 0);
}

//  advances the iterator to the next data element after the current one, unless storing nullptr
//  returns an iterator to the new position
template <typename T>
TVectorIterator< T > TVectorIterator < T >::Next(){
    TVectorIterator< T > newItr;
    if(HasNext()) {      // if more data exists in vector, return iterator pointing to next datum
        newItr.ptr = ++ptr;
        newItr.index = ++index;
    }
    return newItr;
}

//  advances the iterator to the previous data element before the current one, unless storing nullptr
//  returns an iterator to the new position
template <typename T>
TVectorIterator< T > TVectorIterator < T >::Previous(){
    TVectorIterator< T > newItr;
    if(HasPrevious()){      // if more data exists "to the left" in vector, return iterator pointing to next datum
        newItr.ptr = --ptr;
        newItr.index = --index;
    }
    return newItr;
}

//  returns the data item at the current iterator position; if iterator is not pointing to valid spot(nullptr)
//  return dummy (return by reference)
template <typename T>
T& TVectorIterator< T >::GetData() const {
    if(ptr != nullptr){
        return *ptr;
    }else{
        return TVector< T >().dummy;
    }
}

#endif
