#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>
#include <utility>
#include <cassert> // This header is gained from Edge Copilot suggestion, it is used to assert the pointer is not null before dereferencing it.
// Your implementation here

template <typename T>
class UniquePtr {
  private:
    T* ptr;
  public:
    UniquePtr(T* ptr = nullptr):ptr(ptr) {

    }
    ~UniquePtr(){
      delete ptr;
    }
    UniquePtr(const UniquePtr& other) = delete;  // Disable copy constructor
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other): ptr(other.ptr) {
      other.ptr = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
      if (this != &other) {
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
      }
      return *this;
    }
    template<typename U>
    UniquePtr(UniquePtr<U>&& other): ptr(other.release()) {
    }
    T& operator*()const{
      assert(ptr != nullptr);
      return *ptr;
    }
    T* operator->() const
    {
        assert(ptr != nullptr);
        return ptr;
    }
    T* get() const
    {
        return ptr;
    }
    bool operator==(const UniquePtr<T>& other) const
    {
        return ptr == other.ptr;
    }
    T* release()
    {
        T* oldPtr = ptr;
        ptr = nullptr;
        return oldPtr;
    }
    void reset(T* newPtr = nullptr)
    {
        T* oldPtr = ptr;
        ptr = newPtr;
        delete oldPtr;
    }
    void swap(UniquePtr<T>& other)
    {
        T* temp = ptr;
        ptr = other.ptr;
        other.ptr = temp;
    }
    operator bool() const
    {
        return ptr != nullptr;
    }


};

/*
  The following function are autofilled by the VS Code copilot extension
  The role of this function is to auto new a UniquePtr object transfer the ownership of the pointer to the UniquePtr object and return it.
*/
template <typename T, typename... Args>
UniquePtr<T> makeUnique(Args&&... args)
{ 
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
#endif
