#include <mutex>

//code
void threadAction(std::mutex &mut, int &sharedInt)
{
    std::lock_guard<std::mutex> lg{mut, std::adopt_lock_t()};
    // do something with sharedInt
}
//=
