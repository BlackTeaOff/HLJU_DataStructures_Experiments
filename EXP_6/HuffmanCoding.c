#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // selectMin函数中的INT_MAX
#include <math.h>

typedef struct {
    char ch;
    int weight;
    int parent;
    int lchild;
    int rchild;
} HuffmanTree;

char* fileSelect() {
    char *filepath = malloc(sizeof(char) * 100);
    printf("请输入文件的路径: ");
    scanf("%s", filepath);
    printf("文件选择成功\n");
    return filepath;
}

void selectMin(HuffmanTree *T, int n, int *s1, int *s2) { // 选择两个权值最小下标辅助函数
    int min1_weight = INT_MAX; // 存s1权值, 先初始化为int最大值
    int min2_weight = INT_MAX; // 存s2权值
    *s1 = -1; // 先把权值最小下标初始化为-1
    *s2 = -1;

    for (int i = 1; i <= n; i++) { // n是搜索范围
        if (T[i].parent == 0) { // 选择没有parent的结点(还未组成树的)
            if (T[i].weight < min1_weight) { // 该结点的权值小于当前s1的权值
                min2_weight = min1_weight; // 将s2的权值保存为s1的权值
                *s2 = *s1; // s2下标值也更新
                min1_weight = T[i].weight; // 更新s1权值
                *s1 = i; //  更新s1下标
            } else if (T[i].weight < min2_weight) { // 或者当前结点权值大于s1小于s2
                min2_weight = T[i].weight; // 就更新s2的权值
                *s2 = i; // 更新s2下标
            }
        }
    }
}

HuffmanTree* createHTree(char* filepath, int *len) { // len记录叶子节点数量. 用来求数组长度
    if (filepath == NULL) {
        printf("未选择文件\n");
        return NULL;
    }

    FILE *fp = fopen(filepath, "rb");

    if (fp == NULL) {
        printf("文件无法打开\n");
        return NULL;
    }

    int ch; // 存储每个字符的ASCII码
    int char_counts[256]; // 用来存储每个字符出现的权值, 下标是ASCII值(ASCII范围0-255)
    memset(char_counts, 0, sizeof(char_counts)); // 数组清零
    while ((ch = fgetc(fp)) != EOF) {
        char_counts[ch]++; // 以ASCII码作为下标, 相同种类的字符ASCII码相同
    }
    fclose(fp);

    int n = 0;
    for (int i = 0; i < 256; i++) { // 计算n的值, n就是叶子结点的数量
        if (char_counts[i] > 0) { // 也是文件中不同字符的种类数量
            n++; // 权值大于0则就有一种字符
        }
    }
    *len = n;

    HuffmanTree *T = malloc(sizeof(HuffmanTree) * (2 * n)); // 创建2n大小的哈夫曼树
    int leaf_index = 1; // 哈夫曼树一共有2n-1个结点, 第0个位置不用, 于是分配2n大小的空间
    for (int i = 0; i < 256; i++) { // 把叶子结点存入数组
        if (char_counts[i] > 0) { // 如果有权值, 就代表一个字符, 就存入树中
            T[leaf_index].ch = (char)i; // 此时的下标i就是对应字符的ASCII, 可以直接转换为字符
            T[leaf_index].weight = char_counts[i];
            T[leaf_index].parent = 0; // 其他先初始化为0
            T[leaf_index].lchild = 0;
            T[leaf_index].rchild = 0;
            leaf_index++;
        }
    }
    for (int i = n + 1; i < 2 * n; i++) { // 初始化非叶子结点, (2n-1) - n = n-1个
        T[i].ch = 0;
        T[i].weight = 0;
        T[i].parent = 0;
        T[i].lchild = 0;
        T[i].rchild = 0;
    }

    for (int i = n + 1; i < 2 * n; i++) { // 开始用叶子结点创建哈夫曼树, 从n+1开始(叶子结点之后)
        int s1, s2; // 两个parent = 0, 权值最小的结点合成一个树, s1,2存其下标
        selectMin(T, i - 1, &s1, &s2); // 选择范围随着新结点增多而增大, s1,2是两个最小权值结点下标
        T[s1].parent = i; // 两个最小权值结点的parent指向新创建结点下标i
        T[s2].parent = i;
        T[i].lchild = s1; // 新创建的结点的左右子结点下标设为s1,2
        T[i].rchild = s2;
        T[i].weight = T[s1].weight + T[s2].weight; // 新结点权值等于两个子结点权值之和
    }

    return T;
}

