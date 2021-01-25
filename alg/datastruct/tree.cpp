#include <iostream>
#include <list>
using namespace std;

typedef struct _node_s {
    int     val;
    void*   ptr;
    struct _node_s *left;
    struct _node_s *right;
} node_t;


class CBinTree {
    public:
        CBinTree(int val, void* ptr) {
            m_root = new node_t;
            m_root->val = val;
            m_root->ptr = ptr;
            m_root->left = NULL;
            m_root->right = NULL;
        }
    public:
        void AddNode(int val, void* ptr) {
            _AddNode(m_root, val, ptr);
        }
        void Traverse() const {
            _Traverse(m_root);
        }
        void ToDoubleLink(list<node_t*>& dl) {
            _ToDoubleLink(dl, m_root);
        }
    private:
        void _AddNode(node_t* tmp, int val, void* ptr) {
            if (NULL == tmp) {
                return ;
            }
            if (tmp->val > val) {
                if (tmp->left) {
                    _AddNode(tmp->left, val, ptr);
                } else {
                    node_t* t = new node_t;
                    t->val = val;
                    t->ptr = ptr;
                    t->left = NULL;
                    t->right = NULL;
                    tmp->left = t;
                }
            }
            else {
                if (tmp->right) {
                    _AddNode(tmp->right, val, ptr);
                } else {
                    node_t* t = new node_t;
                    t->val = val;
                    t->ptr = ptr;
                    t->left = NULL;
                    t->right = NULL;
                    tmp->right = t;
                }
            }
        }

        void _Traverse(node_t *tmp) const {
            if (NULL == tmp) {
                return ;
            }
            _Traverse(tmp->left);
            cout << tmp->val << " ";
            _Traverse(tmp->right);
        }
        void _ToDoubleLink(list<node_t*>& dl, node_t* tmp) {
            if (NULL == tmp) {
                return ;
            }
            _ToDoubleLink(dl, tmp->left);
            _ToDoubleLink(dl, tmp->right);
            dl.push_back(tmp);
        }
    private:
        node_t*      m_root;
};

int main(int argc, char** argv) {
    CBinTree bt(4, NULL);
    int arr[] = {2, 1, 3, 6, 5, 7};
    for (int i=0; i<6; i++) {
        bt.AddNode(arr[i], NULL);
    }
    bt.Traverse();
    list<node_t*> dl;
    bt.ToDoubleLink(dl);

    cout << endl;
    for (auto iter=dl.begin(); iter!=dl.end(); ++iter) {
        cout << (*iter)->val << " " ;
    }
    cout << endl;
    return 0;
}
