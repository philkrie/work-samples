public enum Suit{
	Club(0), Diamond(1), Heart(2), Spade(3);
	private int value;
	private Suit(int v){this.value = v};
	public int getValue(){return value;}
	public static Suit getSuitFromValue(int value){return new Suit(value);}
}

public class Deck<T extends Card> {
	private ArrayList<T> cards; //all cards
	private int dealtIndex = 0;
	...
}