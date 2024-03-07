// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) {
        // Press Alt+Enter with your caret at the highlighted text to see how
        // IntelliJ IDEA suggests fixing it.

        int sum=0;
        for (String number:args){
            sum=sum+Integer.parseInt(number);
        }
        System.out.print(sum);

        Mancare ceSeGateste = new Mancare();
        ceSeGateste.Placinta();
        Mancare CevaVegan = new MancareVegana();
        CevaVegan.CeSeMananca();
        CevaVegan.Felul();
        try {
            CevaVegan.increaseFoodCount();
        }
        catch (MyException e) {
            System.out.println(e);
        }
        try {
            Mancare.increaseFoodCount();
        }
        catch (MyException e) {
            System.out.println(e);
        }
        ceSeGateste.printFoodCount();
    }
}
class Mancare {
    public String felulSpecial;
    private static int uniqueFoods=2;
    public Mancare() {
        System.out.println("\nSe prepara: ");
        this.felulSpecial="Ceva";
    }

    void Placinta() {
        System.out.println("placinta.");
    }

    static void increaseFoodCount() throws MyException {
        uniqueFoods++;
        if(uniqueFoods>=5)
        throw new MyException("Prea mare");

    }

    void printFoodCount(){
        System.out.println(this.uniqueFoods);
    }
    void Carnati() {
    System.out.println("Carnati.");
    }
    void Felul() {
        System.out.println(felulSpecial);
    }
    void CeSeMananca(){
        System.out.println(felulSpecial);
    }

}
class MancareVegana extends Mancare{
    @Override void CeSeMananca(){
        felulSpecial="Ceva dar Vegan";
    }
}

