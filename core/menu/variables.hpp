#pragma once
#include <string>

namespace var {
	namespace unload {
		inline bool enabled = false;
	}

	namespace menu {
		inline float accent[4] = { 0.769f, 0.161f, 0.835f, 1.0f };
		inline bool background = false;
		inline float background_color[4] = { 0.f, 0.f, 0.f, 0.1f };
		inline bool background_effect = false;
		inline float background_effect_color[4] = { 1.f, 1.f, 1.f, 1.f };
		inline int keybind = 0x2D;
	}

	namespace visuals {
		namespace esp {
			namespace dlight {
				inline bool enabled = false;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				inline int radius = 100;
			}
		}

		namespace chams {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 1;
			inline bool model_occlusion = false;
			inline bool wireframe_overlay = false;
			namespace arms {
				inline bool enabled = false;
				inline bool occluded = false;
				inline bool draw_original = false;
				inline bool remove_sleeves = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				namespace overlay {
					inline bool enabled = false;
					inline bool wireframe = false;
					inline int material = 0;
					inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				}
			}
			namespace weapon {
				inline bool enabled = false;
				inline bool occluded = false;
				inline bool draw_original = false;
				inline int material = 0;
				inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				namespace overlay {
					inline bool enabled = false;
					inline bool wireframe = false;
					inline int material = 0;
					inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
				}
			}
		}

		namespace trail {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int life = 1;
		}
		namespace local_dlight {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int radius = 100;
		}
		namespace bullet_tracers {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace bullet_impacts {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace view {
			inline int fov = 90;
			inline int spin_speed = 1;
			inline int angle = 0;
			inline bool spin = false;
			inline bool viewmodel = false;
			inline int model = 60;
			inline float aspect = 0.f;
		}
		namespace motionblur {
			inline bool enabled = false;
			inline float strength = 1;
		}
		namespace fog_changer {
			inline bool enabled = false;
			inline float color[4] = { 1.f, 1.f, 1.f, 1.f };
			inline int start = 0;
		}
		
		inline bool disable_postprocess = false;
		inline bool watermark = false;
	}

	namespace misc {
		inline bool clantag = false;
		inline bool killsay = false;
		inline bool autoaccept = false;
		inline bool rank_reveal = false;
		inline bool unlock_inventory = false;
		namespace doorspammer {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		
		namespace knife {
			inline int model = 0;
			inline int skin = 0;
			inline bool custom_color = false;
			inline float color1[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color2[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color3[4] = { 1.f, 1.f, 1.f, 1.f };
			inline float color4[4] = { 1.f, 1.f, 1.f, 1.f };
		}
		namespace glove {
			inline int model = 0;
			inline int skin = 0;
		}
	}

	namespace movement {
		namespace bunnyhop {
			inline bool enabled = false;
			inline int hitchance = 100;
		}
		namespace blockbot {
			inline bool enabled = false;
			inline int keybind = 0;
			inline int kb_style = 2;
		}
		inline int ticks = 32;
		inline float lock_factor = 0.5f;
		inline bool slidewalk = false;
	}
}