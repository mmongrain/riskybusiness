default: battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc
	g++ continent.cc territory.cc battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc -std=c++11 -o a.o

gui: territory.cc continent.cc battle.cc comp_player.cc game.cc gui_main.cc human_player.cc map.cc observer.cc player.cc
	g++ territory.cc continent.cc strategy_defensive.cc strategy_aggressive.cc strategy_random.cc battle.cc comp_player.cc game.cc gui_main.cc human_player.cc map.cc observer.cc player.cc -std=c++11 -o g.o -lsfml-graphics -lsfml-window -lsfml-system

player_view: comp_player.cc player.cc player_view_main.cc player_view.cc map.cc observer.cc human_player.cc battle.cc game.cc
	g++ comp_player.cc battle.cc game.cc human_player.cc player.cc player_view.cc player_view_main.cc map.cc observer.cc -std=c++11 -o player_view.o

clean:
	rm *.o
