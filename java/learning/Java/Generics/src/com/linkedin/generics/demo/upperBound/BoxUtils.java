package com.linkedin.generics.demo.upperBound;

public class BoxUtils {

    // Writing a generic method outside of the genetic class
    public static <T extends Boxable> int getCountOfItems(Box<T> box){
        return box.getItems().size();
    }
}
