/*
================================================================================
Взято с https://youtu.be/t11q4qgwngQ?t=957
Использование:

using namespace std::chrono_literals;

...

auto timer = createTimer(5s, []() {
    std::cout << "Call callback\n";    <-- Создание callback'а
})

...

auto status = timer.wait_for(0s);             <-- проверка на завершёность
if (status == std::future_status::ready) {    <---+
    ...
}
================================================================================
*/

#pragma once
#include <functional>
#include <future>
#include <chrono>
#include <thread>

namespace oho {

template <class _Rep, class _Period>
std::future<void> createTimer(std::chrono::duration<_Rep, _Period> duration, std::function<void()> callback) {
    return std::async(std::launch::async, [duration, callback]() {
        std::this_thread::sleep_for(duration);
        callback();
    });
}

};