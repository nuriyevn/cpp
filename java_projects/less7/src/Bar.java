import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

/**
 * Created by nusik on 11/1/15.
 */

public class Bar {

    public static void print(ArrayList<Integer> list) {
        for (int i = 0; i < list.size(); i++)
        {
            System.out.println(list.get(i) + " ");
        }
        System.out.println("\n");
    }

    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        ArrayList<Integer> divByThree = new ArrayList<Integer>();
        ArrayList<Integer> divByTwo = new ArrayList<>();
        ArrayList<Integer> rest = new ArrayList<>();
        boolean already = false;
        for (int i = 0; i < 20; i++)
        {
            String str = reader.readLine();
            int n = Integer.parseInt(str);

            already = false;
            if (n % 3 == 0)
            {
                already = true;
                divByThree.add(n);
            }
            if (n % 2 == 0)
            {
                already = true;
                divByTwo.add(n);
            }
            if (!already)
                rest.add(n);
        }

        print(divByThree);
        print(divByTwo);
        print(rest);

    }
}
