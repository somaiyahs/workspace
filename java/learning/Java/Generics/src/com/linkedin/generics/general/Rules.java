package com.linkedin.generics.general;

import java.util.ArrayList;
import java.util.List;

public class Rules {
    public static void main(String[] args) {
        // The following line will give the compilation error: "Type argument cannot be of primitive type" for List<int> & "no instance(s) of type variable(s) E exist so that ArrayList<E> conforms to List<int>" for new ArrayList<>();
        // List<int> integers = new ArrayList<>();

        // to create a list of int we need to use the wrapper class Integer
        List<Integer> integers = new ArrayList<>();
        integers.add(10); // autoboxing : 10 will be wrapped in an Integer object before being added to the list
        int number = integers.get(0); // unboxing: the Integer object at index 0 will be unwrapped into an int primitive type before assigning it to the variable number.

        List<String> languages = new ArrayList<>();
        languages.add("English");

        // Although both languages and integers are born using List<E> generic type,
        // their type argument is different (one is Integer and the other is String)
        // it means that you cannot assign one list to the other
        // The line of code below produces the following compilation error if uncommented: "Incompatible types. Found: 'java.util.List<java.lang.String>', required: 'java.util.List<java.lang.Integer>'"
        // integers = languages;

        // creating another list of strings
        List<String> fruits = new ArrayList<>();
        fruits.add("Apple");

        // We can do the following assignment bc both languages and fruits are of the same type arguments.
        fruits = languages;
    }
}
