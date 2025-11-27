#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // memcpy

int compare = 0; // 比较次数
int move = 0; // 移动次数


// 快速排序
int Partition(int arr[], int low, int high) {
    int pivot = arr[low]; // 选择基准元素

    while (low < high) {
        while (low < high && arr[high] >= pivot) { // 如果high的值大于等于基准值, 而且low<high
            high--; // high向前移动
            compare++;
        } // 一旦high的值小于基准值
        arr[low] = arr[high]; // 把high的值放到low的位置(放到前面去)
        move++;

        while (low < high && arr[low] <= pivot) { // 如果low的值小于等于基准值, 而且low<high
            low++; // low向后移动
            compare++;
        } // 一旦low的值大于基准值
        arr[high] = arr[low]; // 把low的值放到high的位置(放到后面去)
        move++;
    }

    arr[low] = pivot; // 把基准值放到low和high重合的位置(中间)
    move++;

    return low; // 返回中间值的下标, 以此来对中间值的左右分别进行快速排序(递归)
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) { // low>=high代表该子区域长度小于等于1, 不用排序
        int pos = Partition(arr, low, high); // 返回中间值位置
        QuickSort(arr, low, pos - 1); // 递归处理中间值左侧的子区间
        QuickSort(arr, pos + 1, high); // 递归处理中间值右侧的子区间
    }
}


// 二路归并
void merge(int arr[], int tempArr[], int left, int mid, int right) {
    int l_pos = left; // 左半区第一个元素
    int r_pos = mid + 1; // 右半区第一个元素
    int pos = left; // 临时数组元素的下标

    while (l_pos <= mid && r_pos <= right) { // 合并左右半区(直到一个半区到头了为止)
        if (arr[l_pos] < arr[r_pos]) { // 左半区的剩余元素更小
            tempArr[pos] = arr[l_pos];  // 就把更小的左半区的数字放入临时数组
            pos++; // 临时数组下标+1
            l_pos++; // 左半区下标+1

            compare++; // 左右组数字大小比较
            move++; // 更小的值被移动到临时数组
        } else { // 如果右半区的剩余元素更小
            tempArr[pos] = arr[r_pos]; // 就把更小的右半区的数字放入临时数组
            pos++;
            r_pos++; // 右半区下标+1

            compare++;
            move++;
        }
    }

    while (l_pos <= mid) { // 如果左半区还有剩余元素(右半区都放入了临时数组)
        tempArr[pos] = arr[l_pos]; // 把左半区的元素都复制到临时数组
        pos++;
        l_pos++;

        move++; // 把剩余的都移动到临时数组
    }

    while (r_pos <= right) { // 右半区还有剩余元素
        tempArr[pos] = arr[r_pos]; // 把右半区的元素都复制到临时数组
        pos++;
        r_pos++;

        move++;
    }

    while (left <= right) { // 把临时数组排好序的数字, 放入arr中
        arr[left] = tempArr[left];
        left++;

        move++; // 拍好的放到arr
    }
}

void msort(int arr[], int tempArr[], int left, int right) { // 把数组分左右区间, 并排序
    if (left < right) { // 如果left到right区间内还有至少两个元素, 继续分(如果只有一个元素就不需要继续划分)
        int mid = (left + right) / 2; // 找中间点
        msort(arr, tempArr, left, mid); // 递归划分左半区
        msort(arr, tempArr, mid + 1, right); // 递归划分右半区
        merge(arr, tempArr, left, mid, right); // 合并左右半区
    }
}

void merge_sort(int arr[], int n) { // 传入数组和数组长度
    int *tempArr = (int *)malloc(n * sizeof(int)); // 辅助数组, 存排好序的数
    msort(arr, tempArr, 0, n - 1);
    free(tempArr);
}

