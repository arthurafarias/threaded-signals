# Threaded Signals

This is a simple proof of concept on using a thread pool with signals library.

```cpp
#include <string>
#include <iostream>

#include <signal.hpp>

struct example : std::enable_shared_from_this<example>
{
    signal<std::shared_ptr<example>, std::string> on_data_received;
};

int main(int argc, char* argv[])
{
    /**
     * 
     */
    std::promise<std::string> p;
    auto f = p.get_future();

    auto object = std::make_shared<example>();

    object->on_data_received += [&p](std::shared_ptr<example> sender, std::string data){
        std::cout << data << std::endl;
        p.set_value(data);
    };

    object->on_data_received(object, "Hello World");

    f.wait();
    auto result = f.get();

    if (result == "Hello World") {
        std::cout << "Success" << std::endl;
    }

    return 0;
}
```