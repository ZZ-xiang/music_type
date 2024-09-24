#define Maxsize 2000

int **levelOrder(struct TreeNode *root, int *returnSize,
                 int **returnColumnSizes) {
    *returnSize = 0;    //���һ��Ҫ�ȳ�ʼ��, Ҫ��������ʱ����ac
    if (root == NULL) {
        return NULL;
    }
 
    int **res = (int **)malloc(sizeof(int *) * Maxsize);
    struct TreeNode *Q[Maxsize];
    // **returnColumnSizes һ��ȫ�ֱ���, ÿ����Ŀ������
    // ���������ռ�
    *returnColumnSizes = (int *)malloc(sizeof(int) * Maxsize);
    int front = 0, rear = 0;
    struct TreeNode *p = NULL;
    int size, flag;
    Q[rear++] = root;
    while (front != rear) {
        flag = rear; // ��¼��ǰ��βָ��λ��
        size = 0;
        // ���뵱ǰ��������С
        res[*returnSize] = (int *)malloc(sizeof(int *) * (flag - front));
        while (front < flag) {
            // ���ӷ�������, �����
            p = Q[front++];
            res[*returnSize][size++] = p->val;
            // �����Һ��ӾͶ����
            if (p->left != NULL)
                Q[rear++] = p->left;
            if (p->right != NULL)
                Q[rear++] = p->right;
        }
        (*returnColumnSizes)[*returnSize] = size; //��¼��ǰ�������
        (*returnSize)++;                          //��һ��
    }
    return res;
}