void printHTree(HuffmanTree *T, int n) {
    if (T == NULL || n == 0) {
        return;
    }
    for (int i = 1; i < 2 * n; i++) {
        printf("%c ", T[i].ch);
        printf("%d", T[i].weight);
        printf("\n");
    }
}

char** genHCodes(HuffmanTree *T, int n) { // generate(生成密码本), 返回密码本(字符串数组)
    if (T == NULL) {
        printf("未建立哈夫曼树\n");
        return NULL;
    }

    char **huffmanCodes = calloc(256, sizeof(char *)); // 一个一级指针只能存储一个字符串的地址, 二级指针可以存储多个字符串的指针(一级指针)的地址, 从而实现多个字符串的数组, calloc是为了把每个一级指针都指向NULL

    char *code = malloc(sizeof(char) * n); // n个叶子结点编码最大长度为n-1, 最后一位为'\0', 临时存储当前结点编码
    code[n - 1] = '\0'; // 数组大小为n, 最后一个位置是n-1, 设为结束标识

    for (int i = 1; i <= n; i++) { // 遍历所有叶子结点, 从1到n
        int start = n - 1; // 从数组最后向前记录编码, 因为是从叶子结点开始往上找的
        int current = i;
        int parent = T[current].parent; // 当前结点的父节点

        while (parent != 0) { // 遍历当前结点, 直到到达树顶端
            start--; // 记录编码数组下标向前移一位
            if (T[parent].lchild == current) { // 该结点是父节点的左子结点的情况下(左0右1)
                code[start] = '0'; // 左编码为0
            } else { // 该结点时父节点的右子节点则编码为1
                code[start] = '1';
            }
            current = parent; // 把当前结点变为父节点
            parent = T[current].parent; // 再找当前结点的父节点
        }
        huffmanCodes[T[i].ch] = malloc(sizeof(char) * (n - start)); // 用ASCII码作为当前字符数组下标, 分配大小正好为编码大小(n-start)
        strcpy(huffmanCodes[T[i].ch], &code[start]); // 把编码复制到密码本中
    }
    free(code);
    return huffmanCodes;
}

void encodeFile(char* filepath, char** HCodes) { // 传入文件和密码本
    FILE *fp = fopen(filepath, "rb");

    if (fp == NULL) {
        printf("未选择文件\n");
        return;
    }

    char path[100];
    printf("请输入编码后文件保存路径: ");
    scanf("%s", path);

    FILE *newfp = fopen(path, "w");
    if (newfp == NULL) {
        printf("文件创建失败\n");
        return;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) { // 一个一个读取字符ASCII码
        fputs(HCodes[ch], newfp); // 根据ASCII下标, 找到该字符对应编码, 写入文件
    }

    fclose(fp);
    fclose(newfp);
    printf("文件保存成功\n");
}

void decodeFile(HuffmanTree *T, int n) { // 传入树和叶子结点数量
    if (T == NULL) {
        printf("未建立哈夫曼树\n");
        return;
    }

    char encodedPath[100];
    printf("请输入需要解码的文件路径: ");
    scanf("%s", encodedPath);

    char decodedPath[100];
    printf("请输入解码后文件的保存路径: ");
    scanf("%s", decodedPath);

    FILE *fin = fopen(encodedPath, "r");
    if (fin == NULL) {
        printf("无法打开编码文件\n");
        return;
    }

    FILE *fout = fopen(decodedPath, "w");
    if (fout == NULL) {
        printf("无法创建解码文件\n");
        return;
    }

    int root = 2 * n - 1; // 哈夫曼树的根结点下标是最后一个位置(最后两个合成的结点)
    int current = root; // 现在正在遍历的结点的下标
    int ch; // 从编码文件中获取01

    while ((ch = fgetc(fin)) != EOF) { // 左0右1
        if (ch == '0') { // 如果是0, 则向左走
            current = T[current].lchild; // 更新当前结点
        } else if (ch == '1') { // 如果是1, 则向右走
            current = T[current].rchild;
        }

        if (T[current].lchild == 0 && T[current].rchild == 0) { // 当前结点左右都为0, 则到达叶子结点
            fputc(T[current].ch, fout); // 叶子结点的字符就是解码的结果
            current = root; // 返回到根结点进行下一个字符的解码
        }
    }

    fclose(fin);
    fclose(fout);
    printf("文件解码成功\n");
}

