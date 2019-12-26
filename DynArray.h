#ifndef DYNARRAY_H_INCLUDED
#define DYNARRAY_H_INCLUDED
#include <iostream>

template <typename T>
class DynArray
{
	int capacity;
	int curSize;
	T* data;

    public:
	DynArray();
	DynArray(int size);
	~DynArray();
	DynArray(const DynArray&);
	DynArray& operator=(const DynArray&);

	DynArray(std::initializer_list<T> ilist);


    private:
	void CopyFrom(const DynArray&);
	void resize(int);

    public:
        void clean();

    public:
	const T& operator[](int) const;
	T& operator[](int);

	void pushBack(const T&);
	void popBack();

	void shrinkToFit();

	void insertAt(int, T);
	void removeAt(int);

	T& frontEl();
        const T& frontEl() const;

        T& backEl();
        const T& backEl() const;

	int getCapacity() const;
	int getCurSize() const;
	bool isEmpty() const;
};



template <typename T>
DynArray<T>::DynArray() : capacity(0), curSize(0), data(nullptr)
{}

template<typename T>
DynArray<T>::DynArray(int size) :
	data(new T[size]), curSize(0), capacity(size) {
	/*...*/
}

template<typename T>
DynArray<T>::DynArray(std::initializer_list<T> ilist):
	DynArray(ilist.size()) {

	// notice that we have called the constructor with "size"
	// parameter to allocate memory only once, not to resize
	// each time new element from the initializer list is added
	size_t i = 0;
	for (const T& el: ilist)    // for each element from the initializer list
		data[i++] = el;     // take its value and write it into our array
	curSize = (i) ? i - 1 : 0; // remember how much elements we have read
}

template<typename T>
DynArray<T>::~DynArray()
{
	clean();
}

template <typename T>
void DynArray<T>::CopyFrom(const DynArray & other)
{
	capacity = other.capacity;
	curSize = other.curSize;
	data = new T[capacity];
	for(int i = 0; i < capacity; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void DynArray<T>::resize(int newCap)
{
    T *temp = data;

	data = new T[newCap];

	for (int i = 0; i < curSize; i++)
		data[i] = temp[i];

	capacity = newCap;

    delete[] temp;
}

template <typename T>
void DynArray<T>::clean()
{
    delete[] data;

    capacity = 0;
    curSize = 0;
    data = nullptr;
}

template<typename T>
DynArray<T>::DynArray(const DynArray& other)
{
	CopyFrom(other);
}

template<typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& other)
{
	if (this != &other)
	{
        clean();
        CopyFrom(other);
    }
	return *this;
}

template<typename T>
void DynArray<T>::pushBack(const T& el)
{
    if (curSize == capacity)
	{
	    int newSize = (capacity == 0 ? 2 : capacity*2);
		resize(newSize);
	}
	data[curSize] = el;
	curSize++;
}


template<typename T>
void DynArray<T>::popBack()
{
	if (curSize == 0)
	{
		std::cout << "Empty array";
	}
	curSize--;
}

template<typename T>
void DynArray<T>::shrinkToFit()
{
	if (curSize == capacity)
	{
		return;
	}

	capacity = curSize;
	T* newData = new T[capacity];
	for (int i = 0; i < capacity; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

template<typename T>
void DynArray<T>::insertAt(int position, T element)
{
	if (position < 0 || position > capacity)
	{
		return;
	}

	if (capacity == curSize)
	{
		int newSize = (capacity == 0 ? 2 : capacity*2);
		resize(capacity);
	}

	for (int i = curSize; i >= position ; i--)
	{
		data[i] = data[i - 1];
	}
    data[position] = element;
}

template<typename T>
void DynArray<T>::removeAt(int idx)
{
	if (idx < 0 || idx > capacity)
	{
		std::cout << "Invalid index";
	}

	if (idx == curSize - 1 || curSize == 1)
	{
		popBack();
		return;
	}

	for (int i = idx; i < curSize; i++)
	{
		data[i] = data[i+1];
	}
	curSize--;
}

template<typename T>
const T& DynArray<T>::operator[](int idx) const
{
    if (idx >= curSize || idx < 0)
    {
        std::cout << "Out of range!!!";
    }
    return data[idx];
}

template<typename T>
T& DynArray<T>::operator[](int idx)
{
    return const_cast<T&>(
        static_cast<const DynArray&>(*this)[idx]);
}


template<typename T>
const T& DynArray<T>::backEl() const {
	return (*this)[curSize - 1];
}

template<typename T>
T& DynArray<T>::backEl() {
	return (*this)[curSize - 1];
}

template<typename T>
T& DynArray<T>::frontEl()  {
	return (*this)[0];
}

template<typename T>
const T& DynArray<T>::frontEl() const {
	return (*this)[0];
}



template<typename T>
int DynArray<T>::getCapacity() const
{
    return capacity;
}

template<typename T>
int DynArray<T>::getCurSize() const
{
    return curSize;
}

template<typename T>
bool DynArray<T>::isEmpty() const
{
    return curSize == 0;
}


#endif // DYNARRAY_H_INCLUDED
