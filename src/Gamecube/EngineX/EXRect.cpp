#include "EngineX/EXRect.h"

#define Min(a, b) ((a) < (b) ? (a) : (b))
#define Max(a, b) ((a) > (b) ? (a) : (b))

EXRect IntersectRect(EXRect& rct1, EXRect& rct2)
{
    EXRect rct;
    EXPoint rct1br;
    EXPoint rct2br;
    EXPoint rctbr;

    rct1br.x = rct1.x + rct1.w;
    rct1br.y = rct1.y + rct1.h;
    rct2br.x = rct2.x + rct2.w;
    rct2br.y = rct2.y + rct2.h;

    rct.x = Max(rct1.x, rct2.x);
    rct.y = Max(rct1.y, rct2.y);
    rct.x = Min(rct.x, rct2br.x);
    rct.y = Min(rct.y, rct2br.y);

    rctbr.x = Max(rct1br.x, rct2.x);
    rctbr.y = Max(rct1br.y, rct2.y);
    rctbr.x = Min(rctbr.x, rct2br.x);
    rctbr.y = Min(rctbr.y, rct2br.y);

    rct.w = rctbr.x - rct.x;
    rct.h = rctbr.y - rct.y;
    return rct;
}
