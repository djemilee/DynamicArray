#ifndef DYNARRAY_H_INCLUDED
#define DYNARRAY_H_INCLUDED
#include <iostream>
#include <stdexcept>

template <typename T>
class DynArray
{
	int capacity;
	int cur_size;
	T* data;

    public:
		DynArray();
		DynArray(int size);
		~DynArray();
		DynArray(const DynArray&);
		DynArray& operator=(const DynArray&);

		DynArray(std::initializer_list<T> ilist);


///******************************************************************************************************
    public:
        /* iterator */
        /// very basic random access iterator
        /// @note a better implementation will give a const_iterator, too
        class iterator {
        private:
            T* elem_ptr; //!< pointer to a element from the array

        public:
            typedef iterator                  self_type;
            typedef T                         value_type;
            typedef T&                        reference;
            typedef T*                        pointer;
            typedef int                       difference_type;

            /** Basic iterator constructor - points to an element from the array */
            iterator(pointer e = NULL) : elem_ptr(e){}

        public:
            //@{
            /** access operators */
            reference operator*(){
                return *elem_ptr;
            }
            pointer operator->(){
                return elem_ptr;
            }
            reference operator[](size_t i){
                return  *(elem_ptr + i);
            }
            //@}

            //@{
            /** compare operators */
            bool operator==(const self_type& rhs) const{
                return elem_ptr == rhs.elem_ptr;
            }
            bool operator!=(const self_type& rhs) const{
                return !(rhs == *this);
            }
            bool operator<(const self_type& rhs) const{
                return elem_ptr < rhs.elem_ptr;
            } // compare the addresses
            bool operator>(const self_type& rhs) const{
                return (rhs < *this);
            }
            bool operator<=(const self_type& rhs) const{
                return !(*this > rhs);
            }
            bool operator>=(const self_type& rhs) const{
                return !(*this < rhs);
            }
            //@}

            //@{
            /** modifier operators */
            self_type& operator++() {

                ++elem_ptr;
                return *this;
            }

            self_type operator++(int) {

                self_type res(*this);
                ++(*this);
                return res;
            }

            self_type& operator--() {

                --elem_ptr;
                return *this;
            }

            self_type operator--(int) {

                self_type res(*this);
                --(*this);
                return res;
            }

            self_type& operator+=(int i) {

                difference_type m = i;
                if (m >= 0) while (m--) ++elem_ptr; // forward moving
                else        while (m++) --elem_ptr; // backward moving
                return *this;
            }

            self_type operator+(int i) const {

                self_type res(*this);
                return res += i;
            }

            self_type& operator-=(int i) {

                return *this+=(-i);
            }

            self_type operator-(int i) const {

                self_type res(*this);
                return res -= i;
            }
            //@}

            /// calculates difference between two iterators
            difference_type operator-(const self_type& rhs) const {
                return elem_ptr - rhs.elem_ptr;
            }
        };

    ///*********************************************************************************************

    public:
        /* iterator */
        /// very basic forward iterator
        /// @note a better implementation will give a const_iterator, too
        class forward_iterator {
        private:
            T* elem_ptr; //!< pointer to a element from the array

        public:
            typedef forward_iterator          self_type;
            typedef T                         value_type;
            typedef T&                        reference;
            typedef T*                        pointer;
            typedef int                       difference_type;

            /** Basic iterator constructor - points to an element from the array */
            forward_iterator(pointer e = NULL) : elem_ptr(e){}

        public:
            //@{
            /** access operators */
            reference operator*(){
                return *elem_ptr;
            }
            pointer operator->(){
                return elem_ptr;
            }
            //@}

            //@{
            /** compare operators */
            bool operator==(const self_type& rhs) const{
                return elem_ptr == rhs.elem_ptr;
            }
            bool operator!=(const self_type& rhs) const{
                return !(rhs == *this);
            }
            //@}

            //@{
            /** modifier operators */
            self_type& operator++() {

                ++elem_ptr;
                return *this;
            }

            self_type operator++(int) {

                self_type res(*this);
                ++(*this);
                return res;
            }
        };
///***********************************************************************************************

	private:
		void copy_from(const DynArray&);
		void resize(int);
        void clean();

		iterator binary_search(const T& el, int left, int right) const;
        iterator linear_search(const T& el) const;

	public:
	    const T& operator[](int) const;
	    T& operator[](int);

		void push_back(const T&);
		void pop_back();

		void shrink_to_fit();

		void insert_at(int, T);
		void remove_at(int);

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

		int get_capacity() const;
		int get_cur_size() const;
		bool empty() const;

        void print_elems(std::ostream& os) const;


        iterator find(const T& el, bool is_sorted = false) const;
        iterator begin(){
            return iterator(data);
        }

        /** Get iterator to the end of the array */
        iterator end(){
            return iterator(data + cur_size);
        }

        // constant iterator objects. they have limited usage
        // in our implementation, much better is to create
        // another class: const_iterator
        /** Get constant iterator to the beginning of the array */
        const iterator cbegin() const {
            return iterator(data);
        }

        /** Get constant iterator to the end of the array */
        const iterator cend() const {
            return iterator(data + cur_size);
        }



        forward_iterator fbegin(){
            return forward_iterator(data);
        }

        /** Get iterator to the end of the array */
        forward_iterator fend(){
            return forward_iterator(data + cur_size);
        }

        /** Get constant iterator to the beginning of the array */
        const forward_iterator cfbegin() const {
            return forward_iterator(data);
        }

        /** Get constant iterator to the end of the array */
        const forward_iterator cfend() const {
            return forward_iterator(data + cur_size);
        }
};



