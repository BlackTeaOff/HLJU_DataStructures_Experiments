#define MAXSIZE 100
#include <stdio.h>

typedef struct
{
  int data[MAXSIZE];
  int length;
} SeqList;

void initList(SeqList *L)
{ // ����˳����ַ����ΪC����Ĭ�ϰ�ֵ���ݣ����Ҹ���һ�ݽṹ��ռ�ռ�
  L->length = 0;
}

int appendElem(SeqList *L, int e)
{
  if (L->length >= MAXSIZE)
  {
    printf("˳�������\n");
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
    printf("˳�������\n");
    return 0;
  }
  if (pos < 1 || pos > L->length + 1)
  {
    printf("����λ������\n");
    return 0;
  }
  if (pos == L->length + 1) { // ���뵽ĩβ
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

void increasingOrder(SeqList *L, int x) // �ҵ�Ҫ�����λ��(pos),Ȼ�����insertElem.
{
  for (int i = 0; i <= L->length - 1; i++) { // length���±��1
    if (x < L->data[i]) {
      insertElem(L, i + 1, x); // L�Ѿ���ָ��(��ַ), ����Ҫ��ȡַ����, i+1����Ϊpos�Ǵ�1��ʼ��, i�Ǵ�0��ʼ��
      return;
    }
  }
  L->data[L->length] = x; // ��lengthλ������������һλ�ĺ�һλ
  L->length++;
}

void moveRight(SeqList *L, int k) {
  for (int i = 0; i < k; i++) { // ����������һ�εĲ���
    int temp = L->data[L->length - 1]; // �����һλ����(length - 1�����һλ���±�)
    for (int j = L->length - 2; j >= 0; j--) { // �ӵ����ڶ�λ��ʼ��ǰ��
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
  for (int i = 0; i < 10; i++) { // ȱ5�İ�˳�����кõ�˳���
    if (i == 5) {
      continue;
    }
    appendElem(&mylist, i);
  }
  listElem(&mylist);
  increasingOrder(&mylist, 10); // ������������
  listElem(&mylist);
  increasingOrder(&mylist, -1); // ������С������
  listElem(&mylist);
  increasingOrder(&mylist, 5); // �����м������5
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
