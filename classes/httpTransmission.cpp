#include "httpTransmission.h"
#include <fstream>
USING_NS_CC;
using namespace network;

//��������
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
    std::string parameters("?player_name=" + littlehero->ID + "&type=join_game");    //player_name=��ϷID&type=join_game

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
    std::string parameters("?player_name=" + littlehero->ID + "&type=get_player&seq=2&room_num=" + littlehero->room_num);    //player_name=��ϷID&type=get_player&seq=���&room_num=�����

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
	std::string parameters = write(littlehero->fightheros);   //����������ת��Ϊ�ַ���

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
    std::string parameters("?player_name=" + littlehero->ID + "&type=get_battlefield&seq=" + std::to_string(3 - littlehero->seq) + "&room_num=" + littlehero->room_num);    //player_name=��ϷID&type=get_battlefield&seq=���&room_num=�����

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
    std::string file("?player_name=" + littlehero->ID + "&type=set_battlefield&seq=" + std::to_string(littlehero->seq) + "&room_num=" + littlehero->room_num);  //player_name=���ID&type=set_battlefield&seq=���&room_num=�����
    Vector<Hero*>::iterator p;

    file += "&chess=";
    for (p = herodata.begin(); p != herodata.end(); p++)
    {
        //��������
        file += std::to_string((*p)->getID()) + ' ';

        //�����Ǽ�
        file += std::to_string((*p)->getStar()) + ' ';

        //��������
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

    if (file.empty())   //�մ����У�����з�������û���κ����ӣ�
        littlehero->setEnemyFightingHeroes({});

    std::string str1, str2;
    Hero* hero;
    Vector<Hero*> heroData;
    std::ofstream fout("EnemyInfo.txt");
    

    //д���ļ�
    fout << file;
    fout.close();

    //��ȡ�ļ�
    std::ifstream fin("EnemyInfo.txt");
    if (fin.is_open())
    {
        for (int i = 0; i < 2; i++)
        {
            fin >> str1;    //���ID
            if (str1 == littlehero->ID)    //���������ֶ�ʱ������
            {
                while (true)
                {
                    fin >> str1;
                    if (str1 == "end")
                        break;
                }
            }
            else    //�����з��ֶ�ʱ�Ų���
            {
				fin >> str1;    //�з�Ѫ��
				littlehero->setEnemyHp(std::stoi(str1));
                while (true)
                {
                    //�������ࣨҲ������end�ֶΣ�
                    fin >> str1;
                    if (str1 == "end")
                        break;
                    hero = Hero::createExactHero(static_cast<HeroType>(std::stoi(str1)));

                    //�����Ǽ�
                    fin >> str1;
                    hero->setStar(std::stoi(str1));

                    //��������
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
