//stl使用示例

#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    int ia[] = {27, 210, 12, 47, 109, 83, 40};
    vector<int, allocator<int> > vec(ia, ia + 7);

    cout << count_if(vec.begin(), vec.end(),
                     not1(bind2nd(less_equal<int>(), 40)));

    return 0;
}

// vector 是一个 STL 容器
// count_if 是一个 STL 演算法
// not1 和 bind2nd 都是 STL function adaptors
// less_equal<> 是一个 STL function object
// allocator<> 是一个 STL 记 忆体配置器
// vec.begin() 和 vec.end() 分别传回两个 iterator ，指向容器 vec 的头尾。