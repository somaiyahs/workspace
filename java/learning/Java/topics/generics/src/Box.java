import java.util.ArrayList;
import java.util.List;

/**
 * Description: a generic class to hold multiple of items of type T
 */

public class Box<T> {
//Instance Variables
    private final List<T> items;

    /**
     * Creating an instance of the Box class
     */
    public Box(){
        this.items = new ArrayList<>();
    }

    /**
     * Returns the list of the items in the box.
     * @return the list of the items in the box
     */
    public List<T> getItems(){
        return this.items;
    }

    @Override
    public String toString() {
        return "Box{" +
                "items=" + items +
                '}';
    }
}
