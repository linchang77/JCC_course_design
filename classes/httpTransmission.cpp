#include "httpTransmission.h"
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

void httpTransmission::upload(Battlefield* battlefield)
{
    auto littlehero = LHcontroler::getInstance()->heros.at(0);
    
    //������������
    {
        std::string file = heroDataToString(littlehero->fightheros);   //����������ת��Ϊ�ַ���
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

    //����ССӢ��Ѫ��
    {
        std::string file = std::to_string(littlehero->getHp());   //��ССӢ��Ѫ��ת��Ϊ�ַ���
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
    auto littlehero = LHcontroler::getInstance()->heros.at(0);

    if (littlehero == nullptr)
        log("littlehero is null.");
    else
    {
        auto request = new HttpRequest;
        //��ȡ�з����ӱ�
        request->setUrl("GameServer.org\\aboutHeroes");
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(Battlefield::heroesCallback, battlefield));
        HttpClient::getInstance()->send(request);
        //��ȡ�з�Ѫ��
        request->setUrl("GameServer.org\\aboutLittleHero");
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(Battlefield::hpCallback, battlefield));
        HttpClient::getInstance()->send(request);
        //�������
        request->release();
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
        file += '\n';
    }
    file += '0';    //�ļ��Ե���0��β

    return file;
}

Vector<Hero*> httpTransmission::stringToHeroData(std::string file)
{
    std::string::iterator p = file.begin();
    Vector<Hero*> heroData;

    while (p != file.end())
    {
        for (int i = 0; *p != '\n'; i++, p++)  //һ������ѭ��
        {
            std::string current;    //��������
            while (*p != ' ')
                current += *p++;
            switch (i)
            {
                case 0:
                {
                    int id = std::stoi(current);
                    if (id)
                    {
                        auto hero = Hero::createExactHero(static_cast<HeroType>(id));
                        heroData.pushBack(hero);
                    }
                    else
                        return heroData;    //һ����0��ͷ��ʾ����
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
