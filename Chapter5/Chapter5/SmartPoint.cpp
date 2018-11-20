#include "SmartPoint.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void TestShared_ptr()
{
    //Tow shared pointers representing two persons by their name
    shared_ptr<string> pNico(new string("nico"), [](string* p) {
        cout << "delete " << *p << endl;
        delete p;
    });
    shared_ptr<string> pJutta(new string("jutta"));

    //capitalize person names
    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    //put them multiple times in a container
    vector<shared_ptr<string>> whoMadCoffee;
    whoMadCoffee.push_back(pJutta);
    whoMadCoffee.push_back(pNico);
    whoMadCoffee.push_back(pJutta);
    whoMadCoffee.push_back(pNico);
    whoMadCoffee.push_back(pJutta);

    //print all elements
    for (auto ptr : whoMadCoffee)
    {
        cout << *ptr << "  ";
    }
    cout << endl;

    //overwrite a name again
    *pNico = "Nicolai";

    //print all element again
    for (auto ptr : whoMadCoffee)
    {
        cout << *ptr << "  ";
    }
    cout << endl;

    //print some internal data
    cout << "use_count: " << whoMadCoffee[0].use_count() << endl;
}

void TestShared_ptrByArray()
{
    shared_ptr<int> p(new int[10], [](int* p) {
        delete[] p;
    });

    shared_ptr<int> p1(new int[10], default_delete<int[]>());
}

void TsetShared_ptrByOtherDelete()
{
    class FileDeleter
    {
    private:
        string filename;
    public:
        FileDeleter(const string& strfn)
            : filename(strfn)
        {

        }

        void operator () (std::ofstream* fp)
        {
            fp->close();                //close file
            remove(filename.c_str());   //delete file
        }
    };

    //create and open temporary file
    shared_ptr<ofstream> fp(new ofstream("tmpfile.txt"), FileDeleter("tmpfile.txt"));
}



//////////////////////////////////////////////////////////////////////////
// This function should be runed on Unix/Linux
//class SharedMemoryDetacher
//{
//public:
//    void operator () (int* p)
//    {
//        cout << "unlink /tmp1234" << endl;
//        if (shm_unlink("/tmp1234") != 0)
//        {
//            cerr << "OOPS: shm_unlink() failed" << endl;
//        }
//    }
//};
//
//shared_ptr<int> getSharedIntMemory(int num)
//{
//    void* mem;
//
//    int shmfd = shm_open("/tmp1234", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
//    if (shmfd < 0)
//    {
//        throw string(strerror(errno));
//    }
//
//    if (ftrnucate(shmfd, num* sizeof(int) ) == -1 )
//    {
//        throw string(strerror(errno));
//    }
//
//    mem = mmap(nullptr, num * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmfd, 0);
//    if (mem == MAP_FAILED)
//    {
//        throw string(strerror(errno));
//    }
//
//    return shared_ptr<int>(static_cast<int*>(mem), SharedMemoryDetacher());
//}
//void TestShared_ptrBySharedMemory()
//{
//    //get and attach shared memory for 100 ints
//    shared_ptr<int> smp(getSharedIntMemory(100));
//
//    //init the shared memory
//    for (int i = 0; i < 100; ++i)
//    {
//        smp.get()[i] = i * 42;
//    }
//
//    //deal with shared memory somewhere else:
//    // ...
//    cout << "<return>" << endl;
//    cin.get();
//
//    //release shared memory here:
//    smp.reset();
//
//    // ...
//
//}



//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
class Person
{
public:
    string name;
    shared_ptr<Person> mother;
    shared_ptr<Person> father;
    vector<weak_ptr<Person>> kids;

    Person (const string& n, shared_ptr<Person> m = nullptr, shared_ptr<Person> f = nullptr)
        : name(n)
        , mother(m)
        , father(f)
    { }

    ~Person()
    {
        cout << "delete " << name << endl;
    }
};

shared_ptr<Person> initFamily(const string& name)
{
    shared_ptr<Person> mom(new Person(name + "'s mom"));
    shared_ptr<Person> dad(new Person(name + "'s dad"));
    shared_ptr<Person> kid(new Person(name, mom, dad));

    mom->kids.push_back(kid);
    dad->kids.push_back(kid);

    return kid;
}

void TestWeak_ptr()
{
    shared_ptr<Person> p = initFamily("nico");

    cout << "nico's family exists" << endl;
    cout << " - nico is shared " << p.use_count() << " times" << endl;
    cout << " - name of lst kid of nico's mom: " << p->mother->kids[0].lock()->name << endl;

    p = initFamily("Jim");
    cout << "jim's family exists" << endl;
}

void TestWeak_ptrToShared()
{
    try
    {
        shared_ptr<string> sp(new string("hi"));
        cout << sp.use_count() << endl;

        weak_ptr<string> wp = sp;
        cout << wp.use_count() << endl;

        sp.reset();
        cout << wp.use_count() << endl;

        cout << boolalpha << wp.expired() << endl;
    }
    catch(...)
    {

    }
}
