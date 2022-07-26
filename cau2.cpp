#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<vector<int>> ans;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode*right;
};

TreeNode* createNode(int d){
    TreeNode* p=new TreeNode;
    p->val=d;
    p->left=nullptr;
    p->right=nullptr;
    return p;
}


TreeNode* insertion(TreeNode* &root, int d){
    if(!root){
        root=createNode(d);
        return root;
    }
    if(d<root->val) root->left=insertion(root->left, d);
    else root->right=insertion(root->right,d);
    return root;
}

void findWay(TreeNode*root, vector<int> c, int x){
    if(!root) return;
    if(!root->left and !root->right)
    {
        c.push_back(root->val);
        bool flag = false;
        for(int i=0; i<c.size(); i++)
        {
            if(c[i]==x)
            {
                flag = true;
                break;
            }
        }
        if(flag) ans.push_back(c);
        return;
    }
    c.push_back(root->val);
    findWay(root->left, c, x);
    findWay(root->right, c, x);
}

int main(){
    cout << "Number of elements: ";
    int d,N; cin>>N;
    //Node *root = createNode(=5);
    TreeNode*root=NULL;
    for(int i=0; i<N; i++){
        cin >> d;
        insertion(root,d);
    }
    cout << "X: ";
    int x;
    cin >> x;
    vector<int> p;
    findWay(root, p, x);
    for(int i=0; i<ans.size(); i++)
    {
        cout << "Path "<< i+1<<": ";
        for(int j = 0; j < ans[i].size();j++) cout << ans[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    delete root;
    return 0;
}