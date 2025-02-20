### 那么什么是排序
如果有一种方法能使集合从无序的状态转为有序的状态(从小到大依次排列/从大到小依次排列)，此方法称为**排序**
---
先看快排，这是速度最快的排序算法，比较实用。
## QuickSort(快速排序)
```cpp
void QuickSort(std::vector<int> &arr, size_t left, size_t right) {
  auto left_begin = left;//记录左右指针的初始形态
  auto right_end = right;
  auto temp = arr[left];//记录比较的标准
  if (right == left) {
    return;//递归退出的条件，毕竟此时该区间内元素不再可分
  }
  if (right - left == 1)//此时区间只剩下两个元素 
  {
    if (arr[left] > arr[right]) {
      std::swap(arr[left], arr[right]);
    }
    return;
  }
//left==right就是我们要插入temp的地方，同时跳出大while.
  while (left < right) {
    while (arr[right] >= temp && right > left) {
      right--;
    }//从right开始找第一个小于temp的元素
    if (right > left) {
      std::swap(arr[left], arr[right]);
    }
    left++;//交换元素后，left指针向后移动
    while (arr[left] <= temp && left < right) {
      left++;
    }//从left开始找第一个大于temp的元素
    if (left < right) {
      std::swap(arr[left], arr[right]);
    }
    right--;//交换元素后，right指针向前移动
  }
  arr[left] = temp;//while循环后，left=right
  QuickSort(arr, left_begin, left - 1);//递归处理左半部分
  QuickSort(arr, right + 1, right_end - 1);//递归处理右半部分
}
```
***
再来看看希尔排序算法，仅次于快排，也比较实用
## ShellSort(希尔排序)
```cpp
void ShellSort(std::vector<int> &arr, size_t step) {
  size_t length = arr.size();
  size_t temp{};//用为索引
  size_t index{};
  if (step == 0) {
    return;//递归出口
  }
  while (index < length / 2) {
    while (index + step <= length) {
      if (arr[index] > arr[index + step]) {
        std::swap(arr[index], arr[index + step]);
      }
      index += step;//求得此集合所有距离index为step的元素
    }//index更新为下一个元素
    index = ++temp;，//第一次是0，第二次就是1，就是数组的下标
  }
  ShellSort(arr, step - 1);//递归处理
}
```
***
再来看看稳定的堆排序，性价比适中
## HeapSort(堆排序)
```cpp
class heap {
public:
  void heap_sort(std::vector<int> &arr);
  void shift(std::vector<int> &arr, int length,int start);
private:
};
```
***
shift 函数就是构造第一次大顶排序条件

heap_sort函数就是用来堆排序的
***
```cpp
void heap::shift(std::vector<int> &arr, int length,int start) {
  int largest = start;//此时的节点下标
  int left = start * 2 + 1;//该节点的左孩子
  int right = start * 2 + 2;//节点的右孩子
  if (left < length && arr[start] < arr[left]) {
    largest = left;
  }
  if (right < length && arr[start] < arr[right]) {
    largest = right;
  }//两个if判断左右节点的最大值
  if (largest != start) {
    std::swap(arr[largest], arr[start]);//最大值与父节点交换
    shift(arr,length,largest);//交换后的新子节点要满足堆的性质，递归处理
  }
}

void heap::heap_sort(std::vector<int> &arr) {
  int index{};
for(index=arr.size()/2-1;index>=0;index--){
  shift(arr, arr.size(),index);
}//把堆中那个非叶子节点调整值堆顶
for(int i=arr.size()-1;i>0;i--)
{
  std::swap(arr[i],arr[0]);//与数组的最后一个节点交换
  shift(arr,i, 0);//与数组的最后一个节点交换后，此时不满足堆的性质，
}//注意length形参在不断减少一，也就是理论的数组长度。
}
```
是不是都比较简单，实际如果掌握这三种（十大排序算法中实用较高的，性能top级别的），差不多排序算过关了。当然不止步于此的话，建议自己去了解无妨。
---