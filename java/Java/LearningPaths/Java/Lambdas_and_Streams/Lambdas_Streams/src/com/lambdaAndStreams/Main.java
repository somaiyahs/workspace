package com.lambdaAndStreams;

import java.util.Random;
import java.util.function.IntBinaryOperator;

import com.lambdaAndStreams.greeting.*;

public class Main {

    // implementing the sayHello() function using the OOP concept
    public static void main(String[] args) {
        Greeting greeting = new HelloGreeting();
        greeting.sayHello();
    
        // Quicker way to implement sayHello() function without the HelloGreeting class
        // create a new instance of Greeting and override the method sayHello() within that statement 
        Greeting greeting2 = new Greeting() {
            @Override
            public void sayHello(){ 
                System.out.println("Hello Quicker Way!!"); 
            }
        };
        
        greeting2.sayHello();

        // the pair of paranthesis () right after equal sign is technically the same as 
        // the pair of paranthesis of sayHello() method. they will contain the arguments for the method if it had any. 
        // After the -> sign, we will put the body for the method we are overriding. 
        Greeting greeting3 = () -> System.out.println("Hello world Lambda!");
        greeting3.sayHello();

        // implementing calculate method from Calculator interface
        // by creating an instance of it and using lambda feature. 
        // using lambda to override a method that has arguments and multiple lines of code for the body. 
        Calculator cal = (int x, int y) -> {
            //generate a random number 
            Random random = new Random();
            int randomNumber = random.nextInt(50);
            return x * y + randomNumber;
        };
 
        System.out.println(cal.calculate(1, 2));

        // most of the time you do not have to create your own interface. 
        // Java has quiet a few interfaces ready-made which you can use. 
        // ex. the method "int calculate(int x, int y);" can be found in the 
        // package called java.util.function (checkout the documentations). 
        // one of the most commonly used interfaces is 
        // Function<T,R> : Represents a function that accepts one argument and produces a result. 

        // ready-made interface in Java that can be used instead of Calculator interface 
        // IntBinaryOperator: Represents an operation upon two int-valued arguments and producing and int-valued result. 
        IntBinaryOperator iBinaryOperator = (int x, int y) -> {
            Random random = new Random();
            int randomNumber = random.nextInt(50);
            return x * y + randomNumber; 
        };
        System.out.println(iBinaryOperator.applyAsInt(3, 4));
    }

}
