#include "search.h"

using namespace std;

vector<Car> car_info;

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

void Search::init()
{
    clear();
    printf("clear success!\n");
    read_cars();
    printf("read car success!\n");
    //printf("print cars:\n");
    //print_cars();
}

void Search::clear()
{
    car_info.clear();
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