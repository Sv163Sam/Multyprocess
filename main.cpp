#include "u_pipe.h"
#include "signals.h"
#include "mes_queue.h"

int main()
{
    int game_mode_var = 0;
    str_display("Please, select a game execution: ");
    str_display("1 - By processes with synchronization type - unnamed pipe");
    str_display("2 - By processes with synchronization type - message queue");
    str_display("3 - By signals with synchronization type - real time signals");

    std::cin >> game_mode_var;
    switch(game_mode_var)
    {
        case 1:
        {
            int count = 0;
            bool game_flag = true;

            int fd[2];
            int fd_s[2];
            check(pipe(fd));
            check(pipe(fd_s));
            pid_t p_id = check(fork());

            do {
                if(count % 2 != 0)
                    game_flag = false;

                if (p_id)
                {
                    if(game_flag) U_PIPE::guess_player(fd[0], fd_s[1]);
                    else
                    {
                        sleep(1);
                        U_PIPE::assump_player(fd[1], fd_s[0]);
                    }
                }
                else
                {
                    if(game_flag) U_PIPE::assump_player(fd[1], fd_s[0]);
                    else
                    {
                        sleep(1);
                        U_PIPE::guess_player(fd[0], fd_s[1]);
                    }
                }
                stat_display(count);

                count++;

                if (!game_flag) game_flag = true;

            } while(count < 11);

            exit(EXIT_SUCCESS);

            break;
        }
        case 2:
        {
            int count = 0;
            bool game_flag = true;

            auto d = check(mq_open("/mymq", O_CREAT, S_IRUSR | S_IWUSR, NULL));
            auto d1 = check(mq_open("/mymq1", O_CREAT, S_IRUSR | S_IWUSR, NULL));
            check(mq_close(d));

            pid_t p = check(fork());

            do {
                if(count % 2 != 0) game_flag = false;
                if (p) {
                    mqd_t mqd = check(mq_open("/mymq", O_RDWR, S_IRWXU));
                    mqd_t mqd1 = check(mq_open("/mymq1",O_RDWR, S_IRWXU));
                    if(game_flag) M_QUEUE::guess_player(mqd, mqd1, p);
                    else
                    {
                        sleep(1);
                        M_QUEUE::assump_player(mqd, mqd1, p);
                    }
                }
                else
                {
                    mqd_t mqd = check(mq_open("/mymq", O_RDWR, S_IRWXU));
                    mqd_t mqd1 = check(mq_open("/mymq1",O_RDWR, S_IRWXU));
                    if(game_flag) M_QUEUE::assump_player(mqd, mqd1, p);
                    else
                    {
                        sleep(1);
                        M_QUEUE::guess_player(mqd, mqd1, p);
                    }
                }
                stat_display(count);

                count++;

                if (!game_flag) game_flag = true;

            }while(count < 11);

            exit(EXIT_SUCCESS);
        }
        case 3:
        {
            SIGNALS::prepare();

            pid_t main_id = getpid();
            srand(time(0));

            pid_t child_id = check(fork());

            bool isParent;

            pid_t IDParent;
            pid_t IDChild;
            IDParent = main_id;

            if (child_id > 0)
            {
                isParent = true;
                IDChild = child_id;
            }
            else
            {
                isParent = false;
                IDChild = getpid();
            }

            for (int i = 1; i < 11; i++)
            {
                if (i % 2 != 0)
                {
                    if (child_id == 0)
                    {
                        SIGNALS::assump_player(IDParent, isParent);
                    }
                    else
                    {
                        SIGNALS::guess_player(IDChild);
                    }
                }
                else
                {
                    if (child_id > 0)
                    {
                        SIGNALS::assump_player(IDChild, isParent);
                    }
                    else
                    {
                        SIGNALS::guess_player(IDParent);
                    }
                }
                stat_display(i);
            }
            if (child_id == 0)
            {
                printf("I'm child. I'm exiting now!\n");
                exit(EXIT_SUCCESS);
            }
            else
            {
                atexit(SIGNALS::on_ended);
                exit(EXIT_FAILURE);
            }
        }
        default:
        {
            exit(EXIT_FAILURE);
        }
    }

}


/*
int main()
{

}
// time, attempts
*/
