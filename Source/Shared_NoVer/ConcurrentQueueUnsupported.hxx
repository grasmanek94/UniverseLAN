#pragma once

#include <concepts>
#include <mutex>
#include <optional>
#include <queue>
#include <utility>

namespace Concurrency
{
    template<typename T>
    class concurrent_queue
    {
    public:
        concurrent_queue() = default;

        concurrent_queue(const concurrent_queue&) = delete;
        concurrent_queue& operator=(const concurrent_queue&) = delete;

        concurrent_queue(concurrent_queue&&) = delete;
        concurrent_queue& operator=(concurrent_queue&&) = delete;

        void push(const T& value)
        {
            std::scoped_lock lock(m_mutex);
            m_queue.push(value);
        }

        void push(T&& value)
        {
            std::scoped_lock lock(m_mutex);
            m_queue.push(std::move(value));
        }

        template<typename... Args>
        T& emplace(Args&&... args)
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.emplace(std::forward<Args>(args)...);
        }

        [[nodiscard]]
        bool try_pop(T& value)
            requires std::assignable_from<T&, T>
        {
            std::scoped_lock lock(m_mutex);

            if (m_queue.empty())
                return false;

            value = std::move(m_queue.front());
            m_queue.pop();
            return true;
        }

        [[nodiscard]]
        std::optional<T> try_pop()
        {
            std::scoped_lock lock(m_mutex);

            if (m_queue.empty())
                return std::nullopt;

            std::optional<T> value(std::move(m_queue.front()));
            m_queue.pop();
            return value;
        }

        [[nodiscard]]
        bool empty() const
        {
            std::scoped_lock lock(m_mutex);
            return m_queue.empty();
        }

    private:
        mutable std::mutex m_mutex;
        std::queue<T> m_queue;
    };
}