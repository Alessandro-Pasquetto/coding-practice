public class FactoryMethod {

    // Classes
    abstract class SuperClass {
        abstract void method();
    }

    class Class1 extends SuperClass{
        Class1(){};
        
        @Override
        void method(){
            System.out.println("C1");
        }
    }

    class Class2 extends SuperClass{
        Class2(){};
        
        @Override
        void method(){
            System.out.println("C2");
        }
    }

    // Factory classes
    abstract class Factory {
        abstract SuperClass create();
    }

    class FactoryClass1 extends Factory{
        @Override
        SuperClass create(){
            return new Class1();
        }
    }

    class FactoryClass2 extends Factory{
        @Override
        SuperClass create(){
            return new Class2();
        }
    }

    public static void main(String[] args) {
        FactoryMethod fm = new FactoryMethod();

        Factory f1 = fm.new FactoryClass1();
        Factory f2 = fm.new FactoryClass2();

        SuperClass c1 = f1.create();
        SuperClass c2 = f2.create();

        c1.method();
        c2.method();
    }
}