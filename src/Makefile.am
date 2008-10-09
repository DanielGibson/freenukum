AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = freenukum

INCLUDES = \
					 -I$(srcdir)

freenukum_SOURCES = fn.h \
										fn_object.h \
										fn_actor.h          fn_actor.c \
										fn_borders.h        fn_borders.c \
										fn_bot.h            fn_bot.c \
										fn_draw.h           fn_draw.c \
										fn_drop.h           fn_drop.c \
										fn_effect.h         fn_effect.c \
										fn_error.h          fn_error.c \
										fn_error_cmdline.h  fn_error_cmdline.c \
										fn_game.h           fn_game.c \
										fn_hero.h           fn_hero.c \
										fn_infobox.h        fn_infobox.c \
										fn_item.h           fn_item.c \
										fn_level.h          fn_level.c \
										fn_mainmenu.h       fn_mainmenu.c \
										fn_msgbox.h         fn_msgbox.c \
										fn_picture.h        fn_picture.c \
										fn_picture_splash.h fn_picture_splash.c \
										fn_settings.h       fn_settings.c \
										fn_text.h           fn_text.c \
										fn_tile.h           fn_tile.c \
										fn_tilecache.h      fn_tilecache.c \
										fn_shot.h           fn_shot.c \
										fn_list.h           fn_list.c \
										fn_data.h           fn_data.c \
										fn_collision.h      fn_collision.c \
										freenukum.c

if TESTPROGRAMS
noinst_PROGRAMS = fn_test_tilecache \
                  fn_test_borders \
                  fn_test_draw \
                  fn_test_drop \
                  fn_test_effect \
                  fn_test_error \
                  fn_test_hero \
                  fn_test_infobox \
                  fn_test_inputbox \
									fn_test_menu \
                  fn_test_mainmenu \
                  fn_test_level_loader \
                  fn_test_msgbox \
                  fn_test_picture \
                  fn_test_picture_splash \
                  fn_test_settings \
                  fn_test_tile \
									fn_test_list

fn_test_tilecache_SOURCES = fn_test_tilecache.c \
                            fn.h \
														fn_tilecache.h       fn_tilecache.c \
														fn_tile.h            fn_tile.c \
														fn_draw.h            fn_draw.c \
														fn_error.h           fn_error.c \
														fn_error_cmdline.h   fn_error_cmdline.c

fn_test_borders_SOURCES = fn_test_borders.c \
													fn.h \
													fn_error_cmdline.h fn_error_cmdline.c \
													fn_error.h         fn_error.c \
													fn_tilecache.h     fn_tilecache.c \
													fn_tile.h          fn_tile.c \
													fn_draw.h          fn_draw.c \
													fn_borders.h       fn_borders.c \
													fn_text.h          fn_text.c

fn_test_draw_SOURCES = fn_test_draw.c \
                       fn.h \
											 fn_error_cmdline.h fn_error_cmdline.c \
											 fn_draw.h          fn_draw.c

fn_test_drop_SOURCES = fn_test_drop.c \
                       fn.h \
											 fn_tile.h          fn_tile.c \
											 fn_draw.h          fn_draw.c \
											 fn_drop.h          fn_drop.c

fn_test_effect_SOURCES = fn_test_effect.c \
                         fn_error_cmdline.h fn_error_cmdline.c \
												 fn_error.h         fn_error.c \
												 fn_picture.h       fn_picture.c \
												 fn_effect.h        fn_effect.c \
												 fn_draw.h          fn_draw.c \
												 fn.h

fn_test_error_SOURCES = fn_test_error.c \
                        fn_error.h      fn_error.c \
												fn.h

fn_test_hero_SOURCES = fn_test_hero.c \
                       fn_error.h          fn_error.c \
											 fn_error_cmdline.h  fn_error_cmdline.c \
											 fn_draw.h           fn_draw.c \
											 fn_tilecache.h      fn_tilecache.c \
											 fn_hero.h           fn_hero.c \
											 fn_tile.h           fn_tile.c \
											 fn_level.h          fn_level.c \
											 fn_shot.h           fn_shot.c \
											 fn_actor.h          fn_actor.c \
											 fn_bot.h            fn_bot.c \
											 fn_infobox.h        fn_infobox.c \
											 fn_msgbox.h         fn_msgbox.c \
											 fn_text.h           fn_text.c \
											 fn_list.h           fn_list.c \
											 fn_collision.h      fn_collision.c \
                       fn.h

