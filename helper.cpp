#ifndef UNTITLED_HELPER
#define UNTITLED_HELPER

#include "helper.h"
game_result object;

void stat.display(int count)
{
    std::cout << "Game number: " << count << " done" << "\n" << "Range was till 1 until " << object.array_size << "\n" <<
    "Amount of attempts: " << object.att_count << "\n" << "Game time was: " << object.g_time << std::endl;
}

void increment_game_count(int count)
{
    object.att_count = count;
}

void set_game_time(unsigned time)
{
    object.g_time = time;
}

void set_array_size(int size)
{
    object.array_size = size;
}

void str_display(const std::string& data)
{
    std::cout << data << std::endl;
}

void mes_display(const std::string& data, const int value)
{
    std::cout << data << value << "\n" << std::endl;
}

void assumption_display(int value)
{
    std::cout << "My assumption is: " << value << std::endl;
}

void answer_display(bool flag)
{
    if (flag)
        std::cout << "Your answer is right! Congratulations. Your game just ended. Change places." << std::endl;
    else
        std::cout << "You're not right." << std::endl;
}

#endif