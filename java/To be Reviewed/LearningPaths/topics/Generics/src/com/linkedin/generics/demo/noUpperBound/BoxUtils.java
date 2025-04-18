package com.linkedin.generics.demo.noUpperBound;

public class BoxUtils {

    // Writing a generic method outside of the genetic class
    public static <T> int getCountOfItems(Box<T> box){
        return box.getItems().size();
    }
}
