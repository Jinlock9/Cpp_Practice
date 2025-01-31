#include <iostream>
#include <new>
// g++ -std=c++17 -Wall -Wextra -Werror -pedantic main.cpp -o main

/**************************************************
 * SMART POINTERS *********************************
 **************************************************/

#include <memory>
class Simple {
    int ID;
public:
    int THING;
    Simple(int ID, int THING) : ID(ID), THING(THING) {}
    int getID() {
        return ID;
    }
    void doSth() {
        std::cout << ID << " Did!" << std::endl;
    }
};

template <typename T>
class Foo {
public:
    Foo(std::unique_ptr<T> data) : m_data { std::move(data) } {}
private:
    std::unique_ptr<T> m_data;
};

void notLeaky() {
    auto ptr1 = std::make_unique<Simple>(0, 0);
    std::unique_ptr<Simple> ptr2 { new Simple(0, 0) };
}

int* myAlloc(int value) { return new int { value }; }
void myFree(int* p) { delete p; }

void close(FILE* filePtr) {
    if (filePtr == nullptr) return;
    fclose(filePtr);
    std::cout << "File closed." << std::endl;
}

void useResource(std::weak_ptr<Simple>& weakSimple) {
    auto resource = weakSimple.lock();
    if (resource) {
        std::cout << "Resource still alive." << std::endl;
    } else {
        std::cout << "Resouce has been freed!" << std::endl;
    }
}

std::unique_ptr<Simple> create() {
    auto ptr = std::make_unique<Simple>(7, 0);
    return ptr;
}

class Foo1 : public std::enable_shared_from_this<Foo1> {
public:
    std::shared_ptr<Foo1> getPointer() {
        return shared_from_this();
        // return std::shared_ptr<Foo1>(this) <- WRONG
    }
};
 
int main() {
    /**********************/
    /*** UNIQUE POINTER ***/
    /**********************/

    notLeaky();
    auto ptr0 = std::make_unique<Simple>(1, 0);
    ptr0->doSth();
    (*ptr0).doSth();

    ptr0.reset();
    ptr0.reset(new Simple{2, 0});
    ptr0->doSth();

    Simple* simple = ptr0.release();
    simple->doSth();
    delete simple;
    simple = nullptr;

    auto ptr1 { std::make_unique<Simple>(3, 0) };
    Foo foo0 { std::move(ptr1) };

    auto arr0 = std::make_unique<int[]>(10);
    arr0[1] = 123;

    // std::unique_ptr<int, decltype(&myFree)*> ptr2(myAlloc(42), myFree);

    /**********************/
    /*** SHARED POINTER ***/
    /**********************/

    auto ptr2 { std::make_shared<Simple>(4, 0) };
    auto ptr3 = ptr2;
    std::cout << ptr3.use_count() << std::endl;
    ptr2->doSth();
    ptr3->doSth();

    // Custom delete
    FILE* f = fopen("data.txt", "w");
    std::shared_ptr<FILE> filePtr { f, close };
    if (filePtr == nullptr) std::cerr << "Error Opening File." << std::endl;
    else std::cout << "File opened." << std::endl;

    auto ptr4 { std::make_shared<Simple>(5, 55) };
    auto aliasing {std::shared_ptr<int> { ptr4, &ptr4->THING }};
    ptr4->doSth();
    std::cout << *aliasing << std::endl;

    auto shareSimple = std::make_shared<Simple>(6, 100);
    std::weak_ptr<Simple> weakSimple = shareSimple;
    useResource(weakSimple);
    shareSimple.reset();
    useResource(weakSimple);

    std::unique_ptr<Simple> ptr5 = create();
    auto ptr6 { create() };
    ptr5->doSth();
    ptr6->doSth();

    auto ptr7 = std::make_shared<Foo1>();
    auto ptr8 = ptr7->getPointer();

    return 0;
}

/**************************************************
 * C Style Memory Management **********************
 **************************************************/

// void leaky() {
//     new int; // <- Memory Leak. (Returned pointer by new is ignored.)
// }

// void legacy() {
//     int** handle = nullptr;
//     handle = new int*;
//     *handle = new int;
//     delete *handle; *handle = nullptr;
//     delete handle; handle = nullptr;
//     /*
//      *  < stack >    < free store >
//      *   
//      *    handle  ->  [          ] : *handle
//      *                     |
//      *                     v
//      *                [          ] : **handle
//      */

//     int* ptr0 = new int;
//     delete ptr0;
//     ptr0 = nullptr;

//     int* ptr1 = new(std::nothrow) int; // new that returns nullptr instead of exception when it fails
//     delete ptr1;

//     int arr0[5];
//     /*
//      *      < stack >          < free store >
//      *  arr0[0] : [   ?   ]
//      *  arr0[1] : [   ?   ]
//      *  arr0[2] : [   ?   ]                
//      *  arr0[3] : [   ?   ]
//      *  arr0[4] : [   ?   ]
//      */

//     int arr1[5] { };
//     /*
//      *      < stack >          < free store >
//      *  arr1[0] : [   0   ]
//      *  arr1[1] : [   0   ]
//      *  arr1[2] : [   0   ]                
//      *  arr1[3] : [   0   ]
//      *  arr1[4] : [   0   ]
//      */

//     int* arr2 = new int[5];
//     /*
//      *      < stack >            < free store >
//      *    arr2 [      ]  ----> [   ?   ] : arr2[0]
//      *                         [   ?   ] : arr2[1]
//      *                         [   ?   ] : arr2[2]
//      *                         [   ?   ] : arr2[3]
//      *                         [   ?   ] : arr2[4]
//      */
//     delete[] arr2;

//     char board[3][3] {};
//     /*
//      *       < stack >              < free store >
//      *  board[0][0] : [   0   ]  
//      *  board[0][1] : [   0   ]
//      *  board[0][2] : [   0   ]                
//      *  board[1][0] : [   0   ]
//      *  board[1][1] : [   0   ]
//      *  board[1][2] : [   0   ]
//      *  board[2][0] : [   0   ]
//      *  board[2][1] : [   0   ]
//      *  board[2][2] : [   0   ]
//      */
// }   

// char** allocate2Darray(size_t xDim, size_t yDim) {
//     char** arr = new char*[xDim];
//     for (size_t i = 0; i < xDim; i++) {
//         arr[i] = new char[yDim];
//     }
//     return arr;
// }
// void release2Darray(char**& arr, size_t xDim) {
//     for (size_t i = 0; i < xDim; i++) {
//         delete[] arr[i];
//         arr[i] = nullptr;
//     }
//     delete[] arr;
//     arr = nullptr;
// }

// template<size_t N>
// void doubleIntsStack(int (&arr)[N]) {
//     for (size_t i = 0; i < N; i++) arr[i] *= 2;
// }