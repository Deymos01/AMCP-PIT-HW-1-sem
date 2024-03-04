#ifndef OP_TASK10_ROMANFILES_DEYMOS01_STACK_HPP
#define OP_TASK10_ROMANFILES_DEYMOS01_STACK_HPP

template <typename T>
struct StackObj {
  T dataObj;
  StackObj<T> *next = nullptr;
};

template <typename T>
struct stack {
 private:
  StackObj<T> *top = nullptr;

 public:
  bool empty() { return (top == nullptr); }

  void push(const T &elem) {
    StackObj<T> *newObj = new StackObj<T>;
    newObj->dataObj = elem;
    newObj->next = top;
    top = newObj;
  }

  T pop() {
    if (this->empty()) {
      throw -1;
    }
    StackObj<T> *tmpObj = top;
    T tmpObjData = tmpObj->dataObj;
    top = tmpObj->next;
    delete tmpObj;
    return tmpObjData;
  }
};
#endif  // OP_TASK10_ROMANFILES_DEYMOS01_STACK_HPP
