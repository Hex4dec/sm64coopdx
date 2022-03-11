#include "djui.h"
#include "src/pc/utils/misc.h"
#include "src/pc/configfile.h"
#include "data/dynos_coop.c.h"

static void djui_panel_dynos_apply(struct DjuiBase* caller) {
    dynos_packs_set_enabled(caller->tag, caller->bTag);
}

void djui_panel_dynos_create(struct DjuiBase* caller) {
    int packCount = dynos_packs_get_count();
    f32 bodyHeight = 32 * (packCount) + 64 * 1 + 16 * (packCount + 1);

    struct DjuiBase* defaultBase = NULL;
    struct DjuiThreePanel* panel = djui_panel_menu_create(bodyHeight, "\\#ff0800\\D\\#1be700\\Y\\#00b3ff\\N\\#ffef00\\O\\#ff0800\\S");
    struct DjuiFlowLayout* body = (struct DjuiFlowLayout*)djui_three_panel_get_body(panel);

    {
        for (int i = 0; i < packCount; i++) {
            bool tmp = dynos_packs_get_enabled(i);
            const char* pack = dynos_packs_get(i);

            struct DjuiCheckbox* checkbox1 = djui_checkbox_create(&body->base, pack, &tmp);
            checkbox1->base.tag = i;
            checkbox1->base.bTag = tmp;
            checkbox1->value = &checkbox1->base.bTag;

            djui_base_set_size_type(&checkbox1->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
            djui_base_set_size(&checkbox1->base, 1.0f, 32);
            djui_interactable_hook_value_change(&checkbox1->base, djui_panel_dynos_apply);
            if (i == 0) { defaultBase = &checkbox1->base; }
        }

        struct DjuiButton* button6 = djui_button_create(&body->base, "Back");
        djui_base_set_size_type(&button6->base, DJUI_SVT_RELATIVE, DJUI_SVT_ABSOLUTE);
        djui_base_set_size(&button6->base, 1.0f, 64);
        djui_button_set_style(button6, 1);
        djui_interactable_hook_click(&button6->base, djui_panel_menu_back);
    }

    djui_panel_add(caller, &panel->base, defaultBase);
}