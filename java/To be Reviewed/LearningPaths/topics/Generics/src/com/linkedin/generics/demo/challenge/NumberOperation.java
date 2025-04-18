package com.linkedin.generics.demo.challenge;

import java.util.*;
import java.util.stream.Collectors;

public class NumberOperation <N extends Number & Comparable<N>>{

    private final List<N> numbers;

    public NumberOperation(List<N> data){
        this.numbers = new ArrayList<>(data); // why created a new array? if the input is an immutable list and we try to change it using our code, such as sorting it, we will run into a problem.
    }

    public List<N> getSortedNumbers() {
        Collections.sort(this.numbers);
        return numbers;
    }

    public N getMaximum(){
        return Collections.max(numbers);
    }

    @Override
    public String toString(){
        StringBuilder b = new StringBuilder();
        return this.numbers.stream().map(Objects::toString).collect(Collectors.joining(", "));
    }

}
