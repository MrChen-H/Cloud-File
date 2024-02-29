#include "threadloop.h"
template<class T>
bool SafeQueue<T>::empty() // ���ض����Ƿ�Ϊ��
{
    std::unique_lock<std::mutex> lock(m_mutex); // �����źű�����������ֹm_queue���ı�
    return m_queue.empty();
}

template<class T>
int SafeQueue<T>::size()
{
    std::unique_lock<std::mutex> lock(m_mutex); // �����źű�����������ֹm_queue���ı�
    return m_queue.size();
}

template<class T>
void SafeQueue<T>::enqueue(T &t)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_queue.emplace(t);
}

template<class T>
bool SafeQueue<T>::dequeue(T &t)
{
    std::unique_lock<std::mutex> lock(m_mutex); // ���м���

    if (m_queue.empty())
    {
        return false;
    }

    t = std::move(m_queue.front()); // ȡ������Ԫ�أ����ض���Ԫ��ֵ����������ֵ����
    m_queue.pop(); // ������ӵĵ�һ��Ԫ��

    return true;
}

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id)
{
}

void ThreadPool::ThreadWorker::operator()()
{
    std::function<void()> func; // �������������func
    bool dequeued; // �Ƿ�����ȡ��������Ԫ��
    while (!m_pool->m_shutdown)
    {
        {
            // Ϊ�̻߳��������������ʹ����̵߳����ߺͻ���
            std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
            // ����������Ϊ�գ�������ǰ�߳�
            if (m_pool->m_queue.empty())
            {
                m_pool->m_conditional_lock.wait(lock); // �ȴ���������֪ͨ�������߳�
            }

            // ȡ����������е�Ԫ��
            dequeued = m_pool->m_queue.dequeue(func);
        }
        // ����ɹ�ȡ����ִ�й�������
        if (dequeued)
        {
            func();
        }

    }
}

ThreadPool::ThreadPool(const int n_threads)
    : m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false)
{
}

void ThreadPool::init()
{
    for (int i = 0; i < m_threads.size(); ++i)
    {
        m_threads.at(i) = std::thread(ThreadWorker(this, i)); // ���乤���߳�
    }
}

void ThreadPool::shutdown()
{
    m_shutdown = true;
    m_conditional_lock.notify_all(); // ֪ͨ���������й����߳�
    for (int i = 0; i < m_threads.size(); ++i)
    {
        if (m_threads.at(i).joinable()) // �ж��߳��Ƿ��ڵȴ�
        {
            m_threads.at(i).join(); // ���̼߳��뵽�ȴ�����
        }
    }
}