void saveHCodes(char** codes) { // 保存密码本到文件, 传入密码本(实际上是二维数组)
    if (codes == NULL) {
        printf("未建立密码本\n");
        return;
    }

    char savePath[100];
    printf("输入保存密码本的路径: ");
    scanf("%s", savePath);

    FILE *fp = fopen(savePath, "w");
    if (fp == NULL) {
        printf("无法创建文件\n");
        return;
    }

    for (int i = 0; i < 256; i++) { // codes[i]是某个字符串的地址
        if (codes[i] != NULL) {
            fprintf(fp, "%c: %s\n", i, codes[i]);
        }
    }

    fclose(fp);
    printf("密码本保存成功\n");
}

char binaryToDecimal(char* bin) { // 二进制转十进制(仅支持8位)
    int sum = 0;
    char dec;
    for (int i = 0; i < 8; i++) { // bin[0]是最高位, 需要乘以2的7次方
        sum += (bin[i] - '0') * pow(2, 7 - i); // 2的7-i次方, 把ASCII码转为真正的数字, bin是char类型的数组
    }
    dec = sum;
    return dec;
}

long getFileSize(char* filepath) {
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return -1;
    }
    fseek(fp, 0, SEEK_END); // 文件指针移动到末尾
    long size = ftell(fp); // 获取当前指针到文件头的大小(就是文件大小)
    fclose(fp);
    return size;
}

void compressHCode() {
    char codePath[100];
    printf("请输入需要压缩编码的路径: ");
    scanf("%s", codePath);

    FILE *fin = fopen(codePath, "r");
    if (fin == NULL) {
        printf("编码文件打开失败\n");
        return;
    }

    char compressedPath[100];
    printf("请输入保存压缩文件的路径: ");
    scanf("%s", compressedPath);
    FILE *fout = fopen(compressedPath, "wb");

    long totalBits = getFileSize(codePath);
    fwrite(&totalBits, sizeof(long), 1, fout); // 在文件头写入总位数

    char bitBuffer[8]; // 存储8位二进制数
    int bitCount = 0; // 用来检查是否满8位数, 还有作为bitBuffer的下标
    int ch; // 用来存储从文件读入的字符

    while ((ch = fgetc(fin)) != EOF) { // 一位一位读入数字
        bitBuffer[bitCount] = ch;
        bitCount++; // 下标移动到下一位
        if (bitCount == 8) { // 满8位则把这8位二进制数对应的十进制数用fwrite(二进制)方式直接写入压缩文件
            char byte = binaryToDecimal(bitBuffer); // 把8位数转成了一个十进制数
            fwrite(&byte, sizeof(char), 1, fout); // 再把这个十进制数按二进制的方式写入
            bitCount = 0; // 写完一个重置, 接着处理下8位
        }
    }
    if (bitCount > 0) { // 处理不满8位的情况
        while (bitCount < 8) {
            bitBuffer[bitCount] = '0'; // 在后面全部补0
            bitCount++;
        }
        char byte = binaryToDecimal(bitBuffer);
        fwrite(&byte, sizeof(char), 1, fout); // 再把这8位二进制对应的十进制按二进制方式写入
    }

    fclose(fin);
    fclose(fout);
    printf("文件已成功压缩\n");
    long sourceSize = getFileSize(codePath);
    long compressedSize = getFileSize(compressedPath);
    printf("原始文件大小: %ld字节\n", sourceSize);
    printf("压缩文件大小: %ld字节\n", compressedSize);
    double rate = (double)compressedSize / sourceSize;
    printf("压缩率为: %lf%%\n", rate * 100);
}