int main() {
    srand((unsigned)time(NULL)); // 随机数种子设置为时间, 不会重复

    // a
    int a_length;
    int a_range_start;
    int a_range_end;
    int a_range;
    printf("请输入第一组数据的整数个数: ");
    scanf("%d", &a_length);
    printf("请输入第一组数据的取值范围: ");
    scanf("%d %d", &a_range_start, &a_range_end);
    a_range = a_range_end - a_range_start; // 区间范围内有多少数字
    int a[a_length];
    printf("第一组数据: ");
    for (int i = 0; i < a_length; i++) {
        a[i] = rand() % a_range + a_range_start; // 随机数取a_range的余数, 这个随机数的大小就不会超过a_range, 再加上区间开始的数
        printf("%d ", a[i]);
    }
    printf("\n");

    // b
    int b_length;
    int b_range_start;
    int b_range_end;
    int b_range;
    printf("请输入第二组数据的整数个数: ");
    scanf("%d", &b_length);
    printf("请输入第二组数据的取值范围: ");
    scanf("%d %d", &b_range_start, &b_range_end);
    b_range = b_range_end - b_range_start;
    int b[b_length];
    printf("第二组数据: ");
    for (int i = 0; i < b_length; i++) {
        b[i] = rand() % b_range + b_range_start;
        printf("%d ", b[i]);
    }
    printf("\n");

    // c
    int c_length;
    int c_range_start;
    int c_range_end;
    int c_range;
    printf("请输入第三组数据的整数个数: ");
    scanf("%d", &c_length);
    printf("请输入第三组数据的取值范围: ");
    scanf("%d %d", &c_range_start, &c_range_end);
    c_range = c_range_end - c_range_start;
    int c[c_length];
    printf("第三组数据: ");
    for (int i = 0; i < c_length; i++) {
        c[i] = rand() % c_range + c_range_start;
        printf("%d ", c[i]);
    }
    printf("\n");





    // 排序
    // a
    // 快速排序
    printf("------------------------------\n");
    int a_copy[a_length];
    memcpy(a_copy, a, a_length * sizeof(int)); // 复制一个数组, 供另一个排序使用

    compare = 0;
    move = 0;

    QuickSort(a, 0, a_length - 1);
    printf("第一组快速排序结果: ");
    for (int i = 0; i < a_length; i++) {
        printf("%d ", a[i]);
    }
    printf("\n快速排序: 比较%d次, 移动%d次\n", compare, move);

    compare = 0;
    move = 0;

    merge_sort(a_copy, a_length);
    printf("第一组归并排序结果: ");
    for (int i = 0; i < a_length; i++) {
        printf("%d ", a_copy[i]);
    }
    printf("\n二路归并排序: 比较%d次, 移动%d次\n", compare, move);
    printf("------------------------------\n");


    // b
    printf("------------------------------\n");
    int b_copy[b_length];
    memcpy(b_copy, b, b_length * sizeof(int)); // 复制一个数组, 供另一个排序使用

    compare = 0;
    move = 0;

    QuickSort(b, 0, b_length - 1);
    printf("第二组快速排序结果: ");
    for (int i = 0; i < b_length; i++) {
        printf("%d ", b[i]);
    }
    printf("\n快速排序: 比较%d次, 移动%d次\n", compare, move);

    compare = 0;
    move = 0;

    merge_sort(b_copy, b_length);
    printf("第二组归并排序结果: ");
    for (int i = 0; i < b_length; i++) {
        printf("%d ", b_copy[i]);
    }
    printf("\n二路归并排序: 比较%d次, 移动%d次\n", compare, move);
    printf("------------------------------\n");

    // c
    printf("------------------------------\n");
    int c_copy[c_length];
    memcpy(c_copy, c, c_length * sizeof(int)); // 复制一个数组, 供另一个排序使用

    compare = 0;
    move = 0;

    QuickSort(c, 0, c_length - 1);
    printf("第三组快速排序结果: ");
    for (int i = 0; i < c_length; i++) {
        printf("%d ", c[i]);
    }
    printf("\n快速排序: 比较%d次, 移动%d次\n", compare, move);

    compare = 0;
    move = 0;

    merge_sort(c_copy, c_length);
    printf("第三组归并排序结果: ");
    for (int i = 0; i < c_length; i++) {
        printf("%d ", c_copy[i]);
    }
    printf("\n二路归并排序: 比较%d次, 移动%d次\n", compare, move);
    printf("------------------------------\n");
}