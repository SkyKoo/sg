#include "sgConfig.h"

using namespace sg;

int main()
{
    SGConfig config("./sg.cfg");

    std::string test1 = "";
    config.getValue("test1", test1);
    std::cout << test1 << std::endl;

    int test2 = 0;
    config.getValue("test2", test2);
    std::cout << test2 << std::endl;
    
    config.setValue("test1", "def");
    config.setValue("test2", "456");
    config.setValue("test3", "ggg");
    config.setValue("test4", "12343456");
    config.save();

    config.getValue("test1", test1);
    std::cout << test1 << std::endl;
    config.getValue("test2", test2);
    std::cout << test2 << std::endl;

    return 0;
}
