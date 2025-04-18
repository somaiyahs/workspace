package com.linkedin.generics.demo.upperBound;

/**
 *
 */
class Fruit implements Boxable{
    /* Instance variables */
    private String name;
    private String color;
    private String countryOfOrigin;
    private double weight;

    /**
     * Creating an instance of Fruit
     * @param name name of the fruit
     * @param color color of the fruit
     * @param countryOfOrigin country of origin of the fruit
     * @param weight weight of the fruit
     */
    public Fruit(String name, String color, String countryOfOrigin, double weight){
        this.name = name;
        this.color = color;
        this.countryOfOrigin = countryOfOrigin;
        this.weight = weight;
    }

    /**
     * Returns the name of the fruit.
     * @return name of the fruit
     */
    public String getName(){
        return this.name;
    }

    /**
     * Updates the name of the fruit to the given name.
     * @param name name of the fruit
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Returns the color of the fruit.
     * @return color of the fruit
     */
    public String getColor() {
        return color;
    }

    /**
     * Updated the color of the fruit to the given color
     * @param color color of the fruit
     */
    public void setColor(String color) {
        this.color = color;
    }

    /**
     * Returns the country of the origin of the fruit
     * @return country of the origin of the fruit
     */
    public String getCountryOfOrigin() {
        return countryOfOrigin;
    }

    /**
     * Updates the country of the origin of the fruit to the given countryOfOrigin
     * @param countryOfOrigin country of the origin
     */
    public void setCountryOfOrigin(String countryOfOrigin) {
        this.countryOfOrigin = countryOfOrigin;
    }

    /**
     * Returns the weight of the fruit
     * @return weight of the fruit
     */
    public double getWeight() {
        return weight;
    }

    /**
     * Updates the weight of the fruit to the given weight
     * @param weight weight of the fruit
     */
    public void setWeight(double weight) {
        this.weight = weight;
    }

    /**
     * Returns the string representation of the fruit specifying the name, color, country of the origin and the weight of the fruit.
     * @return the string representation of the fruit
     */
    @Override
    public String toString() {
        return "Fruit{" +
                "name='" + name + '\'' +
                ", color='" + color + '\'' +
                ", countryOfOrigin='" + countryOfOrigin + '\'' +
                ", weight=" + weight +
                '}';
    }
}