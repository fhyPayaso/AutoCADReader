/******************************************************************************
**  dwg2dxf - Program to convert dwg/dxf to dxf(ascii & binary)              **
**                                                                           **
**  Copyright (C) 2015 José F. Soriano, rallazz@gmail.com                    **
**                                                                           **
**  This library is free software, licensed under the terms of the GNU       **
**  General Public License as published by the Free Software Foundation,     **
**  either version 2 of the License, or (at your option) any later version.  **
**  You should have received a copy of the GNU General Public License        **
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.    **
******************************************************************************/

#include <iostream>
#include <algorithm>
#include "dx_iface.h"
#include "libdwgr.h"
#include "libdxfrw.h"

using namespace std;

bool dx_iface::printText(const std::string &fileI, dx_data *fData)
{
    unsigned int found = fileI.find_last_of(".");
    std::string fileExt = fileI.substr(found + 1);
    std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);
    cData = fData;
    currentBlock = cData->mBlock;

    bool success = false;
    if (fileExt == "DXF")
    {
        //loads dxf
        dxfRW *dxf = new dxfRW(fileI.c_str());
        success = dxf->read(this, false);
        delete dxf;
    }
    else if (fileExt == "DWG")
    {
        //loads dwg
        dwgR *dwg = new dwgR(fileI.c_str());
        success = dwg->read(this, false);
        delete dwg;
    }

//    if (success)
//    {
//        int size = cData->mBlock->ent.size();
//        cout << "dwg file object num: " << size << endl;
//        for (std::list<DRW_Entity *>::const_iterator it =
//                cData->mBlock->ent.begin(); it != cData->mBlock->ent.end(); ++it)
//        {
//            DRW_Entity *e = *it;
//            switch (e->eType)
//            {
//                case DRW::TEXT: // 文字
//                {
//                    std::cout << "Text ===> ";
//                    std::cout << static_cast<DRW_Text *>(e)->text << std::endl;
//                    break;
//                }
//                case DRW::MTEXT: // 多行文字
//                {
//                    cout << "MTEXT ===> ";
//                    std::cout << static_cast<DRW_MText *>(e)->text << std::endl;
//                    break;
//                }
//                case DRW::LINE: // 直线
//                {
//                    std::cout << "LINE ==================> " << std::endl;
//                    DRW_Line *obj = static_cast<DRW_Line *>(e);
//                    cout << "base point : x" << obj->basePoint.x << " y:" << obj->basePoint.y << endl;
//                    cout << "second point : x" << obj->secPoint.x << " y:" << obj->secPoint.y << endl;
//                    break;
//                }
//                case DRW::LWPOLYLINE:
//                {
//                    // 多段线
//                    cout << "LWPOLYLINE ==================> " << endl;
//                    DRW_LWPolyline *obj = static_cast<DRW_LWPolyline *>(e);
//                    for (auto vertex : obj->vertlist)
//                        cout << "vertex : x" << vertex->x << " y:" << vertex->y << endl;
//                    break;
//                }
//                case DRW::CIRCLE:
//                {
//                    // 圆
//                    cout << "Circle ==============> " << endl;
//                    DRW_Circle *obj = static_cast<DRW_Circle *>(e);
//                    cout << "base point : x" << obj->basePoint.x << " y:" << obj->basePoint.y << endl;
//                    cout << "radius : " << obj->radious << endl;
//                    break;
//                }
//
////                case DRW::E3DFACE:
////                {
////                    std::cout << "E3DFACE ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMENSION:
////                {
////                    std::cout << "DIMENSION ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMLINEAR:
////                {
////                    std::cout << "DIMLINEAR ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMDIAMETRIC:
////                {
////                    std::cout << "DIMDIAMETRIC ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMANGULAR:
////                {
////                    std::cout << "DIMANGULAR ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMANGULAR3P:
////                {
////                    std::cout << "DIMANGULAR3P ===> " << std::endl;
////                    break;
////                }
////                case DRW::DIMORDINATE:
////                {
////                    std::cout << "DIMORDINATE ===> " << std::endl;
////                    break;
////                }
////                case DRW::ELLIPSE:
////                {
////                    std::cout << "ELLIPSE ===> " << std::endl;
////                    break;
////                }
////                case DRW::HATCH:
////                {
////                    std::cout << "HATCH ===> " << std::endl;
////                    break;
////                }
////                case DRW::IMAGE:
////                {
////                    std::cout << "IMAGE ===> " << std::endl;
////                    break;
////                }
////                case DRW::INSERT:
////                {
////                    std::cout << "INSERT ===> " << std::endl;
////                    break;
////                }
////                case DRW::LEADER:
////                {
////                    std::cout << "LEADER ===> " << std::endl;
////                    break;
////                }
////                case DRW::POINT:
////                {
////                    std::cout << "POINT ===> " << std::endl;
////                    break;
////                }
////                case DRW::POLYLINE:
////                {
////                    std::cout << "POLYLINE ===> " << std::endl;
////                    break;
////                }
////                case DRW::RAY:
////                {
////                    std::cout << "RAY ===> " << std::endl;
////                    break;
////                }
////                case DRW::SOLID:
////                {
////                    std::cout << "SOLID ===> " << std::endl;
////                    break;
////                }
////                case DRW::SPLINE:
////                {
////                    std::cout << "SPLINE ===> " << std::endl;
////                    break;
////                }
////                case DRW::TRACE:
////                {
////                    std::cout << "TRACE ===> " << std::endl;
////                    break;
////                }
////                case DRW::UNDERLAY:
////                {
////                    std::cout << "UNDERLAY ===> " << std::endl;
////                    break;
////                }
////                case DRW::VERTEX:
////                {
////                    std::cout << "VERTEX ===> " << std::endl;
////                    break;
////                }
////                case DRW::VIEWPORT:
////                {
////                    std::cout << "VIEWPORT ===> " << std::endl;
////                    break;
////                }
////                case DRW::XLINE:
////                {
////                    std::cout << "XLINE ===> " << std::endl;
////                    break;
////                }
////                case DRW::UNKNOWN:
////                {
////                    std::cout << "UNKNOWN ===> " << std::endl;
////                    break;
////                }
//                default:
//                    break;
//            }
//        }
//    }
    return success;
}


