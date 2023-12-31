#include "httpTransmission.h"
#include <fstream>
USING_NS_CC;
using namespace network;

//单例对象
static httpTransmission* s_SharedTransmissionTool = nullptr;

httpTransmission* httpTransmission::getInstance()
{
    if (!s_SharedTransmissionTool)
    {
        s_SharedTransmissionTool = new (std::nothrow) httpTransmission;
        CCASSERT(s_SharedTransmissionTool, "FATAL: Not enough memory");
    }

    return s_SharedTransmissionTool;
}

void httpTransmission::joinRoom(Room* room)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    std::string parameters("?player_name=" + littlehero->ID + "&type=join_game");    //player_name=游戏ID&type=join_game

    auto request = new HttpRequest;
    request->setUrl("http://123.60.14.84:888/chess_game.php" + parameters);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(Room::intoRoomCallback, room));
    HttpClient::getInstance()->send(request);
    request->release();
}

void httpTransmission::seekRoom(Room* room)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    std::string parameters("?player_name=" + littlehero->ID + "&type=get_player&seq=2&room_num=" + littlehero->room_num);    //player_name=游戏ID&type=get_player&seq=序号&room_num=房间号

    auto request = new HttpRequest;
    request->setUrl("http://123.60.14.84:888/chess_game.php" + parameters);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(Room::pollCallback, room));
    HttpClient::getInstance()->send(request);
    request->release();
}

void httpTransmission::upload(Battlefield* battlefield)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
	std::string parameters = write(littlehero->fightheros);   //将棋子数据转化为字符串

	if (littlehero == nullptr)
		log("littlehero is null.");
	else
	{
		auto request = new HttpRequest;
		request->setUrl("http://123.60.14.84:888/chess_game.php" + parameters);
		request->setRequestType(HttpRequest::Type::GET);
		HttpClient::getInstance()->send(request);
		request->release();
	}
}

void httpTransmission::download(Battlefield* battlefield)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    std::string parameters("?player_name=" + littlehero->ID + "&type=get_battlefield&seq=" + std::to_string(3 - littlehero->seq) + "&room_num=" + littlehero->room_num);    //player_name=游戏ID&type=get_battlefield&seq=序号&room_num=房间号

    if (littlehero == nullptr)
        log("littlehero is null.");
	else
	{
		auto request = new HttpRequest;
		request->setUrl("http://123.60.14.84:888/chess_game.php" + parameters);
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback(CC_CALLBACK_2(Battlefield::preparationCallback, battlefield));
		HttpClient::getInstance()->send(request);
		request->release();
	}
}

std::string httpTransmission::write(Vector<Hero*> herodata)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    std::string file("?player_name=" + littlehero->ID + "&type=set_battlefield&seq=" + std::to_string(littlehero->seq) + "&room_num=" + littlehero->room_num);  //player_name=玩家ID&type=set_battlefield&seq=序号&room_num=房间号
    Vector<Hero*>::iterator p;

    file += "&chess=";
    for (p = herodata.begin(); p != herodata.end(); p++)
    {
        //棋子种类
        file += std::to_string((*p)->getID()) + ' ';

        //棋子星级
        file += std::to_string((*p)->getStar()) + ' ';

        //棋子坐标
        HeroPosition coord = (*p)->getHeroPosition();
        file += std::to_string(coord.x) + ' ';
        file += std::to_string(coord.y) + ' ';
    }

    log("%s", file.c_str());
    return file;
}

void httpTransmission::convert(std::string file)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    if (file.empty())   //空串特判（代表敌方棋盘上没有任何棋子）
        littlehero->setEnemyFightingHeroes({});

    std::string str1, str2;
    Hero* hero;
    Vector<Hero*> heroData;
    std::ofstream fout("EnemyInfo.txt");
    

    //写入文件
    fout << file;
    fout.close();

    //读取文件
    std::ifstream fin("EnemyInfo.txt");
    if (fin.is_open())
    {
        for (int i = 0; i < 2; i++)
        {
            fin >> str1;    //玩家ID
            if (str1 == littlehero->ID)    //读到己方字段时不操作
            {
                while (true)
                {
                    fin >> str1;
                    if (str1 == "end")
                        break;
                }
            }
            else    //读到敌方字段时才操作
            {
				fin >> str1;    //敌方血量
				littlehero->setEnemyHp(std::stoi(str1));
                while (true)
                {
                    //棋子种类（也可能是end字段）
                    fin >> str1;
                    if (str1 == "end")
                        break;
                    hero = Hero::createExactHero(static_cast<HeroType>(std::stoi(str1)));

                    //棋子星级
                    fin >> str1;
                    hero->setStar(std::stoi(str1));

                    //棋子坐标
                    fin >> str1 >> str2;
                    hero->setHeroPosition({ std::stoi(str1), 7 - std::stoi(str2) });

                    heroData.pushBack(hero);
                }
            }
        }
        littlehero->setEnemyFightingHeroes(heroData);
        fin.close();
    }
    else
        log("file isn't open.");
}
