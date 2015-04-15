class DeckTest {
	void DeckTest::TestClear() {
		Deck::Instance().Clear();
		assert( cards.size() == 0 );
	}
	void DeckTest::TestDraw() {

	}
}