template <typename T>
DynArray<T>::DynArray() : capacity(0), cur_size(0), data(NULL)
{}

template<typename T>
DynArray<T>::DynArray(std::initializer_list<T> ilist):
	DynArray(ilist.size()) {

	// notice that we have called the constructor with "size"
	// parameter to allocate memory only once, not to resize
	// each time new element from the initializer list is added
	size_t i = 0;
	for (const T& el: ilist){    // for each element from the initializer list
		data[i++] = el;         // take its value and write it into our array
    }
	cur_size = (i) ? i - 1 : 0; // remember how much elements we have read
}

template<typename T>
DynArray<T>::DynArray(int size) :
	data(new T[size]), cur_size(0), capacity(size) {
	/*...*/
}

template<typename T>
DynArray<T>::~DynArray(){
	clean();
}

template <typename T>
void DynArray<T>::copy_from(const DynArray & other){
	capacity = other.capacity;
	cur_size = other.cur_size;
	data = new T[capacity];
	for(int i = 0; i < capacity; i++)
	{
		data[i] = other.data[i];
	}
}

template <typename T>
void DynArray<T>::clean(){
    delete[] data;

    capacity = 0;
    cur_size = 0;
    data = NULL;
}

template<typename T>
DynArray<T>::DynArray(const DynArray& other){
	copy_from(other);
}

template<typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other){
	if (this != &other){
        clean();
        copy_from(other);
    }
	return *this;
}

template<typename T>
void DynArray<T>::push_back(const T& el){
    if (cur_size == capacity){
	    int newSize = (capacity == 0 ? 2 : capacity*2);
		resize(newSize);
	}
	data[cur_size] = el;
	cur_size++;
}


template<typename T>
void DynArray<T>::pop_back(){
	if (cur_size == 0){
		throw std::logic_error("Already empty dynamic array");
	}
	cur_size--;
}

template<typename T>
void DynArray<T>::shrink_to_fit(){
	if (cur_size == capacity){
		return;
	}

	capacity = cur_size;
	T* newData = new T[capacity];
	for (int i = 0; i < capacity; i++){
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

template<typename T>
void DynArray<T>::insert_at(int position, T element){
	if (position < 0 || position > capacity){
		return;
	}

	if (capacity == cur_size){
		int newSize = (capacity == 0 ? 2 : capacity*2);
		resize(capacity);
	}

	for (int i = cur_size; i >= position ; i--){
		data[i] = data[i - 1];
	}
    data[position] = element;
}

template<typename T>
void DynArray<T>::remove_at(int idx){
	if (idx < 0 || idx > capacity){
		throw std::out_of_range("Out of range!!!");
	}

	if (idx == cur_size - 1 || cur_size == 1){
		pop_back();
		return;
	}

	for (int i = idx; i < cur_size; i++){
		data[i] = data[i+1];
	}
	cur_size--;
}

template<typename T>
void DynArray<T>::resize(int newCap){
    T *temp = data;

	data = new T[newCap];

	for (int i = 0; i < cur_size; i++){
		data[i] = temp[i];
	}
	capacity = newCap;

    delete[] temp;
}

template<typename T>
const T& DynArray<T>::operator[](int idx) const{
    if (idx >= cur_size || idx < 0){
        throw std::out_of_range("Out of range!!!");
    }
    return data[idx];
}

template<typename T>
T& DynArray<T>::operator[](int idx){
    return const_cast<T&>(
        static_cast<const DynArray&>(*this)[idx]);
}


template<typename T>
const T& DynArray<T>::back() const {
	return (*this)[cur_size - 1];
}

template<typename T>
T& DynArray<T>::back() {
	return (*this)[cur_size - 1];
}

template<typename T>
T& DynArray<T>::front()  {
	return (*this)[0];
}

template<typename T>
const T& DynArray<T>::front() const {
	return (*this)[0];
}


template<typename T>
int DynArray<T>::get_capacity() const{
    return capacity;
}

template<typename T>
int DynArray<T>::get_cur_size() const{
    return cur_size;
}

template<typename T>
bool DynArray<T>::empty() const{
    return cur_size == 0;
}

template<typename T>
typename DynArray<T>::iterator DynArray<T>::
	binary_search(const T& el, int left, int right) const {
	// there is no such element
	if (left > right)
		return cend();

	int med = (left + right) / 2;

	if (data[med] == el)
		return iterator(data + med);

	if (data[med] > el)
		return binary_search(el, left, med - 1);

	if (data[med] < el)
		return binary_search(el, med + 1, right);

	// won't reach this line, but added just to stop compiler's complaining
	return cend();
}

template<typename T>
typename DynArray<T>::iterator DynArray<T>::
	linear_search(const T& el) const {

	for (size_t i = 0; i < cur_size; i++){
		if (data[i] == el){
			return iterator(data + i);
		}
	}
	return cend();
}

template<typename T>
typename DynArray<T>::iterator DynArray<T>::find(const T& el, bool isSorted) const {

	if (isSorted){
		return binary_search(el, 0, cur_size); // O(logN)
	}
	return linear_search(el); // O(N)
}

template<typename T>
void DynArray<T>::print_elems(std::ostream& os) const {

	if (cur_size == 0) {
		os << "{}" << std::endl;
		return;
	}

	if (cur_size == 1) {
		os << '{' << data[0] << '}' << std::endl;
		return;
	}

	os << "{ ";
	for (size_t i = 0; i < cur_size - 1; i++)
		os << data[i] << ", ";
	os << data[cur_size - 1] << " }" << std::endl;
}

#endif // DYNARRAY_H_INCLUDED
