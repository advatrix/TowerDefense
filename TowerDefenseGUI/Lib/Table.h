#pragma once
#include <stdexcept>

namespace customTemplates {

	template<class T>
	class TableIt;

	template<class T>
	class Table {
		friend class TableIt<T>;
	private:
		T* arr;
		unsigned int size;
		unsigned int maxSize;
	public:
		Table() : size(0), maxSize(0), arr(nullptr) {}

		Table(const Table<T>& t) :
			size(t.size), maxSize(t.maxSize), arr(new T[t.maxSize]) {
			for (int i = 0; i < maxSize; i++) arr[i] = t.arr[i];
		}

		Table(Table<T>&& t) : arr(t.arr), size(t.size), maxSize(t.maxSize) { 
			t.arr = nullptr;
			t.size = 0;
			t.maxSize = 0;
		}

		~Table() { delete[] arr; }

		Table<T>& operator =(const Table<T>& t) {
			if (&t == this) return *this;
			delete arr;
			arr = new T[t.maxSize];
			*arr = *t.arr;
			size = t.size;
			maxSize = t.maxSize;
			return *this;
		}

		Table<T>& operator =(Table<T>&& t) {
			if (&t == this) return *this;
			delete arr;
			arr = t.arr;
			t.arr = nullptr;
			size = t.size;
			maxSize = t.maxSize;
			t.size = 0;
			t.maxSize = 0;
			return this;
		}

		int getPos(const T& t) const {
            for (int i = 0; i < size; i++) if (arr[i] == t) return i;
			return -1;
		}
		
		int insert(const T& item) {
			if (getPos(item) != -1) return 1;
			if (size == maxSize) {
				T* old = new T[maxSize + 1];
				for (int i = 0; i < maxSize; ++i) old[i] = arr[i];
				old[maxSize] = item;
				delete[] arr;
				arr = old;
				maxSize++;
			}
			else arr[size] = item;
			size++;
			return 0;
		}
		
		int remove(const T& item) {
			int i = getPos(item);
			if (i == -1) return 1;
			for (int j = i; j < size; j++) arr[j] = arr[j + 1];
			size--;
			return 0;
		}

		inline unsigned int getSize() const { return size; }
		inline unsigned int allocated() const { return maxSize; }

		/*
		T& operator[] (int index) {
			if (index < 0 || index >= size) throw std::invalid_argument("illegal index");
			return arr[index];
		}
		*/

		T operator[] (int index) const {
			if (index < 0 || index >= size) throw std::invalid_argument("illegal index");
			return arr[index];
		}

		typedef TableIt<T> Iterator;
		Iterator begin() { return Iterator(this->arr); }
		Iterator end() { return Iterator(this->arr + size); }
		Iterator find(const T& t) const {
			int i = getPos(t);
			if (i < 0) i = size;
			return Iterator(this->arr + i);
		}
	};

	template<class T>
	class TableIt {
	private:
		T* cur;
	public:
		TableIt() : cur(nullptr) {}
		TableIt(T* t) : cur(t) {}
		
		int operator != (const TableIt<T>& t) const { return cur != t.cur; }
		int operator == (const TableIt<T>& t) const { return cur == t.cur; }

		T& operator *() { return *cur; }
		T* operator ->() { return cur; }

		TableIt<T>& operator ++() {
			++cur;
			return *this;
		}

		TableIt<T> operator ++(int) {
			TableIt<T> res(*this);
			++cur;
			return res;
		}

		TableIt<T>& operator --() {
			--cur;
			return *this;
		}

		TableIt<T> operator --(int) {
			TableIt<T> res(*this);
			--cur;
			return res;
		}

		TableIt<T> operator +=(int i) {
			TableIt<T> res(*this);
			cur += i;
			return res;
		}

		TableIt<T> operator -=(int i) {
			TableIt<T> res(*this);
			cur -= i;
			return res;
		}

		TableIt<T> operator +(int i) {
			TableIt<T> res(*this);
            cur += i;
			return res;
		}

	};


	




}


