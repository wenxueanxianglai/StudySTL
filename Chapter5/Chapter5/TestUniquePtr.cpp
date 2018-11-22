#include "TestUniquePtr.h"

#include <memory>
#include <string>
#include <iostream>

using namespace std;

void TestUnique_ptrByAccessObject()
{
    //create and initalize(pointer to) string;
    unique_ptr<string> up(new string("nico"));

    (*up)[0] = 'N';         //replace first character
    up->append("lai");      //append some characters
    cout << *up << endl;    //print whole string
}

void TestUnique_ptrByConstructor()
{
   // unique_ptr<int> up = new int;       //ERROR
    unique_ptr<int> up(new int);
    unique_ptr<string> up1;
    up1 = nullptr;
    up.reset();

    unique_ptr<string> up3(new string("nico"));
    if (up3)    //if up3 is not empty
    {
        cout << *up3 << endl;
    }
    
    auto sp = up3.release();    //up3 loses ownership
    if (up3)    //if up3 is not empty
    {
        cout << *up3 << endl;
    }

    if (up3 != nullptr)    //if up3 is not empty
    {
        cout << *up3 << endl;
    }

    if (up3.get() != nullptr)    //if up3 is not empty
    {
        cout << *up3 << endl;
    }

}

void TestUnique_ptrByMove()
{
    //initialize a unique_ptr with a new object
    unique_ptr<string> up1(new string);

    //copy the unique_ptr
   // unique_ptr<string> up2(up1);     //ERROR: not possible

    //transfer ownership of the unique_ptr
    unique_ptr<string> up3(std::move(up1));     //OK


    //initialize a unique_ptr with a new object
    unique_ptr<int> up4(new int(4));
    unique_ptr<int> up5;     //create another unique_ptr

   // up5 = up4;                //ERROR: not possible

    up5 = std::move(up4);       //assign the unique_ptr
                                //transfer ownership from up4 to up5
    if (up4)
    {
        cout << *up4 << endl;
    }


}