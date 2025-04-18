package com.linkedin.generics.demo.noUpperBound;

public class TestBoxGenerics {
    public static void main(String[] args) {

        Box<Book> bookBox = new Box<>();
        bookBox.addItem(new Book("Harry Potter & The Half Blood Prince", "JK Rowling", 0.5));
        bookBox.addItem(new Book("Deep Work", "Cal Newport", 0.25));
        System.out.println(bookBox.getLatestItem());
        System.out.println(bookBox);
        System.out.println("Book Count: " + BoxUtils.getCountOfItems(bookBox));

        Box<Fruit> fruitBox = new Box<>();
        fruitBox.addItem(new Fruit("Mango", "India", "Yellow", 0.5));
        fruitBox.addItem(new Fruit("Banana", "Brazil", "Green", 0.3));
        System.out.println(fruitBox.getLatestItem());
        System.out.println(fruitBox);
        System.out.println("Fruit Count: " + BoxUtils.getCountOfItems(fruitBox));
    }
}
