#include <stdio.h>

#include <sokol_app.h>
#include <sokol_args.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>

#include "simple.glsl.h"

static struct {
  sg_pipeline pip{};
  sg_bindings bind{};
  sg_pass_action pass_action{};
} state;

void init() {
  sg_setup({.context = sapp_sgcontext()});

  float vertices[] = {// positions        //colors
                      0.0f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
                      0.5f,  -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
                      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f};

  state.bind.vertex_buffers[0] = sg_make_buffer(
      {.data = SG_RANGE(vertices), .label = "triangle-vertices"});

  sg_shader shd = sg_make_shader(simple_shader_desc(sg_query_backend()));

  sg_pipeline_desc pip_desc = {};
  pip_desc.shader = shd;
  pip_desc.layout.attrs[ATTR_vs_position] = {.format = SG_VERTEXFORMAT_FLOAT3};
  pip_desc.layout.attrs[ATTR_vs_color0] = {.format = SG_VERTEXFORMAT_FLOAT4};
  pip_desc.label = "triangle-pipeline";

  state.pip = sg_make_pipeline(pip_desc);

  state.pass_action.colors[0] = {.action = SG_ACTION_CLEAR,
                                 .value = {0.0f, 0.0f, 0.0f, 1.0f}};
}

void frame() {
  sg_begin_default_pass(&state.pass_action, sapp_width(), sapp_height());
  sg_apply_pipeline(state.pip);
  sg_apply_bindings(&state.bind);
  sg_draw(0, 3, 1);
  sg_end_pass();
  sg_commit();
}

void cleanup() { sg_shutdown(); }

void event_cb(const sapp_event *ev) {
  if (ev->type == SAPP_EVENTTYPE_MOUSE_MOVE) {
    printf("mouse: %.2f, %.2f\n", ev->mouse_x, ev->mouse_y);
  }
}

sapp_desc sokol_main(int argc, char *argv[]) {
  sargs_setup({.argc = argc, .argv = argv});
  if (sargs_exists("test")) {
    printf("test -> %s\n", sargs_value("test"));
  }

  return {.init_cb = init,
          .frame_cb = frame,
          .cleanup_cb = cleanup,
          .event_cb = event_cb,
          .width = 400,
          .height = 300,
          .window_title = "Test",
          .icon = {.sokol_default = true}};
}
