#ifndef _STDARG_H_
#define _STDARG_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __MWERKS__
typedef struct
{
    char gpr;
    char fpr;
    char reserved[2];
    char* input_arg_area;
    char* reg_save_area;
} __va_list[1];
typedef __va_list va_list;

#ifndef __MWERKS__
extern void __builtin_va_info(va_list*);
#endif

void* __va_arg(va_list v_list, unsigned char type);

#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
#define va_arg(ap, t) (*((t*)__va_arg(ap, _var_arg_typeof(t))))
#define va_end(ap) (void)0

#else
// ProDG (gcc 2.95) SysV PowerPC varargs
typedef struct __va_list_tag
{
    char gpr;
    char fpr;
    unsigned short reserved;
    char* overflow_arg_area;
    char* reg_save_area;
} va_list[1];

#define va_start(AP, LASTARG) (__builtin_next_arg(LASTARG), AP[0] = *(__va_list_tag*)__builtin_saveregs())
#define va_arg(AP, TYPE)                                                                                              \
    (*({                                                                                                              \
        TYPE* __ptr;                                                                                                  \
        if (__builtin_classify_type((TYPE)0) == 8)                                                                    \
        {                                                                                                             \
            if ((AP)->fpr <= 7)                                                                                       \
            {                                                                                                         \
                __ptr = (TYPE*)((AP)->reg_save_area + 32 + (AP)->fpr * 8);                                            \
                (AP)->fpr++;                                                                                          \
            }                                                                                                         \
            else                                                                                                      \
            {                                                                                                         \
                __ptr = (TYPE*)(AP)->overflow_arg_area;                                                               \
                (AP)->overflow_arg_area += 8;                                                                         \
            }                                                                                                         \
        }                                                                                                             \
        else                                                                                                          \
        {                                                                                                             \
            if ((unsigned)((AP)->gpr + 1) <= 8)                                                                       \
            {                                                                                                         \
                __ptr = (TYPE*)((AP)->reg_save_area + (AP)->gpr * 4);                                                 \
                (AP)->gpr++;                                                                                          \
            }                                                                                                         \
            else                                                                                                      \
            {                                                                                                         \
                if ((AP)->gpr <= 7)                                                                                   \
                    (AP)->gpr = 8;                                                                                    \
                __ptr = (TYPE*)(AP)->overflow_arg_area;                                                               \
                (AP)->overflow_arg_area += 4;                                                                         \
            }                                                                                                         \
        }                                                                                                             \
        __ptr;                                                                                                        \
    }))
#define va_end(v) (void)0
#endif

#ifdef __cplusplus
}
#endif

#endif
