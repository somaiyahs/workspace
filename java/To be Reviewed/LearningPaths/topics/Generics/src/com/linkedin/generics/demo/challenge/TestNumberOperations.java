package com.linkedin.generics.demo.challenge;

import java.util.ArrayList;
import java.util.List;

public class TestNumberOperations {
    public static void main(String[] args) {
        List<Long> numbers = new ArrayList<>();
        numbers.add(23L);
        numbers.add(10L);
        numbers.add(190L);
        numbers.add(0L);
        System.out.println(numbers);

        NumberOperation<Long> numOps = new NumberOperation<>(numbers);
        System.out.println(numOps);
        System.out.println(numOps.getSortedNumbers());
        System.out.println(numOps.getMaximum());
    }
}