fn_test_infobox_SOURCES = fn_test_infobox.c \
													fn_infobox.h        fn_infobox.c \
													fn_tilecache.h      fn_tilecache.c \
													fn_tile.h           fn_tile.c \
													fn_draw.h           fn_draw.c \
													fn_msgbox.h         fn_msgbox.c \
													fn_text.h           fn_text.c \
                          fn.h

fn_test_menu_SOURCES = fn_test_menu.c \
                       fn_menu.h              fn_menu.c \
											 fn_list.h              fn_list.c \
											 fn_tilecache.h         fn_tilecache.c \
											 fn_tile.h              fn_tile.c \
											 fn_draw.h              fn_draw.c \
											 fn_msgbox.h            fn_msgbox.c \
											 fn_text.h              fn_text.c \
											 fn.h

fn_test_inputbox_SOURCES = fn_test_inputbox.c \
													 fn_inputbox.h       fn_inputbox.c \
													 fn_inputfield.h     fn_inputfield.c \
													 fn_tilecache.h      fn_tilecache.c \
													 fn_tile.h           fn_tile.c \
													 fn_draw.h           fn_draw.c \
													 fn_msgbox.h         fn_msgbox.c \
													 fn_text.h           fn_text.c \
                           fn.h

fn_test_mainmenu_SOURCES = fn_test_mainmenu.c \
													 fn.h

fn_test_level_loader_SOURCES = fn_test_level_loader.c \
															 fn_hero.h           fn_hero.c \
															 fn_tilecache.h      fn_tilecache.c \
															 fn_tile.h           fn_tile.c \
															 fn_draw.h           fn_draw.c \
															 fn_level.h          fn_level.c \
															 fn_shot.h           fn_shot.c \
															 fn_actor.h          fn_actor.c \
															 fn_bot.h            fn_bot.c \
															 fn_infobox.h        fn_infobox.c \
															 fn_error_cmdline.h  fn_error_cmdline.c \
															 fn_error.h          fn_error.c \
															 fn_msgbox.h         fn_msgbox.c \
															 fn_text.h           fn_text.c \
															 fn_list.h           fn_list.c \
															 fn_collision.h      fn_collision.c \
															 fn.h

fn_test_msgbox_SOURCES = fn_test_msgbox.c \
												 fn_msgbox.h         fn_msgbox.c \
												 fn_text.h           fn_text.c \
												 fn_draw.h           fn_draw.c \
												 fn_tilecache.h      fn_tilecache.c \
												 fn_tile.h           fn_tile.c \
												 fn_error_cmdline.h  fn_error_cmdline.c \
												 fn_error.h          fn_error.c \
                         fn.h

fn_test_picture_SOURCES = fn_test_picture.c \
                          fn_picture.h        fn_picture.c \
													fn_draw.h           fn_draw.c \
													fn_error_cmdline.h  fn_error_cmdline.c \
													fn_error.h          fn_error.c \
                          fn.h

fn_test_picture_splash_SOURCES = fn_test_picture_splash.c \
                                 fn_picture.h        fn_picture.c \
                                 fn_picture_splash.h fn_picture_splash.c \
																 fn_draw.h           fn_draw.c \
																 fn_error_cmdline.h  fn_error_cmdline.c \
																 fn_error.h          fn_error.c \
																 fn_msgbox.h         fn_msgbox.c \
																 fn_text.h           fn_text.c \
																 fn_tilecache.h      fn_tilecache.c \
																 fn_tile.h           fn_tile.c \
                                 fn.h

fn_test_settings_SOURCES = fn_test_settings.c \
													 fn_settings.h      fn_settings.c \
                           fn.h

fn_test_tile_SOURCES = fn_test_tile.c \
                       fn_tile.h      fn_tile.c \
											 fn_draw.h      fn_draw.c \
                       fn.h

fn_test_list_SOURCES = fn_test_list.c \
                       fn_list.h      fn_list.c

endif # TESTPROGRAMS
