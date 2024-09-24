#define Maxsize 2000

int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes) {
    *returnSize = 0;    //这个一定要先初始化, 要不空数组时不能ac
    if (root == NULL) {
        return NULL;
    }
 
    int **res = (int **)malloc(sizeof(int *) * Maxsize);
    struct TreeNode *Q[Maxsize];
    // **returnColumnSizes 一个全局变量, 每层数目的数组
    // 给数组分配空间
    *returnColumnSizes = (int *)malloc(sizeof(int) * Maxsize);
    int front = 0, rear = 0;
    struct TreeNode *p = NULL;
    int size, flag;
    Q[rear++] = root;
    while (front != rear) {
        flag = rear; // 记录当前层尾指针位置
        size = 0;
        // 申请当前层的数组大小
        res[*returnSize] = (int *)malloc(sizeof(int *) * (flag - front));
        while (front < flag) {
            // 出队放入数组, 向后移
            p = Q[front++];
            res[*returnSize][size++] = p->val;
            // 有左右孩子就都入队
            if (p->left != NULL)
                Q[rear++] = p->left;
            if (p->right != NULL)
                Q[rear++] = p->right;
        }
        (*returnColumnSizes)[*returnSize] = size; //记录当前层结点个数
        (*returnSize)++;                          //下一层
    }
    return res;
}
