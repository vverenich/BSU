package task23;

import java.io.*;
import java.util.Scanner;

public class Code23{

    public static void parseToWord(int number) throws Exception {
    	if (number < 1 || number > 1000000000) {
    		System.out.println("number must be less, than 1000000000 and more, than 0");
    		return;
    	}
    	if (number == 10) {
    		System.out.println(number + " - дес€ть");
    		return;
    	}
    	int[] array_int = new int[4];
        String[][] array_string = new String[][] {
        	{" миллиард", " миллиарда", " миллиардов"},
            {" миллион", " миллиона", " миллионов"},
            {" тыс€ча", " тыс€чи", " тыс€ч"},
            {"", "", ""}
            };
        array_int[0] = (number - (number % 1000000000)) / 1000000000;
        array_int[1] = ((number % 1000000000) - (number % 1000000)) / 1000000;
        array_int[2] = ((number % 1000000) - (number % 1000)) / 1000;
        array_int[3] = number % 1000;
        String result = "";
        for (int i = 0; i < 4; i++)
        {
            if (array_int[i] != 0)
            {
                if (((array_int[i] - (array_int[i] % 100)) / 100) != 0)
                    switch (((array_int[i] - (array_int[i] % 100)) / 100))
                    {
                        case 1: result += " сто"; break;
                        case 2: result += " двести"; break;
                        case 3: result += " триста"; break;
                        case 4: result += " четыреста"; break;
                        case 5: result += " п€тьсот"; break;
                        case 6: result += " шестьсот"; break;
                        case 7: result += " семьсот"; break;
                        case 8: result += " восемьсот"; break;
                        case 9: result += " дев€тьсот"; break;
                    }
                if (((array_int[i] % 100) - ((array_int[i] % 100) % 10)) / 10 != 1)
                {
                    switch (((array_int[i] % 100) - ((array_int[i] % 100) % 10)) / 10)
                    {
                        case 2: result += " двадцать"; break;
                        case 3: result += " тридцать"; break;
                        case 4: result += " сорок"; break;
                        case 5: result += " п€тьдес€т"; break;
                        case 6: result += " шестьдес€т"; break;
                        case 7: result += " семьдес€т"; break;
                        case 8: result += " восемьдес€т"; break;
                        case 9: result += " дев€носто"; break;
                    }
                }
                switch (array_int[i] % 10)
                {
                    case 1: if (i == 2) result += " одна"; else result += " один"; break;
                    case 2: if (i == 2) result += " две"; else result += " два"; break;
                    case 3: result += " три"; break;
                    case 4: result += " четыре"; break;
                    case 5: result += " п€ть"; break;
                    case 6: result += " шесть"; break;
                    case 7: result += " семь"; break;
                    case 8: result += " восемь"; break;
                    case 9: result += " дев€ть"; break;
                }
            }
            else switch (array_int[i] % 100)
                {
                    case 10: result += " дес€ть"; break;
                    case 11: result += " одиннадцать"; break;
                    case 12: result += " двенадцать"; break;
                    case 13: result += " тринадцать"; break;
                    case 14: result += " четырнадцать"; break;
                    case 15: result += " п€тнадцать"; break;
                    case 16: result += " шестнадцать"; break;
                    case 17: result += " семнадцать"; break;
                    case 18: result += " восемннадцать"; break;
                    case 19: result += " дев€тнадцать"; break;
                }
            if (array_int[i] % 100 >= 10 && array_int[i] % 100 <= 19) result += " " + array_string[i][2] + " ";
            else switch (array_int[i] % 10)
                {
                    case 1: result += " " + array_string[i][0] + " "; break;
                    case 2:
                    case 3:
                    case 4: result += " " + array_string[i][1] + " "; break;
                    case 5:
                    case 6:
                    case 7:
                    case 8:
                    case 9: result += " " + array_string[i][2] + " "; break;
                }
        }
        System.out.println(number + " - " + result);
    }
    public static void task23(String path) throws Exception {
    	try(Scanner scanner = new Scanner(new File(path)))
    	{
    	    //чтение построчно
    	    String line;
    	    while(scanner.hasNextLine()){
    	    	line = scanner.nextLine();
                parseToWord(Integer.parseInt(line));
    	    }
    	} catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (Exception ex) {
        	System.out.println(ex.getMessage());
        }
    }
}
