package com.linkedin.generics.general;

import java.util.ArrayList;
import java.util.List;

public class NonGenericCode {

    public static void main(String[] args) {
        List languages = new ArrayList(); // This is a non-generic list, so you can add any object or values to it.
        // Anything that is added to this list however, will be treated as an Object type.
        // This list is called a raw list or raw type.


        languages.add("English");
        Object value = new String("Sweedish");
        languages.add(value);
        languages.add(23); // This will be allowed since we have a raw list, but we will have a runtime error when processLanguages method is invoked and we get to the first line of the code. because 23 is a Number object and we cannot cast it into a string.
        processLanguages(languages, 0);
        processLanguages(languages, 1);
        processLanguages(languages, 2);
    }

    private static void processLanguages(List data, int index){
        String language = (String) data.get(index); // becuase the element in 0 index is of type object, and you cannot capture it in a string becuse it is an incompatible operation and the compiler doe not allow such thing. Therefore we need to do an explicit casting (see Casting topic for more)
        System.out.println(language);
    }
}
