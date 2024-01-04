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
        request->setResponseCallback(CC_CALLBACK_2(Battlefield::uploadCallback, battlefield));
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
		request->setResponseCallback(CC_CALLBACK_2(Battlefield::downloadCallback, battlefield));
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
        file += std::to_string((*p)->getID());

        //棋子星级
        file += std::to_string((*p)->getStar());

        //棋子坐标
        HeroPosition coord = (*p)->getHeroPosition();
        file += std::to_string(coord.x);
        file += std::to_string(coord.y);
    }

    log("%s", file.c_str());
    return file;
}

void httpTransmission::convert(const std::string file)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    if (file.empty())   //空串特判（代表敌方棋盘上没有任何棋子）
    {
        littlehero->setEnemyFightingHeroes({});
        return;
    }

    std::string::const_iterator p;
    Hero* hero;
    Vector<Hero*> heroData;
    int x, y;

    for (p = file.begin(); p != file.end(); p++)
        switch ((p - file.begin()) % 4)
        {
        case 0: //棋子种类
            hero = Hero::createExactHero(static_cast<HeroType>(*p - '0'));
            break;
        case 1: //棋子星级
            hero->setStar(*p - '0');
            break;
        case 2: //棋子横坐标
            x = 7 - (*p - '0');
            break;
        case 3: //棋子纵坐标
            y = *p - '0';
            hero->setHeroPosition({ x, y });
            hero->setPosition(LHcontroler::getInstance()->getMyLittleHero()->getmidposition(x, y));
            heroData.pushBack(hero);
            break;
        default:
            break;
        }

    littlehero->setEnemyFightingHeroes(heroData);
}