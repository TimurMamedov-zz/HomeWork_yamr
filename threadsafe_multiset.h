/*!
\file
\brief
*/
#pragma once
#include <set>
#include <mutex>

template<typename T>
class ThreadSave_MultiSet
{
public:
    explicit ThreadSave_MultiSet()  = default;
    ThreadSave_MultiSet(ThreadSave_MultiSet&& MultiSet)
        :multiset(std::move(MultiSet.multiset)){}
    ThreadSave_MultiSet(const ThreadSave_MultiSet& ) = delete;
    ThreadSave_MultiSet& operator =(const ThreadSave_MultiSet& ) = delete;
    ~ThreadSave_MultiSet() = default;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lk(mt);
        multiset.emplace(std::move(new_value));
    }

    std::multiset<T>& getNonThreadSave_MultiSet()
    {
        return multiset;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mt);
        return multiset.empty();
    }

private:
    std::multiset<T> multiset;
    mutable std::mutex mt;
};
