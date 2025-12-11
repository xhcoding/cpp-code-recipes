#include <coroutine>
#include <cstdint>
#include <exception>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

auto Timeout(std::jthread& t, int seconds) {
    struct Awaitable {
        std::jthread* t;
        int seconds;

        bool await_ready() {
            return false;
        }
        
        void await_suspend(std::coroutine_handle<> handle) {
            *t = std::jthread([handle, seconds = this->seconds]{
                std::cout << "thread sleep for " << seconds << "s" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(seconds));
                std::cout << "thread sleep for " << seconds << "s finished" << std::endl;
                handle.resume();
            });
        }
        void await_resume() {}
    };

    return Awaitable{&t, seconds};
}

struct Task {
    struct promise_type {
        Task get_return_object() {
            return {};
        }
        std::suspend_never initial_suspend() {
            return {};
        }
        std::suspend_never final_suspend() noexcept {
            return {};
        }
        void return_void() {}
        void unhandled_exception() {}
    };
};

Task AsyncSleep(std::jthread& t, int seconds) {
    std::cout << "Timeout start" << std::endl;
    co_await Timeout(t, seconds);
    std::cout << "Timeout end" << std::endl;
}

int main(int argc, char* argv[]) {

    std::jthread t;
    std::cout << "before async sleep" << std::endl;
    AsyncSleep(t, 2);
    std::cout << "after async sleep" << std::endl;
    
    return 0;
}
