#pragma once
#include <d2d1.h>

enum class EColor
{
    White,
    Black,
    Red,
    Green,
    Blue,
    Aqua,
    Yellow,
    Orange,
    Purple,
    Mint,
    LightMint,
    LightPink,
    LightBlue,
    LightYellow,
    LightOrange
};

// EColor -> D2D1::ColorF 변환 함수
inline D2D1::ColorF ToColorF(EColor color)
{
    switch (color)
    {
    case EColor::White:      return D2D1::ColorF(D2D1::ColorF::White);
    case EColor::Black:      return D2D1::ColorF(D2D1::ColorF::Black);
    case EColor::Red:        return D2D1::ColorF(D2D1::ColorF::Red);
    case EColor::Green:      return D2D1::ColorF(D2D1::ColorF::Green);
    case EColor::Blue:       return D2D1::ColorF(D2D1::ColorF::Blue);
    case EColor::Aqua:       return D2D1::ColorF(D2D1::ColorF::Aqua);
    case EColor::Yellow:     return D2D1::ColorF(D2D1::ColorF::Yellow);
    case EColor::Orange:     return D2D1::ColorF(D2D1::ColorF::Orange);
    case EColor::Purple:     return D2D1::ColorF(D2D1::ColorF::Purple);
    case EColor::Mint:       return D2D1::ColorF(D2D1::ColorF(0.243f, 0.705f, 0.537f, 1.0f));
    case EColor::LightMint:  return D2D1::ColorF(0.706f, 0.902f, 0.824f);
    case EColor::LightPink:  return D2D1::ColorF(1.0f, 0.714f, 0.757f);
    case EColor::LightBlue:  return D2D1::ColorF(0.678f, 0.847f, 0.902f);
    case EColor::LightYellow:return D2D1::ColorF(1.0f, 1.0f, 0.878f);
    case EColor::LightOrange:return D2D1::ColorF(1.0f, 0.784f, 0.588f);
    default:             return D2D1::ColorF(D2D1::ColorF::White);
    }
}
