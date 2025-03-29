
#include <iostream>
#include <memory>

class MylistIterator;
class Linklist;
class Node
{
   public:
    friend class Linklist;
    friend class MylistIterator;
    Node(int data, Node* next) : _data(data), _next(next) {}

   private:
    int _data;
    std::shared_ptr<Node> _next;
};

class MylistIterator{
        public:
        MylistIterator(std::shared_ptr<Node> cur):current(cur){}
        int &operator*(){return current->_data;}
         MylistIterator& operator++(){current=current->_next;
        return  *this;}
          MylistIterator operator++(int){
            auto temp=*this;
            current=current->_next;
            return temp;
          }
          bool  operator!=(const MylistIterator& other){return  current!=other.current;

          }
        
        private:
        std::shared_ptr<Node> current;
    };

class Linklist
{
    friend class MylistIterator;
   public:
    explicit Linklist() : head(nullptr), length(0) {}
    Linklist(const Linklist&) = delete;
    Linklist(Linklist&&) = delete;
    Linklist& operator=(const Linklist&) = delete;
    Linklist& operator=(Linklist&&) = delete;
    ~Linklist();
    void Insert(int key);
    std::shared_ptr<Node> GetTarget(int key);
    std::shared_ptr<Node> ReturnHead();
    void Print();
    void Delete(int key);
    int GetLength();
    void Destory(); 
    MylistIterator begin();
    MylistIterator end();
   private:
    std::shared_ptr<Node> head;
    int length;
};

 

Linklist::~Linklist() { /*Destory();*/ }
std::shared_ptr<Node> Linklist::ReturnHead() { return head; }

void Linklist::Insert(int key)
{
    auto new_node = std::make_shared<Node>(key, nullptr);
    if (head == nullptr)
    {
        head = new_node;
    }
    else
    {
        auto index = head;
        while (index->_next != nullptr)
        {
            index = index->_next;
        }
        index->_next = new_node;
    }
    length++;
}

[[nodiscard("can not ingore the returned")]]
std::shared_ptr<Node> Linklist::GetTarget(int key)
{
    auto current = head;
    if (current)
    {
        return current;
    }
    while (current->_data != key)
    {
        current = current->_next;
    }
    return current;
}

void Linklist::Print()
{
    auto cur = head;
    while (cur != nullptr)
    {
        std::cout << cur->_data << "->";
        cur = cur->_next;
    }
    std::cout << "nullptr" << '\n';
}

void Linklist::Delete(int key)
{
    if (!GetLength())
    {
        std::cout << "Delete Error" << '\n';
        return;
    }
    auto index = head;
    if (index->_data == key)
    {
        if (index->_next == nullptr)
        {
            index.reset();
            head = nullptr;
        }
        else
        {
            while ((index->_next->_data != key) && (index->_next != nullptr))
            {
                index = index->_next;
            }
            auto flag = index->_next;
            index->_next = flag->_next;
            flag->_next = nullptr;
            flag.reset();
        }
        length--;
    }
}

 MylistIterator Linklist::begin(){
return MylistIterator(head);
}

MylistIterator Linklist:: end(){
    return  MylistIterator(nullptr);
}

[[deprecated("it has deprecated")]] void Linklist::Destory()
{
    while (head)
    {
        auto temp = head;
        head = head->_next;
        temp.reset();
    }
    std::cout << "资源回收";
}
int Linklist::GetLength() { return length; }
int main()
{
    Linklist list;
    list.Insert(11);
    list.Delete(11);
    list.Insert(12);
    list.Insert(13);
    list.Insert(14);
    list.Print();
    std::cout << "the length of list " << list.GetLength()<<std::endl;
    for (auto it :list) {
    std::cout<<it<<"->";
    }
    std::cout<<"nullptr";
    return 0;
}
/*
这是基于c++98(后会稍有改动)的语言标准简单写的一个单链表，当然功能并不完善。
你也可以用c++11的标准来实现。最好不要手动释放内存，用RAII来管理会更好。
使用Clang在Vscode上面编译通过。GCC和MSVC应该也可以。
当然，如果支持Asan，可以试试clang++ -fsantize -g -std=c++xx target.cpp -o target
*/
