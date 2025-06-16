#include "editor.h"
#include "input.h"
#include "../../engine/clock.h"

int main() {
    Editor editor;
    GameClock clock;

    init_editor(&editor);
    init_clock(&clock);

    while (!editor.quit) {
        SDL_Event ev;

        editor_nk_input_begin(&editor);
        while (SDL_PollEvent(&ev) != 0) {
            handle_input(&ev, &editor);
        }
        editor_nk_input_end(&editor);

        update_clock(&clock);
        update_editor_entities(&editor, clock.delta_time);

        render_editor_win(&editor, clock.delta_time);
        render_tilesheet_win(&editor);
        render_settings_win(&editor);
    }

    cleanup_editor(&editor);
    return 0;
}

