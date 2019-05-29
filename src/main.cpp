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
    clock_t inter_time1, inter_time2;  
    startTime = clock();

    Search new_search;
    new_search.init();

    inter_time1 = clock();

    result.clear();
    new_search.search_cars(55961, 262074, result);

    inter_time2 = clock();

    print_result();

    endTime = clock();

    printf("init time  : %f s\n", (double)(inter_time1 - startTime) / CLOCKS_PER_SEC);
    printf("search time: %f s\n", (double)(inter_time2 - inter_time1) / CLOCKS_PER_SEC);
    printf("print time : %f s\n", (double)(endTime - inter_time2) / CLOCKS_PER_SEC);
    printf("total time : %f s\n", (double)(endTime - startTime) / CLOCKS_PER_SEC);

    return 0;
}