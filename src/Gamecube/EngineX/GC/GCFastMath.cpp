#include "EngineX/GC/GCFastMath.h"

float GCSqrtf(float x)
{
    if (x != 0.0f)
    {
        // sqrt(x) = x * rsqrt(x), with two Newton-Raphson refinements of the hardware estimate
        float estimate;
        __asm__("frsqrte %0,%1" : "=f"(estimate) : "f"(x));
        float half = estimate * 0.5f;
        float y = half * (1.0f - x * estimate * estimate) + estimate;
        float halfRefined = y * 0.5f;
        y = halfRefined * (1.0f - x * y * y) + y;
        return x * y;
    }
    return 0.0f;
}
