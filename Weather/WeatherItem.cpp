﻿#include "pch.h"
#include "WeatherItem.h"
#include "DataManager.h"

const wchar_t* CWeatherItem::GetItemName() const
{
    return g_data.StringRes(IDS_WEATHER);
}

const wchar_t* CWeatherItem::GetItemId() const
{
    return L"NdKZEf39";
}

const wchar_t* CWeatherItem::GetItemLableText() const
{
    return L"";
}

const wchar_t* CWeatherItem::GetItemValueText() const
{
    return L"";
}

const wchar_t* CWeatherItem::GetItemValueSampleText() const
{
    return L"";
}

bool CWeatherItem::IsCustomDraw() const
{
    return true;
}

int CWeatherItem::GetItemWidth() const
{
    return g_data.m_setting_data.m_display_width;
}

void CWeatherItem::DrawItem(void* hDC, int x, int y, int w, int h, bool dark_mode)
{
    //绘图句柄
    CDC* pDC = CDC::FromHandle((HDC)hDC);
    //矩形区域
    CRect rect(CPoint(x, y), CSize(w, h));
    if (g_data.m_setting_data.m_use_weather_icon)
    {
        //绘制天气图标
        const int icon_size{ g_data.DPI(16) };
        HICON hIcon = g_data.GetWeatherIcon(g_data.GetWeather().m_type);
        CPoint icon_point{ rect.TopLeft() };
        icon_point.x = rect.left + g_data.DPI(2);
        icon_point.y = rect.top + (rect.Height() - icon_size) / 2;
        ::DrawIconEx(pDC->GetSafeHdc(), icon_point.x, icon_point.y, hIcon, icon_size, icon_size, 0, NULL, DI_NORMAL);
        //绘制天气文本
        CRect rc_text{ rect };
        rc_text.left += (icon_size + g_data.DPI(4));
        pDC->DrawText(g_data.GetWeather().ToStringTemperature().c_str(), rc_text, DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    }
    else
    {
        pDC->DrawText(g_data.GetWeather().ToString().c_str(), rect, DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    }
}
