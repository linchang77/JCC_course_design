#ifndef FIGHT_H
#define FIGHT_H
#include "cocos2d.h"
#include"CCVector.h"
#include "Heroes.h"
#include "Map.h"
#include "Littlehero.h"
<<<<<<< HEAD
#define FetterPlace Vec2(50,948-200)
#define FetterDistance Vec2(0, -50)
#define FetterLabelPlace Vec2(150,948-200)
#define Fettersize 16
#define MaxTime 42
#define SIZE_THREE 40
#define ScaleNum 0.3f
#define DAMAGE 2
#define KINGBUFF 0.2f
USING_NS_CC;
class time_label :public Label
{//时间标签
=======
#define MaxTime 20
#define SIZE_THREE 40
USING_NS_CC;
class time_label :public Label
{
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
public:
    CREATE_FUNC(time_label);
    virtual bool init();
    static time_label* getInstance();
    virtual void update_time(int x);
<<<<<<< HEAD
    void clearInstance();
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
private:
    Label* Showtime;
    int num = 0;
};
class turn_label :public Label
<<<<<<< HEAD
{//轮次标签
=======
{
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
public:
    CREATE_FUNC(turn_label);
    virtual bool init();
    static turn_label* getInstance();
<<<<<<< HEAD
    void clearInstance();
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
    virtual void update_turns(int bigt, int smallt);
private:
    Label* Showturn;
    int big_turn = 1;
    int small_turn = 1;
};
class Isfight_label :public Label
<<<<<<< HEAD
{//战斗状态标签
=======
{
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
public:
    CREATE_FUNC(Isfight_label);
    virtual bool init();
    static Isfight_label* getInstance();
    virtual void update_Isfight(int x);
<<<<<<< HEAD
    void clearInstance();
=======
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
private:
    Label* ShowIsfight;
    bool Isfight = 0;
};
<<<<<<< HEAD
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
    static fight* getInstance();    
    static fight* clearInstance();
    virtual void Fight_base(float dt);  //战斗阶段
    int solve_distance(Hero *Hero1,Hero *Hero2);  //求距离
    void FindType();    //找羁绊
    void ChangeType(bool My1,int Type[],bool HasHero[]);   //看某羁绊个数
    void FetterInit(int Type[]);   //羁绊图标的初始化
    void giveAttribute(int Type[],bool My1);  //给属性加成
    void addFetters();     //放羁绊图标和注释
    bool Findenemy(Hero *Hero1);   //寻敌函数
    bool endCheck();    
    bool Find_way(Hero *Hero1);  //找路从Hero1打到任意敌人

    bool Hasenemy(Hero* Hero1, Hero* Hero2);  //测试器
    bool getIsMyHero() { return is_my_hero; }
    void MatchAI(); //匹配AI（显得比较真）
    HeroPosition bfs(Hero *WantFind);  //寻路函数
    bool trueposition(int x, int y);  //位置是否正确
    bool isfunction(Hero* Hero1);  //是否该棋子在做动作
    void somebodydead(Hero* e,bool isMy);  //有人死了，死亡处理
    int getsmallturn() { return small_turn; }  //获得小轮次
    int getbigturn() { return big_turn; }  //获得大轮次
    void putHeros();  //创造棋子（AI）
    void pullHeros();  //放棋子（目前只有己方）
    void Map1init();  //地图初始化（辅助寻路）
    void threeLabelsInit();  //标签初始化
    void makeallVectorEmpty();  //清空vector
    void removeAllLabels();  //清空所有标签
    bool isFace(Hero *Hero1,Hero* Hero2); //判断两个英雄是否面对面
    bool isFace(HeroPosition HPT1,HeroPosition HPT2); //判断两个位置是否满足“面对面”
    void solveAllDead();  //一次性处理所有死人情况。
    void giveLittleHeroDamage();  
    Vector<Hero*> getMyHeroUse() { return My_Hero_use; }
    Vector<Hero*> getEnemyHeroUse() { return Enemy_Hero_use; }
private:
    //用来求最短路的辅助类
    bool vis[8][4]; //最短路辅助记录数组
    Vector<way_Node*> que; //最短路辅助容器
    Vector<Sprite*> Fetters;    //羁绊
    Vector<Label*> Fetter_Labels;  //羁绊标签
=======
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
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
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
<<<<<<< HEAD
    bool is_my_hero = 1;   //判断正在执行动作的是谁
    int is_Fight = 0;  
    bool isAllend = 0;
    bool Has_Match_AI[4] = { 0,0,0,0 };
    HeroPosition start; //用来辅助算路径
    bool Map1[8][4] = {0}; //地图

};
//三个标签：都是单例（其实也可以不用单例）
static fight* Fight_layer = NULL;
=======
    int is_my_hero = 1;
   // HeroPosition start, end; //用来辅助算路径
    bool Map1[8][4]; //地图
};

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
static turn_label* turn_l = NULL;
static time_label* time_l = NULL;
static Isfight_label* Isfight_l = NULL;
#endif