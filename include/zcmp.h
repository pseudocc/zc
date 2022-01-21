#ifndef Z_COMPARE_H
#define Z_COMPARE_H

typedef int (*cmpf)(const void*, const void*);

extern cmpf zcmp_i8;
extern cmpf zcmp_i16;
extern cmpf zcmp_i32;
extern cmpf zcmp_i64;

extern cmpf zcmp_u8;
extern cmpf zcmp_u16;
extern cmpf zcmp_u32;
extern cmpf zcmp_u64;

extern cmpf zcmp_f16;
extern cmpf zcmp_f32;

extern cmpf zcmp_str;
extern cmpf zcmp_obj;

#endif
