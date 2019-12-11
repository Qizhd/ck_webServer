#include "rb_tree.h"

void rb_tree:: insert_tree(int info) {

    NODE cur = make_shared<tree_node>() ;
    cur->data = info ;
    //空树，将该节点给根
    if(root == nullptr) {
        root = cur ;
        root->own_color = BLACK ; 
        null = make_shared<tree_node>() ;
        null->own_color = BLACK ;   
        //设置root的父亲节点指向null
        root->parent = null ;
    } 
    else {
        cur->own_color = RED ;
    }
    //按照二叉搜索树的形式插入
    insert_by_bst_way(cur) ;
    fix_up_insert(cur) ;
}

//插入后修正红黑树，保持性质不改变
void rb_tree :: fix_up_insert(NODE cur) {
    auto  parent = cur->parent ;  
    //要是当前的父亲节点和祖父节点是空
    if(parent == nullptr&&parent->parent == nullptr) {
        return ;
    }
    NODE uncle ;

    //当父亲节点的颜色是红色
    while(cur->parent->own_color == RED) {
        //情况1父亲节点和叔叔节点都是红色，
        //则插入点违反了红黑树性质
        //并且要是爷爷节点左孩子
        //当前父亲节点要是爷爷节点的左孩子
        if(parent == parent->parent->left) {
            //记录叔叔节点
            uncle = parent->parent->right ;
        }
        else {
            uncle = parent->parent->left ;
        }
        //要是叔叔节点是空的
        if(uncle == null) {
            //对当前祖父节点进行左旋
            left_rotate(parent->parent) ;
        }
        //叔叔节点是不是红色
        else {
            //叔叔节点是红色
            if(uncle -> own_color == RED) {
                //将叔叔节点和父亲节点设置成红色
                uncle->own_color = BLACK ;
                parent->own_color = BLACK ;
                parent->parent->own_color = RED ;
                //移动当前插入的节点的指针游标,
                //因为可能会破坏上面子树的结构
                cur = parent->parent ;
            }
        }
        //判断当前节点的父亲节点指向是否为空
        if(cur->parent == null) {
            break ;
        }   
        //要是当前游标指向的节点是其父亲节点的右指针指向的位置
        //处于第二种情况
        if(cur->parent != null && 
           cur == cur->parent->right) {
            //将游标指向父亲节点
            cur = cur->parent ;
            left_rotate(cur) ;   
        }
        //判断cur节点的爷爷节点是否为空，为空就跳出循环
        //第三种情况，变色加右旋就行
        if(cur->parent->parent == null) {
            cur->parent->own_color = BLACK ;
            break ;
        }
        //部位空就变色
        cur->parent->own_color = BLACK ;
        cur->parent->parent->own_color = RED ;
        //进行右旋
        right_rotate(cur->parent->parent) ;
        if(cur->parent == null) {
            break ;
        }
    } 
    root->own_color = BLACK ;
}   

NODE rb_tree :: find_node(int num) {
    auto cur = root ;
    while(cur != nullptr) {
        if(num > cur->data) {
            cur = cur->right ;
        }
        else if(num < cur->data) {
            cur = cur->left ;
        }
        else {
            return cur ;
        }
    }
    return nullptr ;
}

//删除节点
void rb_tree :: delete_node(NODE cur) {
    auto tmp = cur ;
 //   if()
}

//删除树中的一个节点
void rb_tree :: rb_transform(NODE  cur, NODE son) {
    if(cur->parent == null) {
        son->parent = null ;
        root = cur ;
    }
    else if(cur == cur->parent->left){
        cur->parent->left = son ;             
    }
    else if(cur == cur->parent->right){
        cur->parent->right = son ;
    }
    son->parent = cur->parent ;
} 

//左旋
void rb_tree::left_rotate(NODE cur) {
    //获取当前的左孩子
    auto ptr = cur->right ;
    if(ptr == null)  return ;
    //当前节点右子树设置成右孩子的左孩子
    cur->right = ptr->left ;
    if(ptr->left) {
        ptr->left->parent = cur ;
    }   
    //上面解放了右孩子的左指针,
    //这里右子树的左指针重新设置成右子树的父亲节点
    ptr->left = cur ;
    //要是ptr的左孩子不为空的话，将cur设置成该节点的左孩子
    //继承父亲节点  
    ptr->parent = cur->parent ;
    //是根节点
    if(cur->parent == null) {
        root = ptr ;
        root->parent = null ;
    }
    //有父亲节点就使父亲节点中的相应指针指向ptr
    else if(cur == cur->parent->left){
        cur->parent->left = ptr ;
    }
    else if(cur == cur->parent->right) {
        cur->parent->right = ptr ;
    }
    //旋转的根节点的父亲节点指针指向新根节点
    cur->parent = ptr ;
    root->own_color = BLACK ;
}


//右旋
void rb_tree::right_rotate(NODE cur) {
    //获取要旋转节点的左节点
    auto ptr = cur->left ;
    //右节点是空，返回
    if(ptr == null) return ;
    //设置要旋转节点的左孩子，左孩子是当前左孩子的右孩子(ptr->right)
    cur->left = ptr->right ;
    if(ptr->right != null) ptr->right->parent = cur ;    
    //上面既然解放了左孩子的右指针
    //这里左孩子的右指针指向cur
    ptr->right = cur ;
    
    //继承父亲节点
    ptr->parent = cur->parent ;
    //要是当前cur parent节点是空
    if(cur->parent == null) root = ptr ;
    //判断是父亲的左孩子还是右孩子
    else if(cur == cur->parent->left) {
        cur->parent->left = ptr ;
    }
    else if(cur == cur->parent->right) {
        cur->parent->right = ptr ;
    }
    cur->parent = ptr ;
    //将当前节点设置成Ptr
    root->own_color = BLACK ;
}

//按照二叉搜索树的形式插入//////////////////////////////
void rb_tree :: insert_by_bst_way(NODE cur) {
    auto tmp = root ;
    while(tmp) {
        if(tmp->data > cur->data) {
            if(tmp->left == nullptr) {
                tmp->left = cur ;
                cur->parent = tmp ;
                break ;
            }          
            tmp = tmp->left ;
        }   
        else {
            if(tmp->right == nullptr) {
                tmp->right = cur ;
                cur->parent = tmp ;
                break ;
            }
            tmp = tmp->right ;
        }
    }
    cur->left = null ;
    cur->right = null ;
    fix_up_insert(cur) ;
}

