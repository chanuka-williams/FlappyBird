#pragma once
#include <memory>
#include <type_traits>
#include <utility>

class UniqueAction
{
public:
    UniqueAction() = default;

    template <typename F>
    requires(!std::is_same_v<std::decay_t<F>, UniqueAction> && std::is_invocable_r_v<void, std::decay_t<F>&>)
    explicit UniqueAction(F&& f) : m_impl(std::make_unique<Model<std::decay_t<F>>>(std::forward<F>(f)))
    {
    }

    UniqueAction(UniqueAction&&) noexcept = default;
    UniqueAction& operator=(UniqueAction&&) noexcept = default;
    UniqueAction(const UniqueAction&) = delete;
    UniqueAction& operator=(const UniqueAction&) = delete;

    void operator()() const
    {
        m_impl->Call();
    }

    explicit operator bool() const noexcept
    {
        return m_impl != nullptr;
    }

private:
    struct Concept
    {
        virtual ~Concept() = default;
        virtual void Call() = 0;
    };

    template <typename F>
    struct Model final : Concept
    {
        explicit Model(F f) : fn(std::move(f))
        {
        }
        void Call() override
        {
            fn();
        }
        F fn;
    };

    std::unique_ptr<Concept> m_impl;
};