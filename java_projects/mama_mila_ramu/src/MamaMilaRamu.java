import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;

/* Слово «именно»
1. Создай список из слов «мама», «мыла», «раму».
2. После каждого слова вставь в список строку, содержащую слово «именно».
3. Используя цикл for вывести результат на экран, каждый элемент списка с новой строки.
*/

public class MamaMilaRamu
{
    public static void main(String[] args) throws Exception
    {
        //напишите тут ваш код
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

        ArrayList<String> list = new ArrayList<>();


        list.add("мама");
        list.add("мыла");
        list.add("раму");

        String exactly = "именно";
        list.add(1, exactly);
        list.add(3, exactly);
        list.add(5, exactly);

        for (String s : list) {
            System.out.println(s + " ");
        }

    }
}
