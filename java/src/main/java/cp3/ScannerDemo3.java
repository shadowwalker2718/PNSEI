package cp3;

import java.util.Scanner;

// https://stackoverflow.com/questions/2390500/java-scanning-string-for-a-pattern
public class ScannerDemo3 {
    public static void main(String[] args)
    {
        try {
            Scanner sc = new Scanner("1\n[5, 6]\nRXIBDIBF\n");
            sc.useDelimiter("\n");

            String pattern = "[0-9]+";
            while ((sc.hasNext(pattern))) {
                System.out.println(sc.next(pattern));
            }

            pattern = "\\[[0-9]+, [0-9]+\\]";
            while ((sc.hasNext(pattern))) {
                System.out.println(sc.next(pattern));
            }

            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
