#include <sokol_app.h>
#include <sokol_args.h>
#include <sokol_gfx.h>
#include <sokol_glue.h>

#include <stdio.h>

sg_pass_action pass_action = {};

void init() {
  sg_setup({.context = sapp_sgcontext()});
  pass_action.colors[0] = {.action = SG_ACTION_CLEAR,
                           .value = {1.0f, 0.0f, 0.0f, 1.0f}};
}

void frame() {
  float g = pass_action.colors[0].value.g + 0.01f;
  pass_action.colors[0].value.g = (g > 1.0f) ? 0.0f : g;
  sg_begin_default_pass(&pass_action, sapp_width(), sapp_height());
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
