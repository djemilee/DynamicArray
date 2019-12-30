#include <iostream>
#include <random>
#include "DynArray.h"

#include <chrono>  // for high_resolution_clock

using namespace std;

void add_elements(){

    DynArray<int> proba;
    for(int i = 0; i < 10000; i++){
        proba.push_back(i);
    }

    proba.print_info(cout);
    cout << endl << endl;
}

void run_basic_tests() {

	std::cout //<< std::endl
	          //<< "--------------------------------------------"
			  << std::endl
	          << "running basic test"
			  << std::endl << std::endl;

	DynArray<int> first;
	std::cout << "array \"first\" :" << std::endl;
	first.print_info(std::cout);

	first.push_back(7);
	first.push_back(8);
	first.push_back(9);
	first.push_back(10);
	first.push_back(15);
	first.push_back(23);
	std::cout << endl << "after pushing back some elements :" << std::endl;
	first.print_info(std::cout);
	first.print_elems(std::cout);
	std::cout << std::endl;


	std::cout << "element on index 3 : " << first[3] << std::endl;
	std::cout << "size : " << first.get_cur_size()
			  << " cap : " << first.get_capacity()
			  << std::endl;

    first.pop_back();
	first.pop_back();
	std::cout << endl << "after popping back some elements :" << std::endl;
	first.print_info(std::cout);
	first.print_elems(std::cout);
	std::cout << std::endl;



	first.insert_at(2, 18);
	std::cout << endl << "after inserting element 18 in position 2:" << std::endl;
    first.print_info(std::cout);
	first.print_elems(std::cout);
	std::cout << std::endl;



	first.remove_at(3);
	std::cout << endl << "after removing the element in position 3:" << std::endl;
	first.print_info(std::cout);
	first.print_elems(std::cout);
	std::cout << std::endl;


	DynArray<int> second = first;
	std::cout << "array \"second\" a copy of \"first\" :" << std::endl;
	second.print_info(std::cout);
	second.print_elems(std::cout);

	std::cout << endl << "first element: " << first.front() << std::endl;
	std::cout << "last element: " << first.back() << std::endl;

}

void run_advanced_tests() {

	std::cout << std::endl
	          << "-----------------------------------------------------"
			  << std::endl
	          << "modern C++ tests"
			  << std::endl << std::endl;

	// create a test array with initializer list
	DynArray<int> f_arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	std::cout << "iterating over all elements using iterator based for :" << std::endl;
	for (DynArray<int>::iterator it = f_arr.begin(); it != f_arr.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;


	std::cout << "iterates all the elements from back to front using an iterator for:" << std::endl;
	for (DynArray<int>::iterator it = f_arr.end()-1; it != f_arr.begin()-1; --it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;


	std::cout << "iterating over all elements using forward_iterator based for :" << std::endl;
	for (DynArray<int>::forward_iterator it = f_arr.fbegin(); it != f_arr.fend(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl << std::endl;


	std::cout << "iterating over all elements using range based for :" << std::endl;
	for (int el: f_arr) {
		std::cout << el << " ";
	}
	std::cout << std::endl << std::endl;
}

int main()
{

    auto t1 = std::chrono::high_resolution_clock::now();
    add_elements();
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration;

    /* test 3 basic functionality */
	//run_basic_tests();

	/* test 4 advanced functionality */
	//run_advanced_tests();



    return 0;
}
