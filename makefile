default: battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc
	g++ continent.cc territory.cc battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc -std=c++11 -o a.o

stats: battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc
	g++ card.cc stats.cc stats_basic.cc stats_battle.cc stats_control.cc stats_main.cc continent.cc territory.cc battle.cc comp_player.cc game.cc human_player.cc map.cc observer.cc player.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc player_view.cc -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -o stats.o

map: battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc
	g++ graph_main.cc card.cc stats.cc stats_basic.cc stats_battle.cc stats_control.cc continent.cc territory.cc battle.cc comp_player.cc game.cc human_player.cc map.cc observer.cc player.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc player_view.cc -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -o map.o

gui: territory.cc continent.cc battle.cc comp_player.cc game.cc gui_main.cc human_player.cc map.cc observer.cc player.cc
	g++ gui_main.cc card.cc deck.cc stats.cc stats_basic.cc stats_battle.cc stats_control.cc continent.cc territory.cc battle.cc comp_player.cc game.cc human_player.cc map.cc observer.cc player.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc player_view.cc -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -o g.o

win_gui: territory.cc continent.cc battle.cc comp_player.cc game.cc gui_main.cc human_player.cc map.cc observer.cc player.cc
	/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/bin/i586-mingw32-gcc player_view.cc territory.cc continent.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc battle.cc comp_player.cc game.cc gui_main.cc human_player.cc map.cc observer.cc player.cc -std=c++11 -o gui.exe -lsfml-graphics -lsfml-window -lsfml-system

player_view: comp_player.cc player.cc player_view_main.cc player_view.cc map.cc observer.cc human_player.cc battle.cc game.cc
	g++ comp_player.cc battle.cc game.cc human_player.cc player.cc player_view.cc player_view_main.cc map.cc observer.cc -std=c++11 -o player_view.o

clean:
	rm *.o
