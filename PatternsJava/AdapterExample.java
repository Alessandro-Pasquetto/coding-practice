public class AdapterExample {

    // Classe incompatibile
    class Adaptee {
        void specificFunction() {
            System.out.println("Adaptee function");
        }
    }

    interface Target {
        void function();
    }

    class Adapter implements Target {
        private Adaptee adaptee;

        Adapter(Adaptee adaptee) {
            this.adaptee = adaptee;
        }

        @Override
        public void function() {
            adaptee.specificFunction();
        }
    }

    public static void main(String[] args) {
        AdapterExample example = new AdapterExample();

        Adaptee adaptee = example.new Adaptee();

        Target target = example.new Adapter(adaptee);

        target.function();
    }
}