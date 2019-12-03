#ifndef _TABLE_H_
#define _TABLE_H_

#include <stdexcept>

namespace customTemplates {

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

		Table(Table<T>&& t) : arr(t.arr) { t.arr = nullptr; }

		~Table() { delete[] arr; }

		Table<T>& operator =(const Table<T>& t) {
			if (&t == this) return *this;
			delete arr;
			arr = new T[t.size];
			*arr = *t.arr;
			return *this;
		}

		Table<T>& operator =(Table<T>&& t) {
			if (&t == this) return *this;
			delete arr;
			arr = t.arr;
			t.arr = nullptr;
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
		
		void remove(const T& item) {
			int i = getPos(item);
			if (i == -1) return;
			for (int j = i; j < size; j++) arr[j] = arr[j + 1];
			size--;
		}


		const T& operator[] (int index) {
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

		Table<T> operator ++(int) {
			TableIt<T> res(*this);
			++cur;
			return res;
		}

	};


	




}


#endif