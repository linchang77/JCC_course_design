#include "httpTransmission.h"
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

void httpTransmission::upload(Battlefield* battlefield)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();
    
    //传送棋子数据
    {
        std::string file = heroDataToString(littlehero->fightheros);   //将棋子数据转化为字符串
        if (littlehero == nullptr)
            log("littlehero is null.");
        else
        {
            auto request = new HttpRequest;
            request->setUrl("GameServer.org\\aboutHeroes");
            request->setRequestType(HttpRequest::Type::POST);
            request->setRequestData(file.c_str(), file.length());
            HttpClient::getInstance()->send(request);
            request->release();
        }
    }

    //传送小小英雄血量
    {
        std::string file = std::to_string(littlehero->getHp());   //将小小英雄血量转化为字符串
        if (littlehero == nullptr)
            log("littlehero is null.");
        else
        {
            auto request = new HttpRequest;
            request->setUrl("GameServer.org\\aboutLittleHero");
            request->setRequestType(HttpRequest::Type::POST);
            request->setRequestData(file.c_str(), file.length());
            HttpClient::getInstance()->send(request);
            request->release();
        }
    }
}

void httpTransmission::download(Battlefield* battlefield)
{
    auto littlehero = LHcontroler::getInstance()->getMyLittleHero();

    if (littlehero == nullptr)
        log("littlehero is null.");
    else
    { 
        //获取敌方棋子表
        {
            auto request = new HttpRequest;
            request->setUrl("file:///D:/SeniorGameProj/TerminalProj/enemyHeroes.txt");
            request->setRequestType(HttpRequest::Type::GET);
            request->setResponseCallback(CC_CALLBACK_2(Battlefield::heroesCallback, battlefield));
            HttpClient::getInstance()->send(request);
            request->release();
        }

        //获取敌方血量
        {
            auto request = new HttpRequest;
            request->setUrl("file:///D:/SeniorGameProj/TerminalProj/Hp.txt");
            request->setRequestType(HttpRequest::Type::GET);
            request->setResponseCallback(CC_CALLBACK_2(Battlefield::hpCallback, battlefield));
            HttpClient::getInstance()->send(request);
            request->release();
        }
    }
}

std::string httpTransmission::heroDataToString(Vector<Hero*> herodata)
{
    std::string file;
    Vector<Hero*>::iterator p;

    for (p = herodata.begin(); p != herodata.end(); p++)
    {
        file += std::to_string((*p)->getID());
        file += ' ';
        file += std::to_string((*p)->getPositionX());
        file += ' ';
        file += std::to_string((*p)->getPositionY());
        file += ' ';
        file += '/';    //不同棋子的数据之间用斜杠分隔
    }
    file += "-1 ";    //文件以-1结尾

    return file;
}

Vector<Hero*> httpTransmission::stringToHeroData(std::string file)
{
    std::string::iterator p;
    Vector<Hero*> heroData;

    for (p = file.begin(); p != file.end(); p++)
    {
        for (int i = 0; *p != '/'; i++, p++)  //一行数据循环
        {
            std::string current;    //单个数据
            while (*p != ' ')
                current += *p++;
            switch (i)
            {
                case 0:
                {
                    int id = std::stoi(current);
                    if (id != -1)
                    {
                        auto hero = Hero::createExactHero(static_cast<HeroType>(id));
                        heroData.pushBack(hero);
                        break;
                    }
                    else
                        return heroData;    //一行以0开头表示结束
                }
                case 1:
                {
                    float x = std::stof(current);
                    (*(heroData.end() - 1))->setPositionX(x);
                }
                    break;
                case 2:
                {
                    float y = std::stof(current);
                    (*(heroData.end() - 1))->setPositionY(y);
                }
                    break;
                default:
                    break;
            }
        }
    }

    return heroData;
}
