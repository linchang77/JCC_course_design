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
    //ս���׶�
    int solve_distance(Hero *Hero1,Hero *Hero2);
    //�����
    bool Findenemy(Hero *Hero1);
    //Ѱ�к���
    bool Find_way(Hero *Hero1,Hero *Hero2);
    //��·����1��2��
    bool Hasenemy(Hero* Hero1, Hero* Hero2);
    void add_ai();
    //������
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
    //���������·�ĸ�����
    bool vis[8][4]; //���·������¼����
    //Vector<way_Node> que; //���·��������
    Vector<Hero*> My_Hero_use; //�Ҿ�
    Vector<Hero*> Enemy_Hero_use; //�о�
    time_label* time_l1;
    turn_label* turn_l1;
    Isfight_label* Isfight_l1;
    int enemys = 0; //��������
    int mys = 0; //�Ѿ�����
    float timef = 0; //ʱ���¼
    int big_turn = 1; //����
    int last_time = MaxTime; //ʣ��ʱ��
    int small_turn = 1; //С��
    int is_my_hero = 1;
   // HeroPosition start, end; //����������·��
    bool Map1[8][4]; //��ͼ
};

static turn_label* turn_l = NULL;
static time_label* time_l = NULL;
static Isfight_label* Isfight_l = NULL;
#endif