#include <chrono>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <format>

#if defined(_MSC_VER)
    #define NOINLINE __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
    #define NOINLINE __attribute__((noinline))
#else
    #define NOINLINE
#endif

using namespace std;

NOINLINE int64_t Accumulate(vector<int64_t> &arr) {
    int64_t sum = 0;
    int64_t sum2 = 0;
    int64_t sum3 = 0;
    int64_t sum4 = 0;
    for (int i = 0; i < arr.size(); i += 4) {
        sum += arr[i];
        sum2 += arr[i + 1];
        sum3 += arr[i + 2];
        sum4 += arr[i + 3];
    }
    
    return sum + sum2 + sum3 + sum4;
}

NOINLINE vector<int64_t> RandGenerator(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(numeric_limits<int32_t>::min(),
                                       numeric_limits<int32_t>::max());

    vector<int64_t> ans(n);
    for (int i = 0; i < ans.size(); i++) {
        ans[i] = distrib(gen);
    }

    return ans;
}

int main(int argc, char *argv[]) {

    auto arr = RandGenerator(1'000'000'000);

    auto start = chrono::high_resolution_clock::now();
    auto sum = Accumulate(arr);
    auto end = chrono::high_resolution_clock::now();

    auto diff_ns =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << format("sum: {}, diff: {} ns\n", sum, diff_ns) << endl;

    return 0;
}
