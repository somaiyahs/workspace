package com.linkedin.generics.general;

import java.util.ArrayList;
import java.util.List;

public class GenericCode {

    public static void main(String[] args) {
        List<String> languages = new ArrayList<String>(); // This is a non-generic list, so you can add any object or values to it.
        // Anything that is added to this list however, will be treated as an Object type.
        // This list is called a raw list or raw type.


        languages.add("English");
        languages.add("Sweedish");
        //languages.add(23); // When uncommented you can see that you will get a compilation error due to the type safety check by the compiler.
        // 'add(java.lang.String)' in 'java.util.List' cannot be applied to '(int)'
        processLanguages(languages, 0);
        processLanguages(languages, 1);
    }

    private static void processLanguages(List<String> data, int index){ // have to define the parameterize type in the method definition as well.
        String language = data.get(index); //no more need to explicit casting
    }
}
