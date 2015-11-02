import java.io.BufferedReader;
import java.io.InputStreamReader;

public class MaxNumber {
    public static void main(String[] args) throws Exception
    {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int nums[] = new int[5];
        for (int i = 0; i < 5; i++)
            nums[i] = Integer.parseInt(br.readLine());
        System.out.print("Maximum is = " + max(nums));
    }

    public static int max(int[] numbers)
    {
        int maximum = numbers[0];
        for (int i = 1; i < numbers.length; i++)
            maximum = (numbers[i] > maximum) ? numbers[i] : maximum;
        return maximum;
    }


}
