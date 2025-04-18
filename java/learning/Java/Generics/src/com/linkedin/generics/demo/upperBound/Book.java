package com.linkedin.generics.demo.upperBound;

/**
 * Description: A class creating a book object
 */
public class Book implements Boxable {
    /* Instance Variables */
    private String name;
    private String author;
    private double weight;

    public Book(String name, String author, double weight){
        this.name = name;
        this.author = author;
        this.weight = weight;
    }

    /* Getter methods */

    /**
     * Returns the name of the book
     * @return name of the book
     */
    public String getName(){
        return this.name;
    }

    /**
     * Returns the author of the book
     * @return the author of the book
     */
    public String getAuthor(){
        return this.author;
    }

    /**
     * Returns a double, representing the weight of the book
     * @return the weight of the book
     */
    public double getWeight() {
        return this.weight;
    }

    /* Setter methods */

    /**
     * Updates the name of the book, replacing it with the given name.
     * @param name the name of the book
     */
    public void setName(String name){
        this.name = name;
    }

    /**
     * Updates the author of the book, replacing it with given author.
     * @param author the author of the book
     */
    public void setAuthor(String author){
        this.author = author;
    }

    /**
     * Updates the weight of the book, replacing it with the given wegiht.
     * @param weight the weight of the book
     */
    public void setWeight(double weight) {
        this.weight = weight;
    }

    /**
     * Returns the String representation of the book, containing the name, author and the weight of the book.
     * @return name, author and the weight of the book
     */
    @Override
    public String toString() {
        return "Book{" +
                "name='" + name + '\'' +
                ", author='" + author + '\'' +
                ", weight=" + weight +
                '}';
    }
}
