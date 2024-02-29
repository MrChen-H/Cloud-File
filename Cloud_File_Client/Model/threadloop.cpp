#include "threadloop.h"
template<class T>
bool SafeQueue<T>::empty() // 返回队列是否为空
{
    std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
    return m_queue.empty();
}

template<class T>
int SafeQueue<T>::size()
{
    std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变
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
    std::unique_lock<std::mutex> lock(m_mutex); // 队列加锁

    if (m_queue.empty())
    {
        return false;
    }

    t = std::move(m_queue.front()); // 取出队首元素，返回队首元素值，并进行右值引用
    m_queue.pop(); // 弹出入队的第一个元素

    return true;
}

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id)
{
}

void ThreadPool::ThreadWorker::operator()()
{
    std::function<void()> func; // 定义基础函数类func
    bool dequeued; // 是否正在取出队列中元素
    while (!m_pool->m_shutdown)
    {
        {
            // 为线程环境加锁，互访问工作线程的休眠和唤醒
            std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex);
            // 如果任务队列为空，阻塞当前线程
            if (m_pool->m_queue.empty())
            {
                m_pool->m_conditional_lock.wait(lock); // 等待条件变量通知，开启线程
            }

            // 取出任务队列中的元素
            dequeued = m_pool->m_queue.dequeue(func);
        }
        // 如果成功取出，执行工作函数
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
        m_threads.at(i) = std::thread(ThreadWorker(this, i)); // 分配工作线程
    }
}

void ThreadPool::shutdown()
{
    m_shutdown = true;
    m_conditional_lock.notify_all(); // 通知，唤醒所有工作线程
    for (int i = 0; i < m_threads.size(); ++i)
    {
        if (m_threads.at(i).joinable()) // 判断线程是否在等待
        {
            m_threads.at(i).join(); // 将线程加入到等待队列
        }
    }
}
