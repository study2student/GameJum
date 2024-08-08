#include <sstream>
#include "AsoUtility.h"

std::vector<std::string> AsoUtility::Split(std::string& line, char delimiter)
{

    // ���I�z��̕Ԃ�l������
    std::vector<std::string> result;

    // �����񑀍�p�̃N���X�ɒu��������
    std::istringstream stream(line);

    std::string field;

    // stream�����ɓǂݍ��݁A
    // ��R�����Ŏw�肳�ꂽ�����܂ł��Q�����ɕԂ�
    while (getline(stream, field, delimiter)) {
        // ���I�z��ɒǉ�
        result.push_back(field);
    }

    // ��F"aaa,bbb,ccc"
    // �@�@��result[0] = aaa
    // �@�@�@result[1] = bbb
    // �@�@�@result[2] = ccc

    return result;

}

int AsoUtility::Round(float value)
{
    return static_cast<int>(round(value));
}

Vector2 AsoUtility::Round(Vector2F value)
{
    Vector2 ret;
    ret.x = static_cast<int>(round(value.x));
    ret.y = static_cast<int>(round(value.y));
    return ret;
}

Vector2 AsoUtility::Round(float x, float y)
{
    Vector2 ret;
    ret.x = static_cast<int>(round(x));
    ret.y = static_cast<int>(round(y));
    return ret;
}

Vector2F AsoUtility::Normalize(AsoUtility::DIR dir)
{
    Vector2F ret;

    switch (dir)
    {
    case AsoUtility::DIR::UP:
        ret = { 0.0f, -1.0f };
        break;
    case AsoUtility::DIR::RIGHT:
        ret = { 1.0f, 0.0f };
        break;
    case AsoUtility::DIR::DOWN:
        ret = { 0.0f, 1.0f };
        break;
    case AsoUtility::DIR::LEFT:
        ret = { -1.0f, 0.0f };
        break;
    }

    return ret;
}
