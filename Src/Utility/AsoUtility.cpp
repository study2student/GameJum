#include <sstream>
#include "AsoUtility.h"

std::vector<std::string> AsoUtility::Split(std::string& line, char delimiter)
{

    // 動的配列の返り値を準備
    std::vector<std::string> result;

    // 文字列操作用のクラスに置き換える
    std::istringstream stream(line);

    std::string field;

    // streamを順に読み込み、
    // 第３引数で指定された文字までを第２引数に返す
    while (getline(stream, field, delimiter)) {
        // 動的配列に追加
        result.push_back(field);
    }

    // 例："aaa,bbb,ccc"
    // 　　⇒result[0] = aaa
    // 　　　result[1] = bbb
    // 　　　result[2] = ccc

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
