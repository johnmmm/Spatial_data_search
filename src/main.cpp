#include "GPTree.h"
#include "search.h"

vector< pair<int, int> > result;

inline int minone (int a, int b)
{
    if (a < b)
        return a;
    return b;
}

void print_result()
{
    printf("print result: \n");
    int size = minone(result.size(), 5);
    for (int i = 0; i < size; i++)
    {
        printf("Taxi num: %d, Total dis: %d\n", result[i].first, result[i].second);
    }
}

int main()
{
    clock_t startTime, endTime;
    clock_t inter_time1, inter_time2, init_time;  
    startTime = clock();

    Search new_search;
    new_search.init();
    init_time = clock();
    printf("init time  : %f s\n", (double)(init_time - startTime) / CLOCKS_PER_SEC);

    while(1)
    {
        inter_time1 = clock();

        int cur_pos, tar_pos;
        printf("Please input your current position and target position:\n");
        scanf("%d%d", &cur_pos, &tar_pos);
        if (cur_pos == 945841612)
        {
            printf("End now\n");
            break;
        }
        result.clear();
        new_search.search_cars(cur_pos, tar_pos, result);
        print_result();

        inter_time2 = clock();
        printf("search time: %f s\n", (double)(inter_time2 - inter_time1) / CLOCKS_PER_SEC);
    }
    
    endTime = clock();

    // printf("init time  : %f s\n", (double)(inter_time1 - startTime) / CLOCKS_PER_SEC);
    //printf("search time: %f s\n", (double)(inter_time2 - inter_time1) / CLOCKS_PER_SEC);
    //printf("print time : %f s\n", (double)(endTime - inter_time2) / CLOCKS_PER_SEC);
    printf("total time : %f s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

    return 0;
}