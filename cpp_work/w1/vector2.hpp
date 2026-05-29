#ifndef VECTOR_HPP
#define VECTOR_HPP
#include<cstddef>

template<typename T>
class vector {
private:
	T* data_=nullptr;
	std::size_t size_=0;
	std::size_t capacity_=0;
	void reallocate(size_t new_capacity);
	void swap(vector& m );


public:
	vector();
	explicit vector(size_t count);
	~vector();
	vector(const vector& other);
	vector& operator = (const vector & other);

	void push_back(const T& value);


	size_t size() const;
	size_t capacity() const;
	bool empty()const;


	T& operator[](size_t index);
	const T& operator[](size_t index)const;

};




template<typename T>
vector<T>::vector():data_(nullptr),size_(0),capacity_(0){}
template<typename T>
vector<T>::vector(size_t count):data_(new T[count]), size_(count), capacity_(count) {}

template<typename T>
void vector<T>::swap(vector& m)
{
	T* tmp_a = this->data_;
	this->data_ = m.data_;
	m.data_ =tmp_a;
	
	size_t tmp_b = this->capacity_;
	this->capacity_ = m.capacity_;
	m.capacity_ = tmp_b;
	size_t tmp_c = this->size_;
	this->size_ = m.size_;
	m.size_ = tmp_c;


}

template<typename T>
void vector<T>::reallocate(size_t new_capacity)
{
T* new_data = new T[new_capacity];
for(size_t i=0;i<this->size_;i++)
{
new_data[i]=data_[i];
}
delete[] this->data_;
this->data_=new_data;
this->capacity_=new_capacity;

}



template<typename T>
vector<T>:: ~vector()
{
delete[] data_;
}

template<typename T>
vector<T>::vector(const vector& other)
{
	this->reallocate(other.capacity_);
	for (size_t i = 0; i < other.size_; i++)
	{
		this->data_[i] = other.data_[i];
	}
		this->size_ = other.size_;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& other)
{
	if(this!=&other)
	{
	vector amp(other);
	swap(amp);
	}
	return *this;

}

template<typename T>
void vector<T>::push_back(const T& value)
{
if(this->capacity_==this->size_)
{
this->reallocate(this->capacity_*2+1);
}
this->data_[size_]=value;
this->size_+=1;
}

template<typename T>
size_t vector<T>::size()const
{
return this->size_;
}
template<typename T>
size_t vector<T>::capacity()const
{
return this->capacity_;
}

template<typename T>
bool vector<T>::empty()const
{

return this->size_==0;


}

template<typename T>
T& vector<T>::operator[](size_t index)
{
return this->data_[index];
}

template<typename T>
const T& vector<T>::operator[](size_t index) const
{
return this->data_[index];
}





#endif