char* decimalToBinary(unsigned char dec) {
    int q; // 商
    int r; // 余

    char *bin = malloc(sizeof(char) * 9); // 8位数存储二进制数, 最后\0
    bin[8] = '\0';

    for (int i = 0; i < 8; i++) {
        bin[i] = '0';
    }

    int i = 7;    // 余数是从下到上的, 所以倒着存
    while (dec > 0) { // 短除法
        q = dec / 2;
        r = dec % 2;
        bin[i] = r + '0'; // 倒着存余数, 最后得到二进制数, 转换为字符形式
        i--;
        dec = q; // 商继续作为被除数除以2, 直到dec小于0
    }
    return bin;
}

void decompressHCode() {
    char compressedPath[100];
    printf("请输入需要解压的文件路径: ");
    scanf("%s", compressedPath);

    char decompressedPath[100];
    printf("请输入解压后文件的保存路径: ");
    scanf("%s", decompressedPath);

    FILE *fin = fopen(compressedPath, "rb");
    if (fin == NULL) {
        printf("压缩文件打开失败\n");
        return;
    }

    FILE *fout = fopen(decompressedPath, "w");
    if (fout == NULL) {
        printf("无法创建解压文件\n");
        return;
    }

    long totalBits;
    if (fread(&totalBits, sizeof(long), 1, fin) != 1) { // 读取总字节数, 不写入多补的0
        printf("读取文件头失败\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    long bitsWritten = 0; // 记录已写入的位数
    unsigned char byte; // 8位2进制的数最大能表示255, unsigned char范围0-255
    while (fread(&byte, sizeof(unsigned char), 1, fin) == 1 && bitsWritten < totalBits) { // 从文件中每次读1字节
        char *bin = decimalToBinary(byte);

        for (int i = 0; i < 8 && bitsWritten < totalBits; i++) { // 写入的字节要小于总字节(头多一位)
            fputc(bin[i], fout);
            bitsWritten++;
        }
        free(bin);
    }

    fclose(fin);
    fclose(fout);
    printf("文件解压成功\n");
}

int main() {
    // int n = 0;
    // char* filepath = fileSelect();
    // HuffmanTree *T = createHTree(filepath, &n);
    // printHTree(T, n);
    // char** codes = genHCodes(T, n);
    // saveHCodes(codes);
    // encodeFile(filepath, codes);
    // decodeFile(T, n);
    // compressHCode();
    // decompressHCode();

    char *filePath = NULL;
    int n; // 叶子结点数量
    HuffmanTree *T = NULL;
    char **codes;
    char choice;

    while (1) {
        printf("**********************************************************************\n");
        printf("*                        哈夫曼编码译码器                            *\n");
        printf("*                   1. 选择需要进行编码的文件                        *\n");
        printf("*                   2. 建立哈夫曼树                                  *\n");
        printf("*                   3. 建立密码本并对文件编码                        *\n");
        printf("*                   4. 选择需要进行解码的文件并解码                  *\n");
        printf("*                   5. 按位压缩方式对文件进行压缩                    *\n");
        printf("*                   6. 按位解压方式对文件进行解压                    *\n");
        printf("**********************************************************************\n");

        int t;
        scanf("%d", &t);

        switch (t) {
            case 1:
                filePath = fileSelect();
                break;
            case 2:
                T = createHTree(filePath, &n);
                if (T != NULL) {
                    printf("成功创建哈夫曼树\n");
                }
                break;
            case 3:
                codes = genHCodes(T, n); // 密码本二维数组
                encodeFile(filePath, codes);
                if (codes != NULL) {
                    printf("是否保存密码本到文件?(Y/N)");
                    scanf(" %c", &choice);
                    if (choice == 'Y') {
                        saveHCodes(codes);
                    }
                }
                break;
            case 4:
                decodeFile(T, n);
                break;
            case 5:
                compressHCode();
                break;
            case 6:
                decompressHCode();
                break;
        }

    // printf("**********************************************************************\n");
    // printf("*                        哈夫曼编码译码器                            *\n");
    // printf("*                   1. 选择需要进行编码的文件                        *\n");
    // printf("*                   2. 建立哈夫曼树                                  *\n");
    // printf("*                   3. 建立密码本并对文件编码                        *\n");
    // printf("*                   4. 选择需要进行解码的文件并解码                  *\n");
    // printf("*                   5. 按位压缩方式对文件进行压缩                    *\n");
    // printf("**********************************************************************\n");
    }
}