#include <iostream>
#include "SmartPoint.h"
#include "TestUniquePtr.h"

using namespace std;

int main()
{
    //TestShared_ptr();

    //TestWeak_ptr();
    //TestWeak_ptrToShared();

    //TestShared_ptrUse();
  //  TesUnique_ptrByAccessObject();
    //TestUnique_ptrByConstructor();
    TestUnique_ptrByMove();
    getchar();
    return 0;
}