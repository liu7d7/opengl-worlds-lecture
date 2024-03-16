#pragma once

#include <stdint-gcc.h>
#include <intrin.h>
#include <stdbool.h>
#include <math.h>

typedef uint32_t uint;
typedef uint8_t byte;

#define max(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define min(a, b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define objdup(...) \
  ({ __typeof__ (__VA_ARGS__) _a = (__VA_ARGS__); \
     memcpy(malloc(sizeof(_a)), &_a, sizeof(_a));\
  })

typedef union v2f {
  struct {
    float x, y;
  };

  float v[2];
} v2f;

static const v2f v2_ux = (v2f){.x = 1};
static const v2f v2_uy = (v2f){.y = 1};

[[gnu::always_inline]]
inline static v2f v2_add(v2f lhs, v2f rhs) {
  return (v2f){lhs.x + rhs.x, lhs.y + rhs.y};
}

[[gnu::always_inline]]
inline static v2f v2_sub(v2f lhs, v2f rhs) {
  return (v2f){lhs.x - rhs.x, lhs.y - rhs.y};
}

[[gnu::always_inline]]
inline static v2f v2_mul(v2f lhs, float scalar) {
  return (v2f){lhs.x * scalar, lhs.y * scalar};
}

[[gnu::always_inline]]
inline static v2f v2_div(v2f lhs, float scalar) {
  return (v2f){lhs.x / scalar, lhs.y / scalar};
}

