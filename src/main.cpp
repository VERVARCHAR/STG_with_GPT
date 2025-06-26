#include "system/Application.hpp"

int main(int argc, char *argv[])
{
    Application app;
    if (!app.init())
        return -1;
    app.run();
    app.shutdown();
    return 0;
}
