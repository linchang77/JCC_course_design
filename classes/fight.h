#ifndef FIGHT_H
#define FIGHT_H
#include "cocos2d.h"
#include"CCVector.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
#define MaxTime 20
#define SIZE_THREE 40
USING_NS_CC;
class time_label :public Label
{
public:
    CREATE_FUNC(time_label);
    virtual bool init();
    static time_label* getInstance();
    virtual void update_time(int x);
private:
    Label* Showtime;
    int num = 0;
};
class turn_label :public Label
{
public:
    CREATE_FUNC(turn_label);
    virtual bool init();
    static turn_label* getInstance();
    virtual void update_turns(int bigt, int smallt);
private:
    Label* Showturn;
    int big_turn = 1;
    int small_turn = 1;
};
class Isfight_label :public Label
{
public:
    CREATE_FUNC(Isfight_label);
    virtual bool init();
    static Isfight_label* getInstance();
    virtual void update_Isfight(int x);
private:
    Label* ShowIsfight;
    bool Isfight = 0;
};
class fight:public Layer
{
public:
    CREATE_FUNC(fight);
    virtual bool init();
    virtual void Fight_base(float dt);
    //战斗阶段
    int solve_distance(Hero *Hero1,Hero *Hero2);
    //求距离
    bool Findenemy(Hero *Hero1);
    //寻敌函数
    bool Find_way(Hero *Hero1,Hero *Hero2);
    //找路（从1打到2）
    bool Hasenemy(Hero* Hero1, Hero* Hero2);
    void add_ai();
    //测试器
    void Match();
    //HeroPosition bfs();
    bool trueposition(int x, int y);
    bool isfunction(Hero* Hero1);
    void somebodydead(Hero* e,bool isMy);
    int getsmallturn() { return small_turn; }
    int getbigturn() { return big_turn; }
private:
    /*
    class way_Node
    {
    public:
        HeroPosition place;
        way_Node *pre;
        way_Node(HeroPosition x,way_Node *p)
        {
            place = x;
            pre = p;
        }
    };
    */
    //用来求最短路的辅助类
    bool vis[8][4]; //最短路辅助记录数组
    //Vector<way_Node> que; //最短路辅助容器
    Vector<Hero*> My_Hero_use; //我军
    Vector<Hero*> Enemy_Hero_use; //敌军
    time_label* time_l1;
    turn_label* turn_l1;
    Isfight_label* Isfight_l1;
    int enemys = 0; //敌人数量
    int mys = 0; //友军数量
    float timef = 0; //时间记录
    int big_turn = 1; //大轮
    int last_time = MaxTime; //剩余时间
    int small_turn = 1; //小轮
    int is_my_hero = 1;
   // HeroPosition start, end; //用来辅助算路径
    bool Map1[8][4]; //地图
};

static turn_label* turn_l = NULL;
static time_label* time_l = NULL;
static Isfight_label* Isfight_l = NULL;
#endif