bool dx_iface::fileImport(const std::string &fileI, dx_data *fData)
{
    unsigned int found = fileI.find_last_of(".");
    std::string fileExt = fileI.substr(found + 1);
    std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::toupper);
    cData = fData;
    currentBlock = cData->mBlock;

    if (fileExt == "DXF")
    {
        //loads dxf
        dxfRW *dxf = new dxfRW(fileI.c_str());
        bool success = dxf->read(this, false);
        delete dxf;
        return success;
    }
    else if (fileExt == "DWG")
    {
        //loads dwg
        dwgR *dwg = new dwgR(fileI.c_str());
        bool success = dwg->read(this, false);
        delete dwg;
        return success;
    }
    std::cout << "file extension can be dxf or dwg" << std::endl;
    return false;
}

bool dx_iface::fileExport(const std::string &file, DRW::Version v, bool binary, dx_data *fData)
{
    cData = fData;
    dxfW = new dxfRW(file.c_str());
    bool success = dxfW->write(this, v, binary);
    delete dxfW;
    return success;

}

void dx_iface::writeEntity(DRW_Entity *e)
{
    switch (e->eType)
    {
        case DRW::POINT:
            dxfW->writePoint(static_cast<DRW_Point *>(e));
            break;
        case DRW::LINE:
            dxfW->writeLine(static_cast<DRW_Line *>(e));
            break;
        case DRW::CIRCLE:
            dxfW->writeCircle(static_cast<DRW_Circle *>(e));
            break;
        case DRW::ARC:
            dxfW->writeArc(static_cast<DRW_Arc *>(e));
            break;
        case DRW::SOLID:
            dxfW->writeSolid(static_cast<DRW_Solid *>(e));
            break;
        case DRW::ELLIPSE:
            dxfW->writeEllipse(static_cast<DRW_Ellipse *>(e));
            break;
        case DRW::LWPOLYLINE:
            dxfW->writeLWPolyline(static_cast<DRW_LWPolyline *>(e));
            break;
        case DRW::POLYLINE:
            dxfW->writePolyline(static_cast<DRW_Polyline *>(e));
            break;
        case DRW::SPLINE:
            dxfW->writeSpline(static_cast<DRW_Spline *>(e));
            break;
//    case RS2::EntitySplinePoints:
//        writeSplinePoints(static_cast<DRW_Point*>(e));
//        break;
//    case RS2::EntityVertex:
//        break;
        case DRW::INSERT:
            dxfW->writeInsert(static_cast<DRW_Insert *>(e));
            break;
        case DRW::MTEXT:
            dxfW->writeMText(static_cast<DRW_MText *>(e));
            break;
        case DRW::TEXT:
            dxfW->writeText(static_cast<DRW_Text *>(e));
            break;
        case DRW::DIMLINEAR:
        case DRW::DIMALIGNED:
        case DRW::DIMANGULAR:
        case DRW::DIMANGULAR3P:
        case DRW::DIMRADIAL:
        case DRW::DIMDIAMETRIC:
        case DRW::DIMORDINATE:
            dxfW->writeDimension(static_cast<DRW_Dimension *>(e));
            break;
        case DRW::LEADER:
            dxfW->writeLeader(static_cast<DRW_Leader *>(e));
            break;
        case DRW::HATCH:
            dxfW->writeHatch(static_cast<DRW_Hatch *>(e));
            break;
        case DRW::IMAGE:
            dxfW->writeImage(static_cast<DRW_Image *>(e), static_cast<dx_ifaceImg *>(e)->path);
            break;
        default:
            break;
    }
}
