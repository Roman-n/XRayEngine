﻿#include "StdAfx.h"
#include "UIProgressShape.h"

#include "UIStatic.h"

CUIProgressShape::CUIProgressShape()
{
    m_pBackground = NULL;
    m_bText       = false;
    m_pTexture    = xr_new<CUIStatic>();
    AttachChild(m_pTexture);
    m_pBackground = xr_new<CUIStatic>();
    AttachChild(m_pBackground);
};

CUIProgressShape::~CUIProgressShape()
{
    xr_delete(m_pTexture);
    xr_delete(m_pBackground);
}

void CUIProgressShape::SetPos(float pos)
{
    m_stage = pos;
}

void CUIProgressShape::SetPos(int pos, int max)
{
    m_stage = float(pos) / float(max);
    if (m_bText)
    {
        string256 _buff;
        m_pTexture->SetText(itoa(pos, _buff, 10));
    }
}

void CUIProgressShape::SetTextVisible(bool b)
{
    m_bText = b;
}

void _make_rot(Fvector2& pt, const Fvector2& src, float sin_a, float cos_a, float angle)
{
    pt.x = src.x * cos_a + src.y * sin_a;
    pt.y = src.y * cos_a - src.x * sin_a;
}

float calc_color(u32 idx, u32 total, float stage, float max_stage)
{
    float kk = (stage / max_stage) * (float(total + 1));
    float f  = 1 / (exp((float(idx) - kk) * 0.9f) + 1.0f);

    return f;
}

void CUIProgressShape::Draw()
{
    if (m_pBackground)
        m_pBackground->Draw();
    R_ASSERT(m_pTexture);

    if (m_bText)
        m_pTexture->DrawText();

    /*UIRender->SetShader(Shade *this->));*/
    Fvector2 tsize;
    UIRender->GetActiveTextureResolution(tsize);

    UIRender->StartPrimitive(m_sectorCount * 3, IUIRender::ptTriList, IUIRender::pttTL);

    Frect pos_rect;
    m_pTexture->GetAbsoluteRect(pos_rect);
    UI()->ClientToScreenScaled(pos_rect.lt, pos_rect.x1, pos_rect.y1);
    UI()->ClientToScreenScaled(pos_rect.rb, pos_rect.x2, pos_rect.y2);

    Fvector2 center_pos;
    pos_rect.getcenter(center_pos);

    Frect tex_rect = m_pTexture->GetUIStaticItem().GetOriginalRect();

    tex_rect.lt.x /= tsize.x;
    tex_rect.lt.y /= tsize.y;
    tex_rect.rb.x /= tsize.x;
    tex_rect.rb.y /= tsize.y;

    Fvector2 center_tex;
    tex_rect.getcenter(center_tex);

    float    radius_pos = pos_rect.width() / 2.0f;
    float    radius_tex = tex_rect.width() / 2.0f;

    float    curr_angle = 0.0f;
    float    sin_a      = sinf(curr_angle);
    float    cos_a      = cosf(curr_angle);
    Fvector2 start_pos_pt, prev_pos_pt;
    Fvector2 start_tex_pt, prev_tex_pt;

    start_pos_pt.set(0.0f, -radius_pos);
    prev_pos_pt = start_pos_pt;

    start_tex_pt.set(0.0f, -radius_tex);
    prev_tex_pt = start_tex_pt;

    for (u32 i = 0; i < m_sectorCount; ++i)
    {
        float ffff  = calc_color(i + 1, m_sectorCount, m_stage, 1.0f);
        u32   color = color_argb_f(ffff, 1.0f, 1.0f, 1.0f);

        UIRender->PushPoint(center_pos.x, center_pos.y, 0, color, center_tex.x, center_tex.y);

        Fvector2 tp, tp1;
        tp.set(prev_pos_pt);
        tp.add(center_pos);

        Fvector2 tx, tx1;
        tx.set(prev_tex_pt);
        tx.add(center_tex);

        if (m_bClockwise)
            curr_angle -= PI_MUL_2 / float(m_sectorCount);
        else
            curr_angle += PI_MUL_2 / float(m_sectorCount);

        sin_a = sinf(curr_angle);
        cos_a = cosf(curr_angle);

        _make_rot(prev_pos_pt, start_pos_pt, sin_a, cos_a, curr_angle);
        _make_rot(prev_tex_pt, start_tex_pt, sin_a, cos_a, curr_angle);

        tp1.set(prev_pos_pt);
        tp1.add(center_pos);

        tx1.set(prev_tex_pt);
        tx1.add(center_tex);

        if (m_bClockwise)
        {
            UIRender->PushPoint(tp.x, tp.y, 0, color, tx.x, tx.y);
            UIRender->PushPoint(tp1.x, tp1.y, 0, color, tx1.x, tx1.y);
        }
        else
        {
            UIRender->PushPoint(tp1.x, tp1.y, 0, color, tx1.x, tx1.y);
            UIRender->PushPoint(tp.x, tp.y, 0, color, tx.x, tx.y);
        }
        //std::swap					(*(pv-1), *(pv-2));
    }

    UIRender->FlushPrimitive();

    //	if(!m_bClockwise)
    //		RCache.set_CullMode			(CULL_CCW);
}
