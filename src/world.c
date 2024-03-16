#include "world.h"
#include "typedefs.h"

float chunk_get_y(v3f world_pos) {
  static fnl_state* noise = NULL;
  if (!noise) {
    noise = objdup(fnlCreateState());
  }

  return fnlGetNoise2D(noise, world_pos.x * 4, world_pos.z * 4) * 5;
}

v3f chunk_get_pos(v2i pos, int off_x, int off_z) {
  v3f base = {
    pos.x * chunk_size + off_x * chunk_ratio,
    0,
    pos.y * chunk_size + off_z * chunk_ratio,
  };

  base.y = chunk_get_y(base);
  return base;
}

chunk chunk_new(v2i pos) {
  chunk_vtx* verts = arr_new(chunk_vtx, 4);

  for (int i = 0; i < chunk_qty; i++) {
    for (int j = 0; j < chunk_qty; j++) {
      v3f a = chunk_get_pos(pos, i, j);
      v3f b = chunk_get_pos(pos, i + 1, j);
      v3f c = chunk_get_pos(pos, i + 1, j + 1);
      v3f d = chunk_get_pos(pos, i, j + 1);

      // abc acd
      v3f n_abc = v3_cross(v3_sub(c, a), v3_sub(b, a));
      v3f n_acd = v3_cross(v3_sub(d, a), v3_sub(c, a));

      arr_add(&verts, &(chunk_vtx){.pos = a, .norm = n_abc});
      arr_add(&verts, &(chunk_vtx){.pos = b, .norm = n_abc});
      arr_add(&verts, &(chunk_vtx){.pos = c, .norm = n_abc});

      arr_add(&verts, &(chunk_vtx){.pos = a, .norm = n_acd});
      arr_add(&verts, &(chunk_vtx){.pos = c, .norm = n_acd});
      arr_add(&verts, &(chunk_vtx){.pos = d, .norm = n_acd});
    }
  }

  buf vbo = buf_new(GL_ARRAY_BUFFER);

  buf_data_n(&vbo, GL_STATIC_DRAW, sizeof(chunk_vtx), arr_len(verts), verts);

  chunk c = {
    .vao = vao_new(&vbo, NULL, 3, (attrib[]){attr_3f, attr_3f, attr_2f}),
    .pos = pos,
    .n_inds = arr_len(verts)
  };

  return c;
}

world world_new() {
  world w = {
    .chunks = map_new(4, sizeof(v2i), sizeof(chunk), 0.75f, iv2_eq, iv2_hash)
  };

  return w;
}

v2i world_get_chunk_pos(v3f world_pos) {
  return (v2i){(int)(world_pos.x / (float)chunk_size),
               (int)(world_pos.z / (float)chunk_size)};
}

void world_draw(world* w, cam* c, float d) {
  v2i cam_pos = world_get_chunk_pos(cam_get_pos(c, d));

  (void)mod_get_shader(c, m4_ident, d);

  for (int i = -world_draw_dist; i <= world_draw_dist; i++) {
    for (int j = -world_draw_dist; j <= world_draw_dist; j++) {
      v2i chunk_pos = iv2_add_i(cam_pos, i, j);

      if (!map_has(&w->chunks, &chunk_pos)) {
        chunk ch = chunk_new(chunk_pos);
        map_add(&w->chunks, &chunk_pos, &ch);
      }

      chunk* ch = map_at(&w->chunks, &chunk_pos);
      vao_bind(&ch->vao);
      gl_draw_arrays(GL_TRIANGLES, 0, ch->n_inds);
    }
  }
}
