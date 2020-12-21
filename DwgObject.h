/* ====================================================
#   Copyright (C)2020 2021 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Date          : 2020/12/21
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/

#ifndef AUTOCADREADER_DWGOBJECT_H
#define AUTOCADREADER_DWGOBJECT_H

#include "libdxfrw/dx_data.h"

#include <iostream>

using namespace std;

class DwgObject
{
public:
    int type;

    DRW_Line entity_Line;

    DRW_LWPolyline entity_LWPolyline;

    DRW_Circle entity_Circle;

    DRW_Arc entity_Arc;

    DRW_Text entity_Text;

    DRW_MText entity_MText;

    void parse(DRW_Entity *e)
    {
        switch (e->eType)
        {
            case DRW::TEXT: // 文字
                entity_Text = *(static_cast<DRW_Text *>(e));
                break;
            case DRW::MTEXT: // 多行文字
                entity_MText = *(static_cast<DRW_MText *>(e));
                break;
            case DRW::LINE:
                entity_Line = *(static_cast<DRW_Line *>(e));
                break;
            case DRW::LWPOLYLINE:
                entity_LWPolyline = *(static_cast<DRW_LWPolyline *>(e));
                break;
            case DRW::CIRCLE:
                entity_Circle = *(static_cast<DRW_Circle *>(e));
                break;
            case DRW::ARC: //圆弧
                entity_Arc = *(static_cast<DRW_Arc *>(e));
                break;
            default:
                break;
        }
    }
};


#endif //AUTOCADREADER_DWGOBJECT_H
