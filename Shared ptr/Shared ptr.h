#pragma once

template<class T>
class sharedptr
{
private:
	T* ptr = nullptr;
	int* count = nullptr;

public:
	sharedptr() = default;

	sharedptr(T* ptr) {
		this->ptr = ptr;
		count = new int(1);
	}

	sharedptr(const sharedptr& obj) {
		this->ptr = obj.ptr;
		this->count = obj.count;
		if (obj.ptr)
			(*count)++;
	}

	sharedptr& operator=(const sharedptr& obj) {
		(*count)--;
		if (*count == 0)
		{
			if (nullptr != ptr)
				delete ptr;
			delete count;
		}
		ptr = obj.ptr;
		count = obj.count;
		if (nullptr != obj.ptr)
			(*count)++;
	}

	sharedptr& operator=(sharedptr&& dyingObj) {
		(*count)--;
		if (*count == 0)
		{
			if (nullptr != ptr)
				delete ptr;
			delete count;
		}

		ptr = dyingObj.ptr;
		count = dyingObj.count;

		dyingObj.ptr = nullptr;
		dyingObj.count = nullptr;
	}

	int getCount() const { return *count; }

	T* get() const { return ptr; }

	T* operator->() const { return ptr; }

	T& operator*() const { return ptr; }

	~sharedptr()
	{
		(*count)--;
		if (*count == 0)
		{
			if (nullptr != ptr)
				delete ptr;
			delete count;
		}
	}
};