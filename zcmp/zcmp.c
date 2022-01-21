#include <inttypes.h>
#include <string.h>
#include "include/zcmp.h"

#define ZCMP_CMP(l, r) (l > r ? 1 : l == r ? 0 : -1)
#define ZCMP_FUNC(ty) zcmp_priv_##ty
#define ZCMP_IMPL_NUM(var, ty) \
  static int ZCMP_FUNC(ty)(const void* l, const void* r) \
  { return ZCMP_CMP(*(ty*)l, *(ty*)r); } \
  static cmpf var = &ZCMP_FUNC_NAME(ty); \

ZCMP_IMPL_NUM(zcmp_i8, int8_t)
ZCMP_IMPL_NUM(zcmp_i16, int16_t)
ZCMP_IMPL_NUM(zcmp_i32, int32_t)
ZCMP_IMPL_NUM(zcmp_i64, int64_t)

ZCMP_IMPL_NUM(zcmp_u8, uint8_t)
ZCMP_IMPL_NUM(zcmp_u16, uint16_t)
ZCMP_IMPL_NUM(zcmp_u32, uint32_t)
ZCMP_IMPL_NUM(zcmp_u64, uint64_t)

ZCMP_IMPL_NUM(zcmp_f32, float)
ZCMP_IMPL_NUM(zcmp_f64, double)

static int zcmp_priv_str(const void* l, const void* r) {
  char* lstr = *(char**)l;
  char* rstr = *(char**)r;
  return strcmp(lstr, rstr);
}

static cmpf zcmp_obj = zcmp_u64;
