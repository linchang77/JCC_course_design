#ifndef FIGHT_H
#define FIGHT_H
#include "cocos2d.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
#define MaxTime 20
#define SIZE_THREE 40
USING_NS_CC;
class time_label :public Label
{//时间标签
public:
    CREATE_FUNC(time_label);
    virtual bool init();
    static time_label* getInstance();
    virtual void update_time(int x);
    void clearInstance();
private:
    Label* Showtime;
    int num = 0;
};
class turn_label :public Label
{//轮次标签
public:
    CREATE_FUNC(turn_label);
    virtual bool init();
    static turn_label* getInstance();
    void clearInstance();
    virtual void update_turns(int bigt, int smallt);
private:
    Label* Showturn;
    int big_turn = 1;
    int small_turn = 1;
};
class Isfight_label :public Label
{//战斗状态标签
public:
    CREATE_FUNC(Isfight_label);
    virtual bool init();
    static Isfight_label* getInstance();
    virtual void update_Isfight(int x);
    void clearInstance();
private:
    Label* ShowIsfight;
    bool Isfight = 0;
};
class way_Node:public Node
{//用来辅助bfs寻路
public:
    HeroPosition place;
    way_Node* pre;
    way_Node(HeroPosition x, way_Node* p)
    {
        place = x;
        pre = p;
    }
};
class fight:public Layer
{
public:
    CREATE_FUNC(fight);
    virtual bool init();
    virtual void Fight_base(float dt);  //战斗阶段
    int solve_distance(Hero *Hero1,Hero *Hero2);  //求距离
    
    bool Findenemy(Hero *Hero1);   //寻敌函数
    
    bool Find_way(Hero *Hero1);  //找路从Hero1打到任意敌人
    
    bool Hasenemy(Hero* Hero1, Hero* Hero2);  //测试器

    void Match(); //匹配敌人
    void MatchAI(); //匹配AI（显得比较真）
    HeroPosition bfs(Hero *WantFind);  //寻路函数
    bool trueposition(int x, int y);  //位置是否正确
    bool isfunction(Hero* Hero1);  //是否该棋子在做动作
    void somebodydead(Hero* e,bool isMy);  //有人死了，死亡处理
    int getsmallturn() { return small_turn; }  //获得小轮次
    int getbigturn() { return big_turn; }  //获得大轮次
    void putHeros();  //创造棋子（虚假的AI）
    void pullHeros();  //放棋子（目前只有己方）
    void Map1init();  //地图初始化（辅助寻路）
    void threeLabelsInit();  //标签初始化
    void makeallVectorEmpty();  //清空vector
    void removeAllLabels();  //清空所有标签
    bool isFace(Hero *Hero1,Hero* Hero2); //判断两个英雄是否面对面
    bool isFace(HeroPosition HPT1,HeroPosition HPT2);
    void Toturn(Hero* Hero1, Hero* Hero2); //判断一个人是不是该转头
    void solveAllDead();  //一次性处理所有死人情况。
    void giveLittleHeroDamage();
private:
    //用来求最短路的辅助类
    bool vis[8][4]; //最短路辅助记录数组
    Vector<way_Node*> que; //最短路辅助容器
    Hero* AIHero[3];
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
    int is_Fight = 0;  
    HeroPosition start; //用来辅助算路径
    bool Map1[8][4]; //地图
};
//三个标签：都是单例（其实也可以不用单例）
static turn_label* turn_l = NULL;
static time_label* time_l = NULL;
static Isfight_label* Isfight_l = NULL;
#endif