default: game_driver.cc map_editor.cc random_ai_player.cc defensive_ai_player.cc aggressive_ai_player.cc strategy.cc exceptions.cc gui.cc ui.cc card.cc deck.cc stats_basic.cc stats_battle.cc stats_control.cc continent.cc territory.cc battle.cc game.cc human_player.cc map.cc observer.cc player.cc player_view.cc
	g++ game_driver.cc map_editor.cc random_ai_player.cc defensive_ai_player.cc aggressive_ai_player.cc strategy.cc exceptions.cc gui.cc ui.cc card.cc deck.cc stats_basic.cc stats_battle.cc stats_control.cc continent.cc territory.cc battle.cc game.cc human_player.cc map.cc observer.cc player.cc player_view.cc -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system -o rb.o

clean:
	rm *.o
