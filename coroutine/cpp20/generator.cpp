#include <coroutine>
#include <cstdint>
#include <exception>
#include <iostream>

struct MyGenerator {
    
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    
    struct promise_type {
        uint64_t value_;
        std::exception_ptr exception_;
        
        MyGenerator get_return_object() {
            return MyGenerator(handle_type::from_promise(*this));
        }
        
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception(void) { exception_ = std::current_exception(); }
        
        
        std::suspend_always yield_value(uint64_t value) {
            value_ = value;
            return {};
        }
        
        void return_void() {}
        
    };
    
    handle_type handle_;
    
    MyGenerator(handle_type handle) : handle_(handle) {}
    ~MyGenerator() { handle_.destroy(); };
    
    uint64_t operator()() {
        handle_();
        return handle_.promise().value_;
    }
};


MyGenerator Factorial(uint64_t n) {
    uint64_t ans = 1;
    for (int i = 1; i <= n; i++) {
        ans *= i;
        co_yield ans;
    }
}

int main(int argc, char* argv[]) {
    
    auto fac = Factorial(3);
    for (int i = 1; i <= 3; i++) {
        std::cout << i << " factorial: " << fac() << std::endl;
    }
    return 0;
}
