//thread_pool.h

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <mutex>
#include <queue>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

// Thread safe implementation of a Queue using a std::queue
template <class T>
class SafeQueue
{
private:
    std::queue<T> m_queue; //����ģ�庯���������
    std::mutex m_mutex; // ���ʻ����ź���

public:
    SafeQueue() {}
    SafeQueue(SafeQueue &&other) {}
    ~SafeQueue() {}
    
    bool empty();
    
    int size();
    
    // �������Ԫ��
    void enqueue(T &t);
    
    // ����ȡ��Ԫ��
    bool dequeue(T &t);
};

class ThreadPool
{
private:
    class ThreadWorker // �����̹߳�����
    {
    private:
        int m_id; // ����id
        ThreadPool *m_pool; // �����̳߳�
    public:
        // ���캯��
        ThreadWorker(ThreadPool *pool, const int id);
        
        // ����()����
        void operator()();
    };
    
    bool m_shutdown; // �̳߳��Ƿ�ر�

    SafeQueue<std::function<void()>> m_queue; // ִ�к�����ȫ���У����������
    std::vector<std::thread> m_threads; // �����̶߳���
    std::mutex m_conditional_mutex; // �߳��������������
    std::condition_variable m_conditional_lock; // �̻߳��������������̴߳������߻��߻���״̬
public:
    // �̳߳ع��캯��
    ThreadPool(const int n_threads = 4);
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    // Inits thread pool
    void init();
    
    // Waits until threads finish their current task and shutdowns the pool
    void shutdown();
    
    // Submit a function to be executed asynchronously by the pool
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        // Create a function with bounded parameter ready to execute
        std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);// ���Ӻ����Ͳ������壬���⺯�����ͣ���������ֵ����

        // Encapsulate it into a shared pointer in order to be able to copy construct
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

        // Warp packaged task into void function
        std::function<void()> warpper_func = [task_ptr]()
        {
            (*task_ptr)();
        };

        // ����ͨ�ð�ȫ�����������ѹ�밲ȫ����
        m_queue.enqueue(warpper_func);

        // ����һ���ȴ��е��߳�
        m_conditional_lock.notify_one();

        // ������ǰע�������ָ��
        return task_ptr->get_future();
    }
};

#endif
