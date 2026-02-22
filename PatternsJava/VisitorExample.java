public class VisitorExample {

    interface Element {
        void accept(Visitor visitor);
    }

    class ElementA implements Element {

        @Override
        public void accept(Visitor visitor) {
            visitor.visit(this);
        }
    }

    class ElementB implements Element {

        @Override
        public void accept(Visitor visitor) {
            visitor.visit(this);
        }
    }

    // Concrete visitor
    class Visitor{
        public void visit(ElementA elementA) {
            System.out.println("Visiting ElementA");
        }

        public void visit(ElementB elementB) {
            System.out.println("Visiting ElementB");
        }
    }

    public static void main(String[] args) {
        VisitorExample example = new VisitorExample();

        Element elementA = example.new ElementA();
        Element elementB = example.new ElementB();

        Visitor visitor = example.new Visitor();

        elementA.accept(visitor);
        elementB.accept(visitor);
    }
}