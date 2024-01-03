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
{//ʱ���ǩ
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
{//�ִα�ǩ
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
{//ս��״̬��ǩ
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
{//��������bfsѰ·
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
    virtual void Fight_base(float dt);  //ս���׶�
    int solve_distance(Hero *Hero1,Hero *Hero2);  //�����
    void FindType();    //���
    void ChangeType(bool My1,int Type[],bool HasHero[]);   //��ĳ����
    void FetterInit(int Type[]);   //�ͼ��ĳ�ʼ��
    void giveAttribute(int Type[],bool My1);  //�����Լӳ�
    void addFetters();     //���ͼ���ע��
    bool Findenemy(Hero *Hero1);   //Ѱ�к���
    bool endCheck();    
    bool Find_way(Hero *Hero1);  //��·��Hero1���������

    bool Hasenemy(Hero* Hero1, Hero* Hero2);  //������
    bool getIsMyHero() { return is_my_hero; }
    void MatchAI(); //ƥ��AI���ԵñȽ��棩
    HeroPosition bfs(Hero *WantFind);  //Ѱ·����
    bool trueposition(int x, int y);  //λ���Ƿ���ȷ
    bool isfunction(Hero* Hero1);  //�Ƿ��������������
    void somebodydead(Hero* e,bool isMy);  //�������ˣ���������
    int getsmallturn() { return small_turn; }  //���С�ִ�
    int getbigturn() { return big_turn; }  //��ô��ִ�
    void putHeros();  //�������ӣ�AI��
    void pullHeros();  //�����ӣ�Ŀǰֻ�м�����
    void Map1init();  //��ͼ��ʼ��������Ѱ·��
    void threeLabelsInit();  //��ǩ��ʼ��
    void makeallVectorEmpty();  //���vector
    void removeAllLabels();  //������б�ǩ
    bool isFace(Hero *Hero1,Hero* Hero2); //�ж�����Ӣ���Ƿ������
    bool isFace(HeroPosition HPT1,HeroPosition HPT2); //�ж�����λ���Ƿ����㡰����桱
    void solveAllDead();  //һ���Դ����������������
    void giveLittleHeroDamage();  
    Vector<Hero*> getMyHeroUse() { return My_Hero_use; }
    Vector<Hero*> getEnemyHeroUse() { return Enemy_Hero_use; }
private:
    //���������·�ĸ�����
    bool vis[8][4]; //���·������¼����
    Vector<way_Node*> que; //���·��������
    Vector<Sprite*> Fetters;    //�
    Vector<Label*> Fetter_Labels;  //��ǩ
=======
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
>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
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
<<<<<<< HEAD
    bool is_my_hero = 1;   //�ж�����ִ�ж�������˭
    int is_Fight = 0;  
    bool isAllend = 0;
    bool Has_Match_AI[4] = { 0,0,0,0 };
    HeroPosition start; //����������·��
    bool Map1[8][4] = {0}; //��ͼ

};
//������ǩ�����ǵ�������ʵҲ���Բ��õ�����
static fight* Fight_layer = NULL;
=======
    int is_my_hero = 1;
   // HeroPosition start, end; //����������·��
    bool Map1[8][4]; //��ͼ
};

>>>>>>> affd7e5c2e4d7c4aa9b3e774deec4501f5a7068c
static turn_label* turn_l = NULL;
static time_label* time_l = NULL;
static Isfight_label* Isfight_l = NULL;
#endif