#pragma once
#include <ace/Unbounded_Queue.h>

namespace ACE_Based
{
    template <typename T>
    class BoundedQueue
    {

    public:
        int enqueue_head(T& item);
        int enqueue_tail(T& item);
        int dequeue_head(T& item);

        void Init(int MaxElem);

    private:

        ACE_Unbounded_Queue<T> m_internalQueue;

        int m_maxElements;
    };

    template <typename T>
    void BoundedQueue<T>::Init(int MaxElem)
    {
        m_maxElements = MaxElem;
    }

    template <typename T>
    int BoundedQueue<T>::enqueue_tail(T& item)
    {
        if (m_maxElements != 0)
        {
            if (m_internalQueue.size() + 1 > m_maxElements)
            {
                //out of legit bounds, error
                return -2;
            }
        }

        return m_internalQueue.enqueue_tail(item);
    }

    template <typename T>
    int BoundedQueue<T>::dequeue_head(T& item)
    {
        return m_internalQueue.dequeue_head(item);
    }

    template <typename T>
    int BoundedQueue<T>::enqueue_head(T& item)
    {
        if (m_maxElements != 0)
        {
            if (m_internalQueue.size() + 1 > m_maxElements)
            {
                //out of legit bounds, error
                return -2;
            }
        }

        return m_internalQueue.enqueue_head(item);
    }



}