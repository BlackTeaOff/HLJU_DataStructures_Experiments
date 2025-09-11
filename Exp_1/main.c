#define MAXSIZE 100
#include <stdio.h>

typedef struct
{
  int data[MAXSIZE];
  int length;
} SeqList;

void initList(SeqList *L)
{ // 传入顺序表地址，因为C语言默认按值传递，而且复制一份结构体占空间
  L->length = 0;
}

int appendElem(SeqList *L, int e)
{
  if (L->length >= MAXSIZE)
  {
    printf("顺序表已满\n");
    return 0;
  }
  L->data[L->length] = e;
  L->length++;
  return 1;
}

void listElem(SeqList *L)
{
  for (int i = 0; i < L->length; i++)
  {
    printf("%d ", L->data[i]);
  }
  printf("\n");
}

int insertElem(SeqList *L, int pos, int e)
{
  if (L->length >= MAXSIZE)
  {
    printf("顺序表已满\n");
    return 0;
  }
  if (pos < 1 || pos > L->length + 1)
  {
    printf("插入位置有误\n");
    return 0;
  }
  if (pos == L->length + 1) { // 插入到末尾
    L->data[L->length] = e;
  } else { // pos <= L->length
    for (int i = L->length - 1; i >= pos - 1; i--)
    {
      L->data[i + 1] = L->data[i];
    }
    L->data[pos - 1] = e;
  }
  L->length++;
  return 1;
}

void increasingOrder(SeqList *L, int x) // 找到要插入的位置(pos),然后调用insertElem.
{
  for (int i = 0; i <= L->length - 1; i++) { // length比下标大1
    if (x < L->data[i]) {
      insertElem(L, i + 1, x); // L已经是指针(地址), 不需要加取址符了, i+1是因为pos是从1开始的, i是从0开始的
      return;
    }
  }
  L->data[L->length] = x; // 第length位就是数组的最后一位的后一位
  L->length++;
}

void moveRight(SeqList *L, int k) {
  for (int i = 0; i < k; i++) { // 下面是右移一次的操作
    int temp = L->data[L->length - 1]; // 把最后一位存上(length - 1是最后一位的下标)
    for (int j = L->length - 2; j >= 0; j--) { // 从倒数第二位开始往前移
      L->data[j + 1] = L->data[j];
    }
    L->data[0] = temp;
  }
}

void reverse(SeqList *L) {
  for (int i = 0; i <= (L->length - 1) / 2; i++) {
    int temp = L->data[i];
    L->data[i] = L->data[L->length - 1 - i];
    L->data[L->length - 1 - i] = temp;
  }
}

int main()
{
  SeqList mylist;
  initList(&mylist);
  for (int i = 0; i < 10; i++) { // 缺5的按顺序排列好的顺序表
    if (i == 5) {
      continue;
    }
    appendElem(&mylist, i);
  }
  listElem(&mylist);
  increasingOrder(&mylist, 10); // 插入最大的数字
  listElem(&mylist);
  increasingOrder(&mylist, -1); // 插入最小的数字
  listElem(&mylist);
  increasingOrder(&mylist, 5); // 插入中间的数字5
  listElem(&mylist);

  moveRight(&mylist, 1);
  listElem(&mylist);
  moveRight(&mylist, 2);
  listElem(&mylist);

  SeqList q2list;
  initList(&q2list);
  for (int i = 0; i < 6; i++) {
    appendElem(&q2list, i + 1);
  }
  listElem(&q2list);
  moveRight(&q2list, 4);
  listElem(&q2list);

  SeqList q3list;
  initList(&q3list);
  for (int i = 0; i < 6; i++) {
    appendElem(&q3list, i + 1);
  }
  listElem(&q3list);
  reverse(&q3list);
  listElem(&q3list);
}