[[gnu::always_inline]]
inline static float v2_dot(v2f lhs, v2f rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

[[gnu::always_inline]]
inline static float v2_len(v2f a) {
  return sqrtf(v2_dot(a, a));
}

[[gnu::always_inline]]
inline static float v2_dist(v2f lhs, v2f rhs) {
  v2f delta = v2_sub(lhs, rhs);
  return v2_len(delta);
}

[[gnu::always_inline]]
inline static v2f v2_norm(v2f v) {
  float len = v2_len(v);
  return (v2f){.x = v.x / len, .y = v.y / len};
}

typedef union v2i {
  struct {
    int x, y;
  };

  int v[2];
} v2i;

static const v2i iv2_ux = (v2i){.x = 1};
static const v2i iv2_uy = (v2i){.y = 1};

[[gnu::always_inline]]
inline static v2i iv2_add(v2i lhs, v2i rhs) {
  return (v2i){lhs.x + rhs.x, lhs.y + rhs.y};
}

[[gnu::always_inline]]
inline static v2i iv2_add_i(v2i lhs, int rhs_x, int rhs_y) {
  return (v2i){lhs.x + rhs_x, lhs.y + rhs_y};
}

[[gnu::always_inline]]
inline static v2i iv2_sub(v2i lhs, v2i rhs) {
  return (v2i){lhs.x - rhs.x, lhs.y - rhs.y};
}

[[gnu::always_inline]]
inline static v2i iv2_mul(v2i lhs, int scalar) {
  return (v2i){lhs.x * scalar, lhs.y * scalar};
}

[[gnu::always_inline]]
inline static v2i iv2_div(v2i lhs, int scalar) {
  return (v2i){lhs.x / scalar, lhs.y / scalar};
}

[[gnu::always_inline]]
inline static int iv2_dot(v2i lhs, v2i rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

[[gnu::always_inline]]
inline static float iv2_len(v2i a) {
  return sqrtf((float)iv2_dot(a, a));
}

[[gnu::always_inline]]
inline static float iv2_dist(v2i lhs, v2i rhs) {
  v2i delta = iv2_sub(lhs, rhs);
  return iv2_len(delta);
}

typedef union v3f {
  struct {
    float x, y, z;
  };

  float v[3];
} v3f;

static const v3f v3_ux = (v3f){.x = 1};
static const v3f v3_uy = (v3f){.y = 1};
static const v3f v3_uz = (v3f){.z = 1};

[[gnu::always_inline]]
inline static v3f v3_add(v3f lhs, v3f rhs) {
  return (v3f){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

[[gnu::always_inline]]
inline static v3f v3_sub(v3f lhs, v3f rhs) {
  return (v3f){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

[[gnu::always_inline]]
inline static v3f v3_mul(v3f lhs, float scalar) {
  return (v3f){lhs.x * scalar, lhs.y * scalar, lhs.z * scalar};
}

[[gnu::always_inline]]
inline static v3f v3_div(v3f lhs, float scalar) {
  return (v3f){lhs.x / scalar, lhs.y / scalar, lhs.z / scalar};
}

[[gnu::always_inline]]
inline static v3f v3_cross(v3f lhs, v3f rhs) {
  // 23 31 12
  return (v3f){lhs.y * rhs.z - lhs.z * rhs.y,
                lhs.z * rhs.x - lhs.x * rhs.z,
                lhs.x * rhs.y - lhs.y * rhs.x};
}

[[gnu::always_inline]]
inline static float v3_dot(v3f lhs, v3f rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

[[gnu::always_inline]]
inline static float v3_len(v3f v) {
  return sqrtf(v3_dot(v, v));
}

[[gnu::always_inline]]
inline static float v3_dist(v3f lhs, v3f rhs) {
  v3f delta = v3_sub(lhs, rhs);
  return v3_len(delta);
}

[[gnu::always_inline]]
inline static v3f v3_normed(v3f v) {
  float len = v3_len(v);
  return (v3f){.x = v.x / len, .y = v.y / len, .z = v.z / len};
}

[[gnu::always_inline]]
inline static void v3_norm(v3f* v) {
  *v = v3_normed(*v);
}

[[gnu::always_inline]]
inline static v3f v3_lerp(v3f a, v3f b, float d) {
  return v3_add(a, v3_mul(v3_sub(b, a), d));
}

typedef union v4f {
  struct {
    float x, y, z, w;
  };

  float v[4];
} v4f;

static const v4f v4_ux = (v4f){.x = 1};
static const v4f v4_uy = (v4f){.y = 1};
static const v4f v4_uz = (v4f){.z = 1};
static const v4f v4_uw = (v4f){.w = 1};

[[gnu::always_inline]]
inline static v4f v4_add(v4f lhs, v4f rhs) {
  return (v4f){lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w};
}

[[gnu::always_inline]]
inline static v4f v4_sub(v4f lhs, v4f rhs) {
  return (v4f){lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w};
}

[[gnu::always_inline]]
inline static v4f v4_mul(v4f lhs, float scalar) {
  return (v4f){lhs.x * scalar, lhs.y * scalar, lhs.z * scalar, lhs.w * scalar};
}

[[gnu::always_inline]]
inline static v4f v4_div(v4f lhs, float scalar) {
  return (v4f){lhs.x / scalar, lhs.y / scalar, lhs.z / scalar, lhs.w / scalar};
}

[[gnu::always_inline]]
inline static float v4_dot(v4f lhs, v4f rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

[[gnu::always_inline]]
inline static float v4_len(v4f v) {
  return sqrtf(v4_dot(v, v));
}

typedef union m4f {
  float v[4][4];
  v4f r[4];
  struct {
    float
      _00, _01, _02, _03,
      _10, _11, _12, _13,
      _20, _21, _22, _23,
      _30, _31, _32, _33;
  };
} m4f;

static const m4f m4_ident = (m4f){.r = {v4_ux, v4_uy, v4_uz, v4_uw}};

[[gnu::always_inline]]
inline static v4f m4_col(m4f* m, int col) {
  return (v4f){m->v[0][col], m->v[1][col], m->v[2][col], m->v[3][col]};
}

[[gnu::always_inline]]
inline static m4f m4_tpose(m4f* orig) {
  m4f out;
  out.r[0] = m4_col(orig, 0);
  out.r[1] = m4_col(orig, 1);
  out.r[2] = m4_col(orig, 2);
  out.r[3] = m4_col(orig, 3);
  return out;
}

[[gnu::always_inline]]
inline static m4f m4_trans(float x, float y, float z) {
  m4f out = m4_ident;
  out.r[3] = (v4f){x, y, z, 1};
  return out;
}

[[gnu::always_inline]]
inline static m4f m4_trans_v(v3f p) {
  return m4_trans(p.x, p.y, p.z);
}

[[gnu::always_inline]]
inline static m4f m4_scale(float x, float y, float z) {
  m4f out = m4_ident;
  out.r[0].x = x;
  out.r[1].y = y;
  out.r[2].z = z;
  return out;
}

[[gnu::always_inline]]
inline static m4f m4_scale_v(v3f scale) {
  return m4_scale(scale.x, scale.y, scale.z);
}

[[gnu::always_inline]]
inline static m4f m4_rot_x(float radians) {
  float c = cosf(radians);
  float s = sinf(radians);

  m4f out = m4_ident;
  
}

static m4f m4_mul_p(m4f* lhs, m4f* rhs) {
  m4f out;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out.v[i][j] = v4_dot(lhs->r[i], m4_col(rhs, j));
    }
  }

  return out;
}

static m4f m4_mul(m4f lhs, m4f rhs) {
  m4f out;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      out.v[i][j] = v4_dot(lhs.r[i], m4_col(&rhs, j));
    }
  }

  return out;
}

static m4f m4_look(v3f pos, v3f dir, v3f up) {
  v3f f = v3_normed(dir);
  v3f s = v3_normed(v3_cross(f, up));
  v3f u = v3_cross(s, f);

  m4f out = {0};

  out.v[0][0] = s.v[0];
  out.v[0][1] = u.v[0];
  out.v[0][2] = -f.v[0];
  out.v[1][0] = s.v[1];
  out.v[1][1] = u.v[1];
  out.v[1][2] = -f.v[1];
  out.v[2][0] = s.v[2];
  out.v[2][1] = u.v[2];
  out.v[2][2] = -f.v[2];
  out.v[3][0] = -v3_dot(s, pos);
  out.v[3][1] = -v3_dot(u, pos);
  out.v[3][2] = v3_dot(f, pos);
  out.v[0][3] = out.v[1][3] = out.v[2][3] = 0.0f;
  out.v[3][3] = 1.0f;

  return out;
}

static m4f m4_persp(float fovy, float aspect, float z_near, float z_far) {
  m4f out = {0};

  float f = 1.f / tanf(fovy * 0.5f);
  float fn = 1.f / (z_near - z_far);

  out.v[0][0] = f / aspect;
  out.v[1][1] = f;
  out.v[2][2] = (z_near + z_far) * fn;
  out.v[2][3] = -1.0f;
  out.v[3][2] = 2.0f * z_near * z_far * fn;

  return out;
}

static m4f m4_ortho(float left, float right, float bottom, float top, float z_near, float z_far) {
  m4f out = m4_ident;

  float inv_rl = 1.0f / (right - left);
  float inv_tb = 1.0f / (top - bottom);
  float inv_fn = 1.0f / (z_far - z_near);

  out.r[0].x = 2 * inv_rl;
  out.r[1].y = 2 * inv_tb;
  out.r[2].z = -2 * inv_fn;

  out.r[3].x = -(right + left) * inv_rl;
  out.r[3].y = -(top + bottom) * inv_tb;
  out.r[3].z = -(z_far + z_near) * inv_fn;

  return out;
}

[[gnu::always_inline]]
inline static float lerp(float start, float end, float delta) {
  return start + (end - start) * delta;
}

[[gnu::always_inline]]
inline static float clamp(float val, float least, float most) {
  return fminf(fmaxf(val, least), most);
}

[[gnu::always_inline]]
inline static float rad(float deg) {
  return deg * M_PI / 180.f;
}

static size_t iv2_hash(void* key) {
  v2i* vec = key;

  return ((size_t)vec->v[0] << 32) | ((size_t)vec->v[1]);
}

static bool iv2_eq(void* _lhs, void* _rhs) {
  v2i* lhs = _lhs;
  v2i* rhs = _rhs;

  return lhs->v[0] == rhs->v[0] && lhs->v[1] == rhs->v[1];
}