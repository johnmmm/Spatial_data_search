#include "search.h"

using namespace std;

vector< vector<int> > permutations[MAX_PASS+1];
vector<Car> car_info;

bool cmp_taxi(pair<int, int> a, pair<int, int> b) //升序排序
{ 
    return a.second < b.second;
}

void split_strs(string& str1, string& str2, vector<string>& res)
{
	string::size_type p1, p2;
	p1 = 0;  p2 = str1.find(str2);

    while(string::npos != p2)
    {
        if(p1 != p2)
        {
            string tmp = str1.substr(p1, p2-p1);
            res.push_back(tmp);
        }
        p1 = p2 + 1;
        p2 = str1.find(str2, p1);
    }
    if(p1 != str1.length())
    {
        string tmp = str1.substr(p1);
        res.push_back(tmp);
    }
}

Search::Search()
{

}

Search::~Search()
{

}

void Search::init_tree()
{
    gptree.init();
    gptree.read();
    gptree.build_tree();
    gptree.save();
}

void Search::init()
{
    clear();
    printf("clear success!\n");

    build_permutation();
    printf("build permutation success!\n");

    gptree.load();
    printf("Load tree success!\n");

    read_cars();
    printf("read car success!\n");

    //printf("print cars:\n");
    //print_cars();
}

void Search::init_dis_matrix(int cur_pos, vector<int>& tar_pos_vec)
{
    int size = tar_pos_vec.size();

    // clear
    for (int i = 0; i < MAX_PASS+1; i++)
        for (int j = 0; j < MAX_PASS+1; j++)
            dis_matrix[i][j] = 0;

    // init
    for (int i = 1; i <= size; i++)
    {
        dis_matrix[0][i] = gptree.get_min_distance(cur_pos, tar_pos_vec[i-1]);
        dis_matrix[i][0] = dis_matrix[0][i];
    }
    for (int i = 1; i <= size; i++)
    {
        for (int j = i + 1; j <= size; j++)
        {
            dis_matrix[i][j] = gptree.get_min_distance(tar_pos_vec[i-1], tar_pos_vec[j-1]);
            dis_matrix[j][i] = dis_matrix[i][j];
        }
    }
}

int Search::delivery_dis(int car_pos, vector<int>& tar_pos_vec)
{
    int min_dis = MAXN;
    int size = tar_pos_vec.size();

    if (size == 0)
    {
        min_dis = 0;
        return min_dis;
    }

    for (int i = 0; i < permutations[size].size(); i++)
    {
        int distance = 0;
        distance = dis_matrix[0][ permutations[size][i][0] ];

        for(int j = 1; j < size; ++j)
            distance += dis_matrix[ permutations[size][i][j-1] ][ permutations[size][i][j] ];
        if (distance < min_dis)
            min_dis = distance;
    }

    return min_dis;
}

void Search::search_cars(int cur_pos, int tar_pos, vector< pair<int, int> >& res)
{
    
    if (car_info.size() < 100000)
    {
        printf("Something must be wrong!\n");
        return;
    }
    for (int i = 0; i < 100000; i++)
    {
        if (car_info[i].pass_num >= 4)
            continue;
        double distance = Euclidean_Dist(car_info[i].pos, cur_pos);
        if (distance > 10000) // 也不知道为什么，这个加上就特别快
            continue;
        
        int D2 = gptree.get_min_distance(car_info[i].pos, cur_pos);
        if (D2 > 10000)
            continue;
        car_info[i].tar_pos.push_back(tar_pos);
        
        // D3这里为接到乘客后送人
        init_dis_matrix(cur_pos, car_info[i].tar_pos);
        int D3 = delivery_dis(cur_pos, car_info[i].tar_pos);
        int D4 = gptree.get_min_distance(cur_pos, tar_pos);
        car_info[i].tar_pos.pop_back();
        if (D3 - D4 > 10000)
            continue;

        // D1为直接送人
        init_dis_matrix(car_info[i].pos, car_info[i].tar_pos);
        int D1 = delivery_dis(car_info[i].pos, car_info[i].tar_pos);
        if (D2 + D3 - D1 > 10000)
            continue;

        // 可行的出租车
        //printf("Num: %d, D1: %d, D2: %d, D3: %d, D4: %d\n", i, D1, D2, D3, D4);
        res.emplace_back(i, D3 - D4 + D2 + D3 - D1);
        sort(res.begin(), res.end(), cmp_taxi);
    }
}

void Search::clear()
{
    car_info.clear();
    for (int i = 0; i < MAX_PASS+1; i++)
        permutations[i].clear();

    for (int i = 0; i < MAX_PASS+1; i++)
        for (int j = 0; j < MAX_PASS+1; j++)
            dis_matrix[i][j] = 0;
}

void Search::build_permutation()
{
    // 建立全排列
    for (int i = 1; i <= MAX_PASS; i++)
    {
        int arr[] = {1, 2, 3, 4};
        do
        {
            vector<int> one_per;
            one_per.clear();
            for (int j = 0; j < i; j++)
                one_per.push_back(arr[j]);
            permutations[i].push_back(one_per);
        } 
        while (next_permutation(arr,arr+i));
    }

    // for (int i = 1; i <= MAX_PASS; i++)
    // {
    //     int size = permutations[i].size();
    //     printf("num%d: ", i);
    //     for (int j = 0; j < size; j++)
    //     {
    //         printf("{");
    //         for (int k = 0; k < permutations[i][j].size(); k++)
    //         {
    //             printf("%d, ", permutations[i][j][k]);
    //         }
    //         printf("}, ");
    //     }
    //     printf("\n");
    // }
}

void Search::read_cars()
{
    char buf[1024];
    FILE *fp = fopen(car_file, "r");
    while (fgets(buf ,sizeof(buf), fp) != nullptr)
    {
        string tmp_str = string(buf);
		if(tmp_str[tmp_str.length()-1] == '\n')
			tmp_str.erase(tmp_str.length()-1);
        
        Car new_car;
        vector<string> res;
        res.clear();
        string split = " ";
        split_strs(tmp_str, split, res);
        if (res.size() < 2)
            continue;
        int pass_num = atoi(res[1].c_str());
        if (res.size() != pass_num+3)
        {
            printf("Not avaliable!\n");
            continue;
        }

        new_car.pass_num = pass_num;
        vector<string> tmp_pos;
        tmp_pos.clear();
        string split2 = ",";
        split_strs(res[2], split2, tmp_pos);
        new_car.pos = atoi(tmp_pos[2].c_str());

        for (int i = 0; i < pass_num; i++)
        {
            tmp_pos.clear();
            split_strs(res[i+3], split2, tmp_pos);
            new_car.tar_pos.push_back(atoi(tmp_pos[2].c_str()));
        }
        car_info.push_back(new_car);
    }
    fclose(fp);
}

void Search::print_cars()
{
    for (int i = 0; i < 10; i++)
    {
        printf("taxi_num: %d, taxi_pos: %d, pass_num: %d, target:\n", i, car_info[i].pos, car_info[i].pass_num);
        for (int j = 0; j < car_info[i].pass_num; j++)
        {
            printf("target: %d\n", car_info[i].tar_pos[j]);
        }
    }
}