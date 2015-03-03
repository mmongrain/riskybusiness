default: battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc
	g++ battle.cc comp_player.cc game.cc game_driver.cc human_player.cc map.cc observer.cc player.cc -std=c++11 -o a.o

player_view: comp_player.cc player.cc player_view_main.cc player_view.cc map.cc observer.cc human_player.cc battle.cc game.cc
	g++ comp_player.cc battle.cc game.cc human_player.cc player.cc player_view.cc player_view_main.cc map.cc observer.cc -std=c++11 -o player_view.o 

clean:
	rm *.o
