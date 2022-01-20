// Created by Tyler Starling on 5/23/2021.
// COP4530

#include <iostream>
#include <string>

#include "tvector.h"

using namespace std;

/*
int main(){
    //  Testing default and 2 param constructors
    TVector< int > v1, v2, vEmptyTester;
    TVector< double > v3, v4, v100;
    TVector< char > v5('#', 10);

    //  Testing Print with the contents of v5
    cout << "\nThe contents of v5 are: ";
    v5.Print(cout, ' ');
    cout << "\nThe size of v5 is: " << v5.GetSize() << "\n\n";  //  Tests the GetSize function

    v5.Clear(); // Testing Clear on v5
    cout << "After the Clearing of v5's contents, v5 now contains: ";
    v5.Print(cout, ' ');
    cout << "\n";

    // Testing InsertBack on v1-v4 and populating the vectors with data
    for(int i = 0; i < 10; i++){
        v1.InsertBack(i*2);
        v2.InsertBack(i*3);
        v3.InsertBack(i*1.5);
        v4.InsertBack(i*2.5);
        v100.InsertBack(i*30.5);
    }

    //  Testing Print with the contents of v1
    cout << "\nThe contents of v1 are: ";
    v1.Print(cout, ' ');
    cout << "\nThe first element of v1 is: " << v1.GetFirst() << "\n";  //  Tests the GetFirst function

    //  Testing Print with the contents of v2
    cout << "\nThe contents of v2 are: ";
    v2.Print(cout, ' ');
    cout << "\nThe last element of v2 is: " << v2.GetLast() << "\n";    //  Tests the GetLast function

    //  Testing Print with the contents of v3
    cout << "\nThe contents of v3 are: ";
    v3.Print(cout, ' ');

    //  Testing Print with the contents of v4
    cout << "\nThe contents of v4 are: ";
    v4.Print(cout, ' ');
    cout << "\n\n";

    //  Testing IsEmpty
    cout << "This line will return 1 if the vEmptyTester is empty or 0 if it's not. We're expecting a 1. Here goes: " << vEmptyTester.IsEmpty() << "\n\n";

    //  Testing Copy Constructor
    cout << "Cloning v6 to match v1 using Copy Constructor";
    TVector< int > v6 = v1;
    cout << "\nThe contents of v6 are now: ";
    v6.Print(cout, ' ');
    cout << "\n\n";

    //  Testing Copy Assignment Operator
    cout << "Cloning v6 to match v2 using Copy Assignment Operator";
    v6 = v2;
    cout << "\nThe contents of v6 are now: ";
    v6.Print(cout, ' ');
    cout << "\n\n";

    //  Testing Move Constructor
    cout << "Creating v7 that equals v3+v4 using Move Constructor";
    TVector< double > v7 = v3 + v4;
    cout << "\nThe contents of v7 are now: ";
    v7.Print(cout, ' ');
    cout << "\n\n";

    //  Testing Move Assignment Operator
    cout << "Creating v7 that equals v3+v100 using Move Assignment Operator";
    v7 = v3 + v100;
    cout << "\nThe contents of v7 are now: ";
    v7.Print(cout, ' ');
    cout << "\n\n";

    //  Testing SetCapacity Function
    cout << "Changing the capacity of v1 from original to 50\n";
    v1.SetCapacity(50);

    //  Testing RemoveBack
    cout << "\nThe contents of v1 are: ";
    v1.Print(cout, ' ');
    cout << "Removing " << v1.GetLast() << " from v1\n";
    v1.RemoveBack();
    cout << "The contents of v1 are now: ";
    v1.Print(cout, ' ');
    cout << endl;

    cout << "\nThe contents of v3 are: ";
    v3.Print(cout, ' ');
    cout << "Removing the last 9 elements from v3\n";
    for(int i = 0; i < 9; i++){
        v3.RemoveBack();
    }
    cout << "The contents of v3 are now: ";
    v3.Print(cout, ' ');
    cout << endl;

    //  Creating Iterators for the test vectors
    TVectorIterator< int > v1Itr = v1.GetIterator();
    TVectorIterator< int > v1Itr2 = v1.GetIteratorEnd();
    TVectorIterator< int > v2Itr = v2.GetIterator();
    TVectorIterator< int > v2Itr2 = v2.GetIteratorEnd();
    TVectorIterator< double > v4Itr = v4.GetIterator();
    TVectorIterator< double > v4Itr2 = v4.GetIteratorEnd();

    //  Traverse iterator front to back of v1.
    cout << "\nThe contents of v1 are: ";
    v1.Print(cout, ' ');
    cout << "The size of v1 is: " << v1.GetSize();
    cout << "\nv1Itr is pointing at " << v1Itr.GetData() << "\n";
    cout << "Now traversing v1Itr front to back...\n";
    while(v1Itr.HasNext()){
        v1Itr.Next();
    }
    cout << "V1Itr is now pointing at " << v1Itr.GetData() << "\n\n";

    //  Traverse iterator back to front of v4.
    cout << "\nThe contents of v4 are: ";
    v4.Print(cout, ' ');
    cout << "The size of v4 is: " << v4.GetSize();
    cout << "\nv4Itr is pointing at " << v4Itr2.GetData() << "\n";
    cout << "Now traversing v4Itr back to front...\n";
    while(v4Itr2.HasPrevious()){
        v4Itr2.Previous();
    }
    cout << "V4Itr is now pointing at " << v4Itr2.GetData() << "\n\n";


    // Removal Testing
    cout << "\nThe contents of v2 are: ";
    v2.Print(cout, ' ');
    cout << "Lets remove " << v2Itr.GetData() << " up to (but not including) ";
    v2Itr2.Previous();
    v2Itr2.Previous();
    v2Itr2.Previous();
    v2Itr2.Previous();
    cout << v2Itr2.GetData() << ".\nRemoving now...";
    v2Itr = v2.Remove(v2Itr, v2Itr2);
    cout << "\nThe contents of v2 are now: ";
    v2.Print(cout, ' ');
    cout << "The size of v2 is now: " << v2.GetSize() << endl;

    // Insert Testing and Removal
    cout << "\nNow lets add 5 data elements to v2.";
    for(int i = 0; i < 5; i++){
        v2Itr = v2.Insert(v2Itr, i*4);
    }
    cout << "\nThe contents of v2 have been updated to: ";
    v2.Print(cout, ' ');
    cout << "The size of v2 is now: " << v2.GetSize() << endl;
    cout << "Not a big fan of that 12 in there.. lets get him out.\n";
    while(v2Itr2.HasNext()){
        v2Itr2.Next();
    }
    v2Itr2.Previous();
    v2Itr2.Previous();
    v2Itr2.Previous();
    v2Itr2.Previous();
    v2Itr2 = v2.Remove(v2Itr2);
    cout << "\nThe contents of v2 have been updated to: ";
    v2.Print(cout, ' ');
    cout << "The size of v2 is now: " << v2.GetSize() << endl;
    cout << "That's much better.\n";

    cout << "\nThe contents of v4 are: ";
    v4.Print(cout, ' ');
    cout << "Lets remove everything but the " << v4.GetLast() << "\nRemoving now...";
    for(int i = 0; i < 9; i++){
        v4Itr = v4.Remove(v4Itr);
        v4Itr.Previous();
    }
    cout << "\nThe contents of v4 have been updated to: ";
    v4.Print(cout, ' ');
    cout << "The size of v4 is now: " << v4.GetSize() << endl;
    cout << "\nInserting 5 data elements into v4 now.";
    v4Itr.Next();
    for(int i = 0; i < 5; i++){
        v4Itr = v4.Insert(v4Itr, i*4.5);
        v4Itr.Next();
    }
    cout << "\nThe contents of v4 have been updated to: ";
    v4.Print(cout, ' ');
    cout << "The size of v4 is now: " << v4.GetSize() << endl;


    //  Testing operator+ overload
    TVector< int > v10 = v1+v2;
    TVectorIterator< int > v10Itr = v10.GetIterator();
    TVectorIterator< int > v10Itr2 = v10.GetIteratorEnd();

    cout << "\nLets concatenate the contents of v1 and v2 and store them in a new vector (v10).";
    cout << "\nThe contents of v1 are: ";
    v1.Print(cout, ' ');
    cout << "The size of v1 is now: " << v1.GetSize();
    cout << "\nThe contents of v2 are: ";
    v2.Print(cout, ' ');
    cout << "The size of v2 is now: " << v2.GetSize() << endl;
    cout << "\nThe contents of v10 are: ";
    v10.Print(cout, ' ');
    cout << "The size of v10 is now: " << v10.GetSize() << endl << endl << endl;

    //  Prints updated contents of vectors
    cout << "\nHere are the updated vectors: ";
    cout << "\nThe contents of v1 are: ";
    v1.Print(cout, ' ');
    cout << "The size of v1 is now: " << v1.GetSize();
    cout << "\nThe contents of v2 are: ";
    v2.Print(cout, ' ');
    cout << "The size of v2 is now: " << v2.GetSize();
    cout << "\nThe contents of v3 are: ";
    v3.Print(cout, ' ');
    cout << "The size of v3 is now: " << v3.GetSize();
    cout << "\nThe contents of v4 are: ";
    v4.Print(cout, ' ');
    cout << "The size of v4 is now: " << v4.GetSize();
    cout << "\nThe contents of v10 are: ";
    v10.Print(cout, ' ');
    cout << "The size of v10 is now: " << v10.GetSize() << endl;

    //  Testing Removing from range
    cout << "\nRemoving the 6 up to, but not including, 14 in v1\n";
    while(v1Itr.HasPrevious()){
        v1Itr.Previous();
    }
    v1Itr.Next();
    v1Itr.Next();
    v1Itr.Next();
    v1Itr2.Previous();
    v1Itr = v1.Remove(v1Itr, v1Itr2);
    cout << "The contents of v1 are now: ";
    v1.Print(cout, ' ');
    cout << "The size of v1 is now: " << v1.GetSize() << endl;

    cout << "\nRemoving the first 5 elements in v10\n";
    while(v10Itr2.HasPrevious()){
        v10Itr2.Previous();
    }
    v10Itr2.Next();
    v10Itr2.Next();
    v10Itr2.Next();
    v10Itr2.Next();
    v10Itr2.Next();
    v10Itr = v10.Remove(v10Itr, v10Itr2);
    cout << "The contents of v10 are now: ";
    v10.Print(cout, ' ');
    cout << "The size of v1 is now: " << v10.GetSize() << endl;
    cout << "\nTesting Complete.\n";
}
*/
