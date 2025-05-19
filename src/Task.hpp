#ifndef ENG_TASK_HPP
#define ENG_TASK_HPP

#include <functional>
#include <memory>

namespace engine {

class TaskDispatcher {
public:
    TaskDispatcher();
    virtual ~TaskDispatcher() = default;

    static std::shared_ptr<TaskDispatcher> New();

    void Run(std::function<void()> task);

private:
};

} // namespace engine

#endif // !ENG_TASK_HPP
