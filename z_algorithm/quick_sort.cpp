#include <vector>

/*
快速排序使用分治法（Divide and conquer）策略来把一个序列（list）分为两个子序列（sub-lists）。步骤如下：

1. 从数列中挑出一个元素，称为“基准”（pivot）；

2. 分区（partition）: 遍历数列，比基准小的元素放左边，比它大的放右边。 于是此次分区结束后，该基准就处于数列的中间位置，其左边的数全比它小（称为小于子序列），右边的数全比它大（称为大于子序列），这样一次排序就造成了整体上的有序化；

3. 子序列排序: 将小于子序列和大于子序列分别继续快速排序；

4. 递归到最底部时，数列的大小是零或一，至此就都排序好了，递归结束。
*/
void quickSort(std::vector<int>& v, int left, int right)
{
    if (left >= right) {
        return;
    }

    int i = left;
    int j = right;

    int tmp = v[i];

    while (i < j) {
        while (i < j && v[j] > tmp) 
            --j;
        if (i < j) 
            v[i++] = v[j];

        while (i < j && v[i] < tmp) 
            ++i;
        if (i < j)
            v[j--] = v[i];
    }
    v[i] = tmp;

    quickSort(v, left, i - 1);
    quickSort(v, i + 1, right);
}

int main()
{
    std::vector<int> v{2, 5, 1, 8, 9, 6};
    quickSort(v, 0, v.size() - 1);
    return 0;
}
