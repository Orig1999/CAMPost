#ifndef LINKLIST_H
#define LINKLIST_H
//#define 0 0// 0 值的指针被称为空指针。0 指针是一个定义在标准库中的值为0的常量
template <class T>
class LinkNode
{
public :
    ~LinkNode()
    {

    }
    LinkNode()
    {
        pNext=0;
    }
    LinkNode(T data)
    {
        Data=data;
        pNext=0;
    }
    LinkNode<T> *pNext;//下一个节点
    T Data;
};

template <class T>
class LinkList
{
private:

public:
    LinkNode<T> *pHead;//链表头
    int length;
    ~LinkList()
    {
        Clear();
    }
    LinkList()
    {
        pHead=0;
        length=0;
    }
    LinkNode<T> * GetNode(int pos)
    {
        if(pos<0 || pos>length-1)//索引不在[0,length-1]则返回0
            return 0;

        LinkNode<T> *tmpNode = pHead;
        int i = 0;
        while(tmpNode && i<length)
        {
            if(i==pos)
            {
                return tmpNode;
            }
            tmpNode = tmpNode->pNext;
            ++i;
        }
        return 0;
    }
    void Clear()
    {
        if(length==0)
            return;

        LinkNode<T> *tmpNode = pHead;
        int i = 0;
        int tmpLength = length;
        while(tmpNode && i<tmpLength-1)
        {
            LinkNode<T> *needDelNode = tmpNode->pNext;
            pHead->pNext = needDelNode->pNext;
            delete needDelNode;
            --length;
            ++i;
        }
        delete pHead;
        --length;
    }
    LinkNode<T> * GetHead()
    {
        return pHead;
    }
    void SetHead(T &data)//设置链表头
    {
        Insert(0,data);
    }
    bool Insert(int pos,T &data)
    {
        if(pos<0)
            return false;
        else if(pos==0)
        {
            LinkNode<T> *head = new LinkNode<T> (data);
            pHead=head;
            ++length;
            return true;
        }
        else if(pos>length)//插在末尾
        {
            Insert(length,data);
            return true;
        }
        else
        {
            LinkNode<T> *nodeBeforeInsert = GetNode(pos-1);//获取需要被插入的位置的前一个节点
            if(nodeBeforeInsert!=0)
            {
                LinkNode<T> *newNode = new LinkNode<T> (data);
                newNode->pNext = nodeBeforeInsert->pNext;
                nodeBeforeInsert->pNext=newNode;
                ++length;
                return true;
            }
        }
        return false;
    }
    bool Remove(int pos)
    {
        if(pos<0 || pos>length-1)
            return false;
        if(pos==0)
        {
            LinkNode<T> *needRemoveNode = pHead;
            pHead=pHead->pNext;
            if(needRemoveNode!=0)
            {
                delete  needRemoveNode ;
                needRemoveNode=0;
            }
            -- length;
            return true;
        }
        else
        {
            LinkNode<T> *nodeBeforeDel = GetNode(pos-1);//获取需要被删除的前一个节点
            if(nodeBeforeDel!=0)
            {
                LinkNode<T> *needRemoveNode = nodeBeforeDel->pNext;
                nodeBeforeDel->pNext=needRemoveNode->pNext;
                if(needRemoveNode!=0)
                {
                    delete  needRemoveNode ;
                    needRemoveNode=0;
                }
                -- length;
                return true;
            }
        }
        return false;
    }
    T *GetData(int pos)
    {
        if(GetNode(pos)!=0)
            return &(GetNode(pos)->Data);
        return 0;
    }
};





#endif // LINKLIST_